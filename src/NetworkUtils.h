/*==============================================================================

    Mosaic: Live Visual Patching Creative-Coding Platform

    Copyright (c) 2026 Emanuele Mazza aka n3m3da <emanuelemazza@d3cod3.org>

    Mosaic is distributed under the MIT License. This gives everyone the
    freedoms to use Mosaic in any context: commercial or non-commercial,
    public or private, open or closed source.

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
    OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.

    See https://github.com/d3cod3/Mosaic for documentation

==============================================================================*/

#pragma once

#include "ofMain.h"

#include <iostream>
#include <asio.hpp>
#include <chrono>
#include <functional>
#include <memory>
#include <vector>
#include <string>
#include <random>


//------------------------------------------------------------------------------------------
class InternetChecker : public std::enable_shared_from_this<InternetChecker> {
public:
    // Iniciamos la verificación asíncrona pasándole el contexto de ejecución y el callback
    static void check(asio::io_context& ctx, int sec, std::function<void(bool)> callback) {
        auto checker = std::shared_ptr<InternetChecker>(new InternetChecker(ctx, callback));
        checker->start(sec);
    }

private:
    asio::ip::tcp::socket socket_;
    asio::steady_timer timer_;
    asio::ip::tcp::endpoint endpoint_;
    std::function<void(bool)> callback_;
    bool has_responded_ = false;

    InternetChecker(asio::io_context& ctx, std::function<void(bool)> callback)
        : socket_(ctx),
          timer_(ctx),
          endpoint_(asio::ip::make_address("202.61.236.67"), 443),
          callback_(callback) {}

    void start(int seconds) {
        // 1. Configuramos un temporizador para controlar el tiempo límite
        timer_.expires_after(std::chrono::seconds(seconds));
        timer_.async_wait(std::bind(&InternetChecker::handle_timeout, shared_from_this(), std::placeholders::_1));

        // 2. Iniciamos el intento de conexión TCP asíncrono
        socket_.open(asio::ip::tcp::v4());
        socket_.async_connect(endpoint_, std::bind(&InternetChecker::handle_connect, shared_from_this(), std::placeholders::_1));
    }

    void handle_connect(const asio::error_code& ec) {
        if (has_responded_) return;

        // Cancelamos el temporizador ya que obtuvimos respuesta (éxito o fallo rápido)
        timer_.cancel();
        has_responded_ = true;

        if (!ec) {
            socket_.close();
            callback_(true);  // conected
        } else {
            callback_(false); // conexion fault
        }
    }

    void handle_timeout(const asio::error_code& ec) {
        // Si el temporizador no fue cancelado explícitamente y aún no hemos respondido...
        if (!ec && !has_responded_) {
            has_responded_ = true;
            asio::error_code ignored_ec;
            socket_.close(ignored_ec); // Forzamos el cierre del socket para abortar la conexión activa
            callback_(false); // Error por límite de tiempo excedido
        }
    }
};

//--------------------------------------------------------------
inline bool checkInternetReachability(){ // Linux/macOS only

    FILE *output = popen("ping -c 1 www.github.com | grep -c from","r");

    unsigned int i;
    bool fsf = false;
    if(fscanf(output,"%u",&i)) fsf = true;

    if(i == 1 && fsf){
        string tmpstr = "------------------- INTERNET IS AVAILABLE!";
        ofLog(OF_LOG_NOTICE,"%s",tmpstr.c_str());
        pclose(output);
        return true;
    }else{
        string tmpstr = "INTERNET IS NOT AVAILABLE!";
        ofLog(OF_LOG_ERROR,"%s",tmpstr.c_str());
        pclose(output);
        return false;
    }
}

//--------------------------------------------------------------
inline std::string getRandomUserAgent(std::string response){
    // plan B useragents strings
    static const std::vector<std::string> commonUserAgents = {
            "Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10_6_6; en-us) AppleWebKit/533.20.25 (KHTML, like Gecko) Version/5.0.4 Safari/533.20.27"
            "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/129.0.0.0 Safari/537.36",
            "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/129.0.0.0 Safari/537.36",
            "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:130.0) Gecko/20100101 Firefox/130.0",
            "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/17.6 Safari/605.1.15",
            "Mozilla/5.0 (Linux; Android 10; K) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/129.0.0.0 Mobile Safari/537.36",
            "Mozilla/5.0 (iPhone; CPU iPhone OS 17_6_1 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/17.6 Mobile/15E148 Safari/605.1.15",
            "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/129.0.0.0 Safari/537.36"
    };

    static std::random_device rd;
    static std::mt19937 generator(rd());

    pugi::xml_document      xml;
    bool isLoaded;
    std::string s = response;
    isLoaded = xml.load_string(s.c_str()) != pugi::status_ok;
    if(isLoaded){
        pugi::xpath_node_set ua = xml.select_nodes("//useragent");
        std::vector<std::string> uas;
        for (pugi::xpath_node xpath_node : ua) {
            pugi::xml_node node = xpath_node.node();
            pugi::xml_attribute attr = node.attribute("useragent");
            if (attr && std::strlen(attr.value()) > 0) {
                uas.push_back(attr.value());
            }
            //std::cout << "UA: " << attr.value() << std::endl;
        }

        // locally store the useragents xml file
        bool xmlSaved = xml.save_file(ofToDataPath("www/gecko/useragentswitcher.xml","true").c_str());

        std::uniform_int_distribution<size_t> distribution(0, uas.size() - 1);
        return uas[distribution(generator)];
    }

    std::uniform_int_distribution<size_t> distribution(0, commonUserAgents.size() - 1);
    return commonUserAgents[distribution(generator)];
}
