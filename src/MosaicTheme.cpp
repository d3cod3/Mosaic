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

// Some C64 retro stylin' (just in case)
#define C64_BLACK 	ImVec4(0,0,0,1)
#define C64_WHITE 	ImVec4(1,1,1,1)
#define C64_RED     ImVec4(136/255.0f,57/255.0f,50/255.0f,1.0f)
#define C64_CYAN 	ImVec4(103/255.0f,182/255.0f,189/255.0f,1.0f)
#define C64_PURPLE	ImVec4(139/255.0f,63/255.0f,150/255.0f,1.0f)
#define C64_GREEN	ImVec4(85/255.0f,160/255.0f,73/255.0f,1.0f)
#define C64_BLUE	ImVec4(64/255.0f,49/255.0f,141/255.0f,1.0f)
#define C64_YELLOW	ImVec4(191/255.0f,206/255.0f,114/255.0f,1.0f)
#define C64_ORANGE	ImVec4(139/255.0f,84/255.0f,41/255.0f,1.0f)
#define C64_BROWN	ImVec4(87/255.0f,66/255.0f,0/255.0f,1.0f)
#define C64_PINK	ImVec4(184/255.0f,105/255.0f,98/255.0f,1.0f)
#define C64_DGRAY	ImVec4(80/255.0f,80/255.0f,80/255.0f,1.0f)
#define C64_MGRAY	ImVec4(120/255.0f,120/255.0f,120/255.0f,1.0f)
#define C64_LGREEN	ImVec4(148/255.0f,224/255.0f,137/255.0f,1.0f)
#define C64_LBLUE 	ImVec4(120/255.0f,105/255.0f,196/255.0f,1.0f)
#define C64_LGRAY 	ImVec4(159/255.0f,159/255.0f,159/255.0f,1.0f)


