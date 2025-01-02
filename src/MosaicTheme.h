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

#include "TextEditor.h"
#include "imgui_stdlib.h"

struct MosaicCommand{
    std::string command;
    std::string description;
};

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

    ImVector<char*>             Items;
    TextEditor                  console;

    bool                        scrollToBottom;
    bool                        recoverFocus;
    bool                        isOverLogger;
    std::string                 log_command;
    float                       retinaScale;

    ofEvent<std::string>        commandEvent;

    MosaicLoggerChannel() {
        scrollToBottom = true;
        recoverFocus = false;
        log_command = "";
        retinaScale = 1.0f;

        console.SetShowWhitespaces(false);
        console.SetText("");
        console.SetReadOnly(true);
        console.SetShowLineNumbers(false);
        console.SetPalette(TextEditor::GetConsolePalette());
        console.SetLanguageDefinition(TextEditor::LanguageDefinition::SimpleConsole());
    }

    void setRetinaScale(float s){
        retinaScale = s;
    }

    void setCommand(string comm){
        log_command = comm;
    }

    void log( ofLogLevel level, const std::string & module, const std::string & message ){
        std::ostringstream oss;
        oss << ofGetTimestampString("%H:%M:%S:%i") << " ";
        if(ofGetLogLevelName(level, true) != "notice "){
            oss << "[" << ofGetLogLevelName(level, true) << "] ";
        }
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
        if(ofGetLogLevelName(level, true) != "notice "){
            oss << "[" << ofGetLogLevelName(level, true) << "] ";
        }
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

        console.SetText("");
    }

    void AddLog(const char* fmt, ...) IM_FMTARGS(2){
        char buf[1024];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
        buf[IM_ARRAYSIZE(buf)-1] = 0;
        va_end(args);
        Items.push_back(strdup(buf));
        console.InsertText(strdup(buf));
        scrollToBottom = true;
    }

    string GetLastLog() {
        if(Items.empty()) return std::string("");

        std::string str(Items.back());
        return str;
    }

    void Draw(const char* title, bool* active){

        if (ImGui::Begin(title,active,ImGuiWindowFlags_NoCollapse)){

            isOverLogger = ImGui::IsWindowHovered(ImGuiHoveredFlags_RootWindow) || ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows);

            if (ImGui::Button("Clear")) Clear();

            ImGui::Separator();
            if (ImGui::BeginChild("scrolling", ImVec2(0,0), false, ImGuiWindowFlags_HorizontalScrollbar) ){

                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4,1)); // Tighten spacing

                ImVec4 col_default_text = ImGui::GetStyleColorVec4(ImGuiCol_Text);

                console.Render("Console",ImVec2(-1.0, -36*retinaScale));
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();

                if(recoverFocus){
                    recoverFocus = false;
                    ImGui::SetKeyboardFocusHere();
                }
                ImGui::PushStyleColor(ImGuiCol_TextSelectedBg,ImVec4(1,1,1,0.05));
                ImGui::PushItemWidth(-1);
                if(ImGui::InputTextWithHint("###command","Send a command...",&log_command,ImGuiInputTextFlags_EnterReturnsTrue)){
                    if(log_command != ""){
                        ofNotifyEvent(commandEvent,log_command);
                    }
                    // clear previuos command
                    log_command = "";
                    // focus on input command again
                    ImGui::SetKeyboardFocusHere(-1);
                }
                ImGui::PopItemWidth();
                ImGui::PopStyleColor();


                if(scrollToBottom){
                    scrollToBottom = false;
                    ImGui::SetScrollHereY(1.0f);
                }

                ImGui::PopStyleVar(1);

            }

            ImGui::EndChild();

            ImGui::End();

        }
    }

};

/**************************************************************************************/
/* original code from braitsch: https://github.com/braitsch/ofxParagraph */

class ofxParagraph{

public:

    enum Alignment
    {
        ALIGN_LEFT = 1,
        ALIGN_CENTER = 2,
        ALIGN_RIGHT = 3
    };

    ofxParagraph(){
        mIndent = 40;
        mSpacing = 6;
        mLeading = 16;
        mBorderPadding = 15;
        mMaxLines = 2;

        setText("");
        setAlignment(ALIGN_LEFT);
        setWidth(ofGetWindowWidth());
    }

    int x;
    int y;

    void setText(std::string text){
        mText = trim(text);
        render();
    }

