/*==============================================================================

    Mosaic: Live Visual Patching Creative-Coding Platform

    Copyright (c) 2018 Emanuele Mazza aka n3m3da <emanuelemazza@d3cod3.org>

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

#include "BaseTheme.h"
#include "ofMain.h"

class MosaicTheme : public ofxImGui::BaseTheme{

public:

    void setup() override;

    void fixForRetinaScreen();


    // TextInput ComboBox
    static bool identical(const char* buf, const char* item);
    static int propose(ImGuiInputTextCallbackData* data);

    static bool TextInputComboBox(const char* id, std::string& str, size_t maxInputSize, const char* items[], size_t item_len);
    static bool TextInputComboBox(const char* id, char* buffer, size_t maxInputSize, const char* items[], size_t item_len);

    static void drawDemoComboBox();
    static void drawMosaicLogDemo();

};

class MosaicLoggerChannel : public ofBaseLoggerChannel
{
public:

    ImVector<char*>     Items;
    bool                scrollToBottom;

    MosaicLoggerChannel() {
        scrollToBottom = true;
    }

    void log( ofLogLevel level, const std::string & module, const std::string & message ){
        std::ostringstream oss;
        oss << ofGetTimestampString("%H:%M:%S:%i") << " ";
        oss << "[" << ofGetLogLevelName(level, true) << "] ";
        if (module != "") {
            oss << module << ": ";
        }
        oss << message << endl;

        AddLog("%s\n", oss.str().c_str());
    }
    void log( ofLogLevel level, const std::string & module, const char* format, ... ) OF_PRINTF_ATTR( 4, 5 ){
        va_list args;
        va_start(args, format);
        log(level, module, format, args);
        va_end(args);
    }
    void log( ofLogLevel level, const std::string & module, const char* format, va_list args ){
        // Compose the message.
        std::ostringstream oss;
        oss << ofGetTimestampString("%H:%M:%S:%i") << " ";
        oss << "[" << ofGetLogLevelName(level, true) << "] ";
        if (module != "") {
            oss << module << ": ";
        }

        oss << ofVAArgsToString(format, args) << endl;

        AddLog("%s\n", oss.str().c_str());
    }

    void Clear()     {
        for (int i = 0; i < Items.Size; i++){
            free(Items[i]);
        }
        Items.clear();
    }

    void AddLog(const char* fmt, ...) IM_FMTARGS(2){
        char buf[1024];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
        buf[IM_ARRAYSIZE(buf)-1] = 0;
        va_end(args);
        Items.push_back(strdup(buf));
        scrollToBottom = true;
    }

    string GetLastLog() {
        if(Items.empty()) return std::string("");

        std::string str(Items.back());
        return str;
    }

    void Draw(const char* title, bool* active){

        if (!ImGui::Begin(title,active,ImGuiWindowFlags_NoCollapse))
        {
            ImGui::End();
            return;
        }
        if (ImGui::Button("Clear")) Clear();

        ImGui::Separator();
        if (ImGui::BeginChild("scrolling", ImVec2(0,0), false, ImGuiWindowFlags_HorizontalScrollbar) ){

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4,1)); // Tighten spacing

            ImVec4 col_default_text = ImGui::GetStyleColorVec4(ImGuiCol_Text);
            for (int i = 0; i < Items.Size; i++){
                const char* item = Items[i];
                ImVec4 col = col_default_text;
                if (strstr(item, "[notice")) col = ImGui::GetStyleColorVec4(ImGuiCol_Text);
                else if (strstr(item, "[warning")) col = ImColor(1.0f,0.5f,0.0f,1.0f);
                else if (strstr(item, "[ error")) col = ImColor(1.0f,0.176f,0.176f,1.0f);
                else if (strstr(item, "[silent")) col = ImColor(1.0f,0.78f,0.58f,1.0f);
                else if (strncmp(item, "# ", 2) == 0) col = ImColor(1.0f,0.78f,0.58f,1.0f);

                // force verbose
                if(strstr(item, "[verbose]")){
                    col = ImColor(0.235f,1.0f,0.235f,1.0f);
                }

                ImGui::PushStyleColor(ImGuiCol_Text, col);
                ImGui::TextUnformatted(item);
                ImGui::PopStyleColor();
            }

            if(scrollToBottom){
                scrollToBottom = false;
                ImGui::SetScrollHere(1.0f);
            }

            ImGui::PopStyleVar(1);

            ImGui::EndChild();
        }
        ImGui::End();
    }

};