void MosaicTheme::setup(){
    ofColor col_main_text = ofColor::fromHex(0xededed);
    ofColor col_main_head = ofColor::fromHex(0x404040);
    ofColor col_main_area = ofColor::fromHex(0x222222);
    ofColor col_win_popup = ofColor::fromHex(0xd1d1d1);
    ofColor col_win_backg = ofColor::fromHex(0x2b2b2b);
    ofColor col_win_detail = ofColor::fromHex(0x3B445B);


    ImGuiStyle* style = &ImGui::GetStyle();

    style->Alpha                       = 1.0f;  // Global alpha applies to everything in Dear ImGui.
    style->WindowPadding               = ImVec2(8, 8);  // Padding within a window.
    style->WindowRounding              = 4.0f;  // Radius of window corners rounding. Set to 0.0f to have rectangular windows. Large values tend to lead to variety of artifacts and are not recommended.
    style->WindowBorderSize            = 0.0f;  // Thickness of border around windows. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly).
    style->WindowMinSize               = ImVec2(160, 70);  // Minimum window size. This is a global setting. If you want to constraint individual windows, use SetNextWindowSizeConstraints().
    //style->WindowTitleAlign            = ;  // Alignment for title bar text. Defaults to (0.0f,0.5f) for left-aligned,vertically centered.
    //style->WindowMenuButtonPosition    = ;  // Side of the collapsing/docking button in the title bar (None/Left/Right). Defaults to ImGuiDir_Left.
    //style->ChildRounding               = ;  // Radius of child window corners rounding. Set to 0.0f to have rectangular windows.
    style->ChildBorderSize             = 0.0f;  // Thickness of border around child windows. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly).
    style->PopupRounding               = 0.0f;  // Radius of popup window corners rounding. (Note that tooltip windows use WindowRounding)
    style->PopupBorderSize             = 0.0f;  // Thickness of border around popup/tooltip windows. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly).
    style->FramePadding                = ImVec2(4, 6);  // Padding within a framed rectangle (used by most widgets).
    style->FrameRounding               = 0.0f;  // Radius of frame corners rounding. Set to 0.0f to have rectangular frame (used by most widgets).
    style->FrameBorderSize             = 0.0f;  // Thickness of border around frames. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly).
    style->ItemSpacing                 = ImVec2(8, 2);  // Horizontal and vertical spacing between widgets/lines.
    style->ItemInnerSpacing            = ImVec2(6, 4);  // Horizontal and vertical spacing between within elements of a composed widget (e.g. a slider and its label).
    //style->CellPadding                 = ;  // Padding within a table cell
    //style->TouchExtraPadding           = ;  // Expand reactive bounding box for touch-based system where touch position is not accurate enough. Unfortunately we don't sort widgets so priority on overlap will always be given to the first widget. So don't grow this too much!
    style->IndentSpacing               = 6.0f;  // Horizontal indentation when e.g. entering a tree node. Generally == (FontSize + FramePadding.x*2).
    style->ColumnsMinSpacing           = 50.0f;  // Minimum horizontal spacing between two columns. Preferably > (FramePadding.x + 1).
    style->ScrollbarSize               = 14.0f;  // Width of the vertical scrollbar, Height of the horizontal scrollbar.
    style->ScrollbarRounding           = 4.0f;  // Radius of grab corners for scrollbar.
    style->GrabMinSize                 = 14.0f;  // Minimum width/height of a grab box for slider/scrollbar.
    style->GrabRounding                = 0.0f;  // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
    //style->LogSliderDeadzone           = ;  // The size in pixels of the dead-zone around zero on logarithmic sliders that cross zero.
    style->TabRounding                 = 0.0f;  // Radius of upper corners of a tab. Set to 0.0f to have rectangular tabs.
    style->TabBorderSize               = 0.0f;  // Thickness of border around tabs.
    //style->TabMinWidthForCloseButton   = ;  // Minimum width for close button to appears on an unselected tab when hovered. Set to 0.0f to always show when hovering, set to FLT_MAX to never show close button unless selected.
    //style->ColorButtonPosition         = ;  // Side of the color button in the ColorEdit4 widget (left/right). Defaults to ImGuiDir_Right.
    //style->ButtonTextAlign             = ;  // Alignment of button text when button is larger than text. Defaults to (0.5f, 0.5f) (centered).
    //style->SelectableTextAlign         = ;  // Alignment of selectable text. Defaults to (0.0f, 0.0f) (top-left aligned). It's generally important to keep this left-aligned if you want to lay multiple items on a same line.
    //style->DisplayWindowPadding        = ;  // Window position are clamped to be visible within the display area or monitors by at least this amount. Only applies to regular windows.
    //style->DisplaySafeAreaPadding      = ;  // If you cannot see the edges of your screen (e.g. on a TV) increase the safe area padding. Apply to popups/tooltips as well regular windows. NB: Prefer configuring your TV sets correctly!
    //style->MouseCursorScale            = ;  // Scale software rendered mouse cursor (when io.MouseDrawCursor is enabled). We apply per-monitor DPI scaling over this scale. May be removed later.
    //style->AntiAliasedLines            = ;  // Enable anti-aliased lines/borders. Disable if you are really tight on CPU/GPU. Latched at the beginning of the frame (copied to ImDrawList).
    //style->AntiAliasedLinesUseTex      = ;  // Enable anti-aliased lines/borders using textures where possible. Require backend to render with bilinear filtering. Latched at the beginning of the frame (copied to ImDrawList).
    //style->AntiAliasedFill             = ;  // Enable anti-aliased edges around filled shapes (rounded rectangles, circles, etc.). Disable if you are really tight on CPU/GPU. Latched at the beginning of the frame (copied to ImDrawList).
    //style->CurveTessellationTol        = ;  // Tessellation tolerance when using PathBezierCurveTo() without a specific number of segments. Decrease for highly tessellated curves (higher quality, more polygons), increase to reduce quality.
    //style->CircleTessellationMaxError  = ;  // Maximum error (in pixels) allowed when using AddCircle()/AddCircleFilled() or drawing rounded corner rectangles with no explicit segment count specified. Decrease for higher quality but more geometry.

    style->Colors[ImGuiCol_Text] = ImVec4(col_main_text, 1.00f);
    style->Colors[ImGuiCol_TextDisabled] = ImVec4(col_main_text, 0.58f);
    style->Colors[ImGuiCol_WindowBg] = ImVec4(col_win_backg, 0.70f);
    style->Colors[ImGuiCol_ChildBg] = ImVec4(col_main_area, 0.58f);
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
    style->Colors[ImGuiCol_ResizeGrip] = ImVec4(col_win_popup, 0.20f);
    style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(col_win_popup, 0.60f);
    style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(col_win_popup, 0.80f);
    style->Colors[ImGuiCol_PlotLines] = ImVec4(col_main_text, 0.63f);
    style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(col_main_head, 1.00f);
    style->Colors[ImGuiCol_PlotHistogram] = ImVec4(col_main_text, 0.63f);
    style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(col_main_head, 1.00f);
    style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(col_win_popup, 0.9f);
    style->Colors[ImGuiCol_PopupBg] = ImVec4(col_win_backg, 0.92f);
    style->Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(col_main_area, 0.0f);
    style->Colors[ImGuiCol_Separator] = ImVec4(col_main_head, 0.73f);
    style->Colors[ImGuiCol_SeparatorHovered] = ImVec4(col_main_head, 0.f);
    style->Colors[ImGuiCol_SeparatorActive] = ImVec4(col_main_head, 0.f);
    style->Colors[ImGuiCol_DragDropTarget] = ImVec4(col_main_head, 0.8f);
    style->Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(col_main_head, 0.f);
    style->Colors[ImGuiCol_Tab] = ImVec4(col_main_area, 0.9f);
    style->Colors[ImGuiCol_TabDimmed] = ImVec4(col_main_area, 0.3f);
    style->Colors[ImGuiCol_TabDimmedSelected] = ImVec4(col_main_area, 0.3f);
    style->Colors[ImGuiCol_TabHovered] = ImVec4(col_win_detail, 0.9f);
    style->Colors[ImGuiCol_TabSelectedOverline] = ImVec4(col_win_detail, 0.7f);
    style->Colors[ImGuiCol_TabDimmedSelectedOverline] = ImVec4(col_main_area, 0.3f);
    style->Colors[ImGuiCol_TabSelected] = ImVec4(col_win_detail, 0.7f);


    // New colors to be customized
    //style->Colors[ImGuiCol_TabUnfocused]            = ImVec4();
    //style->Colors[ImGuiCol_TabUnfocusedActive]      = ImVec4();
    style->Colors[ImGuiCol_DockingPreview]          = ImVec4(col_main_head, .7f);
    style->Colors[ImGuiCol_DockingEmptyBg]          = ImVec4(col_main_head, .0f);
    //style->Colors[ImGuiCol_TableHeaderBg]           = ImVec4();
    //style->Colors[ImGuiCol_TableBorderStrong]       = ImVec4();
    //style->Colors[ImGuiCol_TableBorderLight]        = ImVec4();
    //style->Colors[ImGuiCol_TableRowBg]              = ImVec4();
    //style->Colors[ImGuiCol_TableRowBgAlt]           = ImVec4();

}

//--------------------------------------------------------------
void MosaicTheme::fixForRetinaScreen(){
    ImGuiStyle* style = &ImGui::GetStyle();

    style->WindowMinSize = ImVec2(320, 140);
    style->WindowPadding = ImVec2(16, 16);
    style->FramePadding = ImVec2(8, 12);
    style->ItemSpacing = ImVec2(16, 4);
    style->ItemInnerSpacing = ImVec2(12, 8);
    style->IndentSpacing = 12.0f;
    style->ColumnsMinSpacing = 100.0f;
    style->GrabMinSize = 28.0f;
    style->ScrollbarSize = 28.0f;
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

        log.Draw("Example: Log",0);
}