    void init(std::string fontfile, float fontsize){
        mFont.load(fontfile,fontsize,true,true);
    }

    void setWidth(int width){
        mWidth = width;
        render();
    }
    void setIndent(int indent){
        mIndent = indent;
        render();
    }
    void setPosition(int x, int y){
        this->x = x;
        this->y = y;
    }
    void setAlignment(Alignment align){
        mAlignment = align;
        render();
    }
    void setSpacing(int spacing){
        mSpacing = spacing;
        render();
    }
    void setLeading(int leading){
        mLeading = leading;
        render();
    }
    void setBorderPadding(int padding){
        mBorderPadding = padding;
    }

    void setMaxLines(int ml){
        mMaxLines = ml;
    }

    int getWidth() { return mWidth; }
    int getHeight() { return mHeight; }

    void draw(){
        for (int i=0; i<mWords.size(); i++) {
            mFont.drawString(mWords[i].text, this->x + mWords[i].rect.x, this->y + mWords[i].rect.y);
        }
    }
    void draw(int x, int y){
        this->x = x;
        this->y = y;
        draw();
    }

private:

    int mWidth;
    int mHeight;
    int mIndent;
    int mLeading;
    int mSpacing;
    int mLineHeight;
    int mMaxLines;
    std::string mText;
    Alignment mAlignment;

    ofTrueTypeFont mFont;
    int mBorderPadding;

    struct word {
        std::string text;
        ofRectangle rect;
    };

    std::vector< word > mWords;
    std::vector< std::vector<word*> > mLines;

    void render(){
        mWords.clear();
        mLineHeight = 0;
        std::string str = mText;

        // break paragraph into words //
        int position = str.find(" ");
        while ( position != std::string::npos )
        {
            std::string s = str.substr(0, position);
            word w = {s, mFont.getStringBoundingBox(s,0,0)};
            mWords.push_back(w);
            str.erase(0, position + 1);
            position = str.find(" ");
            if (w.rect.height > mLineHeight) mLineHeight = w.rect.height;
        }
        // append the last word //
        word w = {str, mFont.getStringBoundingBox(str,0,0)};
        mWords.push_back(w);
        if (w.rect.height > mLineHeight) mLineHeight = w.rect.height;

        // assign words to lines //
        int y = 0;
        int x = mAlignment == ALIGN_LEFT ? mIndent : 0;
        mLines.clear();
        std::vector<word*> line;
        for (int i=0; i<mWords.size(); i++) {
            if (x + mWords[i].rect.width < mWidth){
                mWords[i].rect.x = x;
                mWords[i].rect.y = y;
                x += mWords[i].rect.width + mSpacing;
                line.push_back(&mWords[i]);
            }   else{
                if (line.size() > 0 ) y+= mLineHeight + mLeading;
                mWords[i].rect.x = 0;
                mWords[i].rect.y = y;
                x = mWords[i].rect.width + mSpacing;
                if (line.size() > 0) mLines.push_back(line);
                line.clear();
                line.push_back(&mWords[i]);
            }
        }
        // append the last line //
        if(mLines.size() < mMaxLines-1){
            mLines.push_back(line);
        }
        mHeight = mLines.size() * (mLineHeight + mLeading);

        // reposition words for right & center aligned paragraphs //
        if (mAlignment == ALIGN_CENTER){
            for(int i=0; i<mLines.size(); i++) {
                int lineWidth = 0;
                for(int j=0; j<mLines[i].size(); j++) {
                    lineWidth+= mLines[i][j]->rect.width;
                }
                lineWidth+= mSpacing * (mLines[i].size()-1);
                // calculate the amount each word should move over //
                int offset = (mWidth - lineWidth) / 2;
                for(int j=0; j<mLines[i].size(); j++) mLines[i][j]->rect.x += offset;
            }
        }   else if (mAlignment == ALIGN_RIGHT){
            for(int i=0; i<mLines.size(); i++) {
                word* lword = mLines[i].back();
                // calculate the distance the last word in each line is from the right boundary //
                int offset = mWidth - (lword->rect.x + lword->rect.width);
                for(int j=0; j<mLines[i].size(); j++) mLines[i][j]->rect.x += offset;
            }
        }
    }

    static inline std::string &trim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](char c) {return !isspace(c); }));
        s.erase(std::find_if(s.rbegin(), s.rend(), [](char c) {return !isspace(c); }).base(), s.end());
        return s;
    }


};
/**************************************************************************************/
