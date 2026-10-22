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


//------------------------------------------------------------------------------------------
class InternetChecker : public std::enable_shared_from_this<InternetChecker> {
public:
    // Iniciamos la verificación asíncrona pasándole el contexto de ejecución y el callback
    static void check(asio::io_context& ctx, std::function<void(bool)> callback) {
        auto checker = std::shared_ptr<InternetChecker>(new InternetChecker(ctx, callback));
        checker->start();
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

    void start() {
        // 1. Configuramos un temporizador para controlar el tiempo límite (Timeout) de 3 segundos
        timer_.expires_after(std::chrono::seconds(3));
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
            callback_(true);  // ¡Conectado!
        } else {
            callback_(false); // Falló la conexión (p. ej. red inalcanzable)
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
