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

#include "MosaicTheme.h"

void MosaicTheme::setup(){
    ofColor col_main_text = ofColor::fromHex(0xededed);
    ofColor col_main_head = ofColor::fromHex(0x404040);
    ofColor col_main_area = ofColor::fromHex(0x222222);
    ofColor col_win_popup = ofColor::fromHex(0xd1d1d1);
    ofColor col_win_backg = ofColor::fromHex(0x2b2b2b);

    ImGuiStyle* style = &ImGui::GetStyle();

    style->WindowMinSize = ImVec2(160, 65);
    style->FramePadding = ImVec2(4, 2);
    style->ItemSpacing = ImVec2(6, 2);
    style->ItemInnerSpacing = ImVec2(6, 4);
    style->Alpha = 1.0f;
    style->WindowRounding = 0.0f;
    style->FrameRounding = 0.0f;
    style->IndentSpacing = 6.0f;
    style->ItemInnerSpacing = ImVec2(2, 4);
    style->ColumnsMinSpacing = 50.0f;
    style->GrabMinSize = 14.0f;
    style->GrabRounding = 0.0f;
    style->ScrollbarSize = 12.0f;
    style->ScrollbarRounding = 0.0f;

    style->Colors[ImGuiCol_Text] = ImVec4(col_main_text, 1.00f);
    style->Colors[ImGuiCol_TextDisabled] = ImVec4(col_main_text, 0.58f);
    style->Colors[ImGuiCol_WindowBg] = ImVec4(col_win_backg, 0.70f);
    style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(col_main_area, 0.58f);
    style->Colors[ImGuiCol_Border] = ImVec4(col_win_backg, 0.00f);
    style->Colors[ImGuiCol_BorderShadow] = ImVec4(col_win_backg, 0.00f);
    style->Colors[ImGuiCol_FrameBg] = ImVec4(col_main_area, 1.00f);
    style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(col_main_head, 0.78f);
    style->Colors[ImGuiCol_FrameBgActive] = ImVec4(col_main_head, 1.00f);
    style->Colors[ImGuiCol_TitleBg] = ImVec4(col_main_area, 1.00f);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(col_main_area, 0.75f);
    style->Colors[ImGuiCol_TitleBgActive] = ImVec4(col_main_head, 1.00f);
    style->Colors[ImGuiCol_MenuBarBg] = ImVec4(col_main_area, 0.47f);
    style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(col_main_area, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(col_win_popup, 0.21f);
    style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(col_main_head, 0.78f);
    style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(col_main_head, 1.00f);
    style->Colors[ImGuiCol_CheckMark] = ImVec4(ofColor::fromHex(0xaaaaaa), 0.80f);
    style->Colors[ImGuiCol_SliderGrab] = ImVec4(col_win_popup, 0.14f);
    style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(col_main_head, 1.00f);
    style->Colors[ImGuiCol_Button] = ImVec4(col_win_popup, 0.14f);
    style->Colors[ImGuiCol_ButtonHovered] = ImVec4(col_main_head, 0.86f);
    style->Colors[ImGuiCol_ButtonActive] = ImVec4(col_main_head, 1.00f);
    style->Colors[ImGuiCol_Header] = ImVec4(col_main_head, 0.76f);
    style->Colors[ImGuiCol_HeaderHovered] = ImVec4(col_main_head, 0.86f);
    style->Colors[ImGuiCol_HeaderActive] = ImVec4(col_main_head, 1.00f);
    style->Colors[ImGuiCol_ResizeGrip] = ImVec4(col_win_popup, 0.04f);
    style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(col_main_head, 0.78f);
    style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(col_main_head, 1.00f);
    style->Colors[ImGuiCol_PlotLines] = ImVec4(col_main_text, 0.63f);
    style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(col_main_head, 1.00f);
    style->Colors[ImGuiCol_PlotHistogram] = ImVec4(col_main_text, 0.63f);
    style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(col_main_head, 1.00f);
    style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(col_main_head, 0.43f);
    style->Colors[ImGuiCol_PopupBg] = ImVec4(col_win_backg, 0.92f);
    style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(col_main_area, 0.73f);

}

//--------------------------------------------------------------
bool MosaicTheme::identical(const char* buf, const char* item){
    size_t buf_size = strlen(buf);
    size_t item_size = strlen(item);
    //Check if the item length is shorter or equal --> exclude
    if (buf_size >= item_size) return false;
    for (int i = 0; i < strlen(buf); ++i)
        // set the current pos if matching or return the pos if not
        if (buf[i] != item[i]) return false;
    // Complete match
    // and the item size is greater --> include
    return true;
}

//--------------------------------------------------------------
int MosaicTheme::propose(ImGuiInputTextCallbackData* data){
    //We don't want to "preselect" anything
    if (strlen(data->Buf) == 0) return 0;

    //Get our items back
    const char** items = static_cast<std::pair<const char**, size_t>*> (data->UserData)->first;
    size_t length = static_cast<std::pair<const char**, size_t>*> (data->UserData)->second;

    //We need to give the user a chance to remove wrong input
    if (ofGetKeyPressed(OF_KEY_BACKSPACE)) {
        //We delete the last char automatically
        if (data->SelectionEnd != data->SelectionStart)
            if (data->BufTextLen > 0) //...and the buffer isn't empty
                if (data->CursorPos > 0) //...and the cursor not at pos 0
                    data->DeleteChars(data->CursorPos - 1, 1);
        return 0;
    }

    if(ofGetKeyPressed(OF_KEY_TAB)){
        for (int i = 0; i < length; i++) {
            if (identical(data->Buf, items[i])) {
                const int cursor = data->CursorPos;
                //Insert the first match
                data->DeleteChars(0, data->BufTextLen);
                data->InsertChars(0, items[i]);
                //Reset the cursor position
                //data->CursorPos = cursor;
                //Select the text, so the user can simply go on writing
                data->SelectionStart = cursor;
                data->SelectionEnd = data->BufTextLen;
                break;
            }
        }
    }

    if(ofGetKeyPressed(OF_KEY_RETURN) || ofGetKeyPressed(OF_KEY_DEL)) data->DeleteChars(0, data->BufTextLen); // ofGetKeyPressed(OF_KEY_BACKSPACE) ||

    return 0;
}

//--------------------------------------------------------------
bool MosaicTheme::TextInputComboBox(const char* id, std::string& str, size_t maxInputSize, const char* items[], size_t item_len){
    if (str.size() > maxInputSize) { // too large for editing
        return false;
    }

    std::string buffer(str);
    buffer.resize(maxInputSize);
    bool changed = MosaicTheme::TextInputComboBox(id, &buffer[0], maxInputSize, items, item_len);
    // using string as char array
    if (changed) {
        auto i = buffer.find_first_of('\0');
        str = buffer.substr(0u, i);
    }
    return changed;
}

//--------------------------------------------------------------
bool MosaicTheme::TextInputComboBox(const char* id, char* buffer, size_t maxInputSize, const char* items[], size_t item_len){

    ImGui::PushID(id);
    std::pair<const char**, size_t> pass(items, item_len); //We need to pass the array length as well

    bool ret = ImGui::InputText(" search", buffer, maxInputSize, ImGuiInputTextFlags_::ImGuiInputTextFlags_CallbackAlways, propose, static_cast<void*>(&pass));

    /*ImGui::BeginChild("Options");
    for(int i = 0; i < item_len; i++){
        if (ImGui::Selectable(items[i])){
            strcpy(buffer, items[i]);
        }
    }
    ImGui::EndChild();*/
    ImGui::PopID();

    return ret;
}

//--------------------------------------------------------------
void MosaicTheme::drawDemoComboBox(){
    ImGui::Begin("Combobox");
        static std::string buffer;
        const char* items[] = {"video player", "soundfile player", "bang", "trigger", "floats to vector", "slider", "lua script"};
        MosaicTheme::TextInputComboBox("Objects", buffer, 20, items, IM_ARRAYSIZE(items));
    ImGui::End();
}

//--------------------------------------------------------------
void MosaicTheme::drawMosaicLogDemo(){
        static MosaicLoggerChannel log;

        // Demo: add random items (unless Ctrl is held)
        static double last_time = -1.0;
        double time = ImGui::GetTime();
        if (time - last_time >= 0.20f && !ImGui::GetIO().KeyCtrl)
        {
            const char* random_words[] = { "system", "info", "warning", "error", "fatal", "notice", "log" };
            log.AddLog("[%s] Hello, time is %.1f, frame count is %d\n", random_words[rand() % IM_ARRAYSIZE(random_words)], time, ImGui::GetFrameCount());
            last_time = time;
        }

        log.Draw("Example: Log");
}
