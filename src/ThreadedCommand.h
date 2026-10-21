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

#include <thread>
#include <boost/process.hpp>


class ThreadedCommand {

    std::shared_ptr<boost::process::child> threaded_process = nullptr;
    std::string threaded_cmd;

public:
    ThreadedCommand(std::string _cmd){
       threaded_cmd = _cmd;
    };

  void run_thread(){
    threaded_process = std::make_shared<boost::process::child>(threaded_cmd.c_str());
    std::cout << "Running new threaded command: " << threaded_cmd.c_str() << std::endl;
  }

  void start_thread(int sleep){
      std::thread new_thread(&ThreadedCommand::run_thread,this);
      new_thread.detach();
      std::this_thread::sleep_for(std::chrono::seconds(sleep));
  }

  void terminate_thread(){
      if(threaded_process && threaded_process->running()){
          threaded_process->terminate();
      }
      std::exit(0);
  }
};
