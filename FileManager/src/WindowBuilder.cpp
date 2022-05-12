#pragma execution_character_set("utf-8")
#include <iostream>
#include <string>
#include <vector>
#include "WindowBuilder.h"
#include "Window.h"
#include "imgui.h"
#include "imgui_impl_glut.h"

// #include "imgui_impl_opengl2.h"
#include <GL/freeglut.h>
#include "settings.h"
// #include "icons.h"
#include "IconsFontAwesome4.h"
#include "font.h"
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include "Console.h"
#include <unistd.h>

void get_user(char* buff, size_t buffsize) {
    getlogin_r(buff, buffsize);
}

int a = -1;
bool isclicked = false;
std::string name_of_the_button_clicked = "";
std::string new_dir = "";
std::string str_username;
std::string current_path;
std::vector<std::string> cur_dir_list = std::vector<std::string>(0);
std::map<std::string, std::string> cur_dirs;
int cur_index = 0;
bool selects[10000];
Console* console = nullptr;
bool WindowBuilder::is_new_file_clicked = false;
bool DialogWindow::is_new_file_window_created = false;
bool WindowBuilder::is_new_folder_clicked = false;
bool DialogWindow::is_new_folder_window_created = false;
bool DialogWindow::is_open_folder_window_created = false;
bool WindowBuilder::is_open_folder_clicked = false;
bool WindowWithFiles::is_window_with_files_created = false;
WindowBuilder::WindowBuilder() {}



Window* WindowBuilder::build(const std::string& type, const std::string& blabla) {
    if(type == "main") {
        MainWindowBuilder main_window_builder;
        return main_window_builder.build(type, blabla);
    }
}

// TextInfo

TextInfoWindowBuilder::TextInfoWindowBuilder() {

}

Window* TextInfoWindowBuilder::build(const std::string& name, const std::string& param) {
    /*ImGuiStyle* style = &ImGui::GetStyle();
    ImGui::Begin(name.c_str());
    style->WindowMinSize = ImVec2(50, 50);
    ImGui::Text("jvdsjvnsjnv");
    ImGui::End();*/
}

void TextInfoWindowBuilder::set_text(std::string text) {

}

//  Main Window

MainWindowBuilder::MainWindowBuilder() = default;


void MainWindowBuilder::add_files_list(std::string path_name, std::string folder_name) {
    ImGui::Begin("File explorer");
    ImGuiStyle& style = ImGui::GetStyle();
    static bool show_hidden = false;
    ImVec2 pw_size = ImGui::GetWindowSize();
    bool show_error = false;
    float list_item_height = ImGui::CalcTextSize("").y + style.ItemSpacing.y;
    float input_bar_ypos = pw_size.y - ImGui::GetFrameHeightWithSpacing() * 2.5f - style.WindowPadding.y;
    float window_height = input_bar_ypos - ImGui::GetCursorPosY() - style.ItemSpacing.y;
    float window_width = pw_size.x - ImGui::GetCursorPosX();
    float window_content_height = window_height - style.WindowPadding.y * 2.0f;
    float min_content_size = pw_size.x - style.WindowPadding.x * 4.0f;
    ImGui::BeginChild("##Files list", ImVec2(0, window_height), true);
    if(cur_dirs.empty()) {
        cur_dirs[path_name] = folder_name;
    }
    ImGui::EndChild();
    std::map<std::string, std::string> copy = cur_dirs;
    std::map<std::string, std::string>::iterator it1;
    ImGui::BeginChild("##Files list", ImVec2(0, window_height), true);
    static ImGuiTextFilter filter;
    filter.Draw("##seach bar", 500);
    ImGui::SameLine(530);
    static bool selection_mode = false;
    ImGui::Checkbox("Selection mode", &selection_mode);
    
    if(ImGui::BeginTabBar("MyTabBar")) {
        ImGui::Spacing();
        for(it1 = copy.begin(); it1 != copy.end(); ++it1) {
            bool open = true;
            if(ImGui::BeginTabItem((it1->second).c_str(), &open)) {
                boost::filesystem::path dir = (it1->first);
                FileSystemItem fsi;
                std::map<std::string, std::string> dirs = fsi.get_dirs(it1->first);
                std::map<std::string, std::string> files = fsi.get_files(it1->first);
                std::map<std::string, std::string>::iterator it2;
                static bool is_selected[10000];          
                size_t counter = 0;
                for(it2 = dirs.begin(); it2 != dirs.end(); ++it2) {
                    if(filter.PassFilter((it2->second).c_str())) {
                        if(!show_hidden && it2->second[0] == '.') {
                            continue;
                        }
                        if(ImGui::Selectable((ICON_FA_FOLDER + (" " + it2->second)).c_str(), &is_selected[counter], 0, ImVec2(0, 0))) {
                            current_path = it1->first;
                            if(!selection_mode) {
                                is_selected[counter] = !is_selected[counter];
                                cur_dir_list.push_back(it2->second);
                                cur_dirs[it2->first] = it2->second;
                            }
                        }
                        ImGui::Spacing();
                        ++counter;
                    }
                } 
                
                for(it2 = files.begin(); it2 != files.end(); ++it2) {
                    if(filter.PassFilter((it2->first).c_str())) {
                        if(ImGui::Selectable((ICON_FA_FILE + (" " + it2->second)).c_str(), &is_selected[counter], ImGuiSelectableFlags_AllowDoubleClick)) {
                            
                            if(!selection_mode) {
                                is_selected[counter] = !is_selected[counter];
                                File new_file(it2->first);
                                    // ++counter;          
                                if(new_file.is_executable()) {
                                    new_file.execute();
                                } else {
                                    new_file.open();
                                }
                            }
                            
                        }
                        ImGui::Spacing();
                        ++counter;
                    }
                }
                ImGui::EndTabItem();
            }
            if(!open) {
                cur_dirs.erase((it1->first));
            }
        }
        ImGui::EndTabBar();
    }
    ImGui::EndChild();
    
    ImGui::Checkbox("Show hidden files and directories", &show_hidden);
    ImGui::End();
}

Window* MainWindowBuilder::build(const std::string& name, const std::string& p) {
    char buffer_username[80];
    getlogin_r(buffer_username, 80);
    str_username = std::string(buffer_username);
    current_path = "/home/" + str_username + "/";
    
    ImVec2 pos (400, 400);
    ImVec2 size(915, 455);
    ImGuiStyle* style = &ImGui::GetStyle();
    
    /*ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontDefault();*/
    // ImGuiIO& io = ImGui::GetIO();

    // (ImGui::GetIO()).Fonts->AddFontFromFileTTF("./arial.ttf", 20, NULL, (ImGui::GetIO()).Fonts->GetGlyphRangesCyrillic());
    bool fl = false;
    ImGui::SetNextWindowSize(ImVec2(930, 430));
    ImGui::Begin("File explorer", nullptr); 

    style->WindowTitleAlign = ImVec2(0.5, 0.5);
    style->FramePadding = ImVec2(8, 4);
    // style->WindowMinSize = ImVec2(930, 430);
    style->Colors[ImGuiCol_TitleBg] = ImColor(255, 120, 53, 255);
    style->Colors[ImGuiCol_TitleBgActive] = ImColor(255, 120, 53, 255);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(255, 120, 53, 255);
    style->Colors[ImGuiCol_Button] = ImColor(31, 30, 31, 255);
    style->Colors[ImGuiCol_ButtonActive] = ImColor(31, 30, 31, 255);
    style->Colors[ImGuiCol_ButtonHovered] = ImColor(41, 40, 41, 255);
    style->Colors[ImGuiCol_Separator] = ImColor(70, 70, 70, 255);
    style->Colors[ImGuiCol_SeparatorActive] = ImColor(70, 70, 70, 255);
    style->Colors[ImGuiCol_SeparatorHovered] = ImColor(100, 100, 100, 255);
    
    ImGui::End();
    add_main_menu();
    
    ImGui::Begin("File explorer");
    ImGui::Columns(2);
    ImGui::SetColumnOffset(1, 230);
    ImGuiIO& io = ImGui::GetIO();
    
    
    {
        if(ImGui::Button(ICON_FA_HOME " Home", ImVec2(230 - 15, 41))) {
            current_path = "/home/" + str_username + "/";
            cur_dirs.clear();
            Settings::Tab = 1;
        }
        ImGui::Spacing();
        if(ImGui::Button(ICON_FA_FILE_TEXT_O " Documents", ImVec2(230 - 15, 41))) {
            current_path = "/home/" + str_username + "/Documents/";
            cur_dirs.clear();
            Settings::Tab = 2;
        }
        ImGui::Spacing();
        if(ImGui::Button(ICON_FA_DOWNLOAD " Downloads", ImVec2(230 - 15, 41))) {
            current_path = "/home/" + str_username + "/Downloads/";
            cur_dirs.clear();
            Settings::Tab = 3;
        }
        ImGui::Spacing();
        if(ImGui::Button(ICON_FA_MUSIC " Music", ImVec2(230 - 15, 41))) {
            current_path = "/home/" + str_username + "/Music/";
            cur_dirs.clear();
            Settings::Tab = 4;
        }
        ImGui::Spacing();
        if(ImGui::Button(ICON_FA_PICTURE_O " Pictures", ImVec2(230 - 15, 41))) {
            current_path = "/home/" + str_username + "/Pictures/";
            cur_dirs.clear();
            Settings::Tab = 5;
        }
        ImGui::Spacing();
        if(ImGui::Button(ICON_FA_VIDEO_CAMERA " Videos", ImVec2(230 - 15, 41))) {
            current_path = "/home/" + str_username + "/Videos/";
            cur_dirs.clear();
            Settings::Tab = 6;
        }
        ImGui::Spacing();
        if(ImGui::Button(ICON_FA_TRASH " Trash", ImVec2(230 - 15, 41))) {
            cur_dirs.clear();
            Settings::Tab = 7;
        }
        ImGui::Spacing();
    }

    ImGui::NextColumn();

    {
        if (Settings::Tab == 1) {
            add_files_list("/home/" + str_username + "/", str_username);
        }
        if (Settings::Tab == 2) {
            add_files_list("/home/" + str_username + "/Documents/", "Documents");
        }
        if(Settings::Tab == 3) {
            add_files_list("/home/" + str_username + "/Downloads/", "Downloads");
        }
        if(Settings::Tab == 4) {
            add_files_list("/home/" + str_username + "/Music/", "Music");
        }
        if(Settings::Tab == 5) {
            add_files_list("/home/" + str_username + "/Pictures/", "Pictures");
        }
        if(Settings::Tab == 6) {
            add_files_list("/home/" + str_username + "/Videos/", "Videos");
        }
        
    }
    ImGui::End();
    result = new MainWindow("File explorer");
    // MainWindow main_window("File explorer");
    return result;
}



Window* wind = nullptr;
Window* wind2 = nullptr;
Window* wind3 = nullptr;
Window* wind4 = nullptr;
bool* console_opened;
std::map<std::string, std::string> current_dirs;
std::vector<std::string> current_dir_list;

void MainWindowBuilder::add_main_menu() {
    static bool show_app_console = false;
    static bool show_window_with_files = false;
    static std::string p;
    static std::string true_path = "";
    static DialogWindowBuilder dialog_builder;
    static WindowWithFilesBuilder wf_builder;
    ImGui::Begin("File explorer");
    if(ImGui::BeginMainMenuBar()) {
        if(ImGui::BeginMenu("File")) {
            if(ImGui::MenuItem("New file", "", &is_new_file_clicked)) {

            }
            if(ImGui::MenuItem("New folder", "", &is_new_folder_clicked)) {
                
            }
            if(ImGui::MenuItem("New console", "", &show_app_console)) {
                console = new Console();
            }
            if(ImGui::MenuItem("Open folder", "", &is_open_folder_clicked)) {

            }
            ImGui::EndMenu();
        }
        if(ImGui::BeginMenu("Settings")) {
            if(ImGui::MenuItem("Style")) {

            }
            if(ImGui::MenuItem("Commands")) {

            }
            ImGui::EndMenu();
        }
        if(ImGui::BeginMenu("About")) {

            ImGui::EndMenu();
        }
        // std::cout << "is pressed: " << new_file_is_pressed << '\n';
        if(is_new_file_clicked/* && !DialogWindow::is_new_file_window_created*/) {
            if(!(DialogWindow::is_new_file_window_created)) {
                wind = dialog_builder.build("New file window", current_path);
            } else {
                dialog_builder.set_input_field(wind, "New file window");
                wind->get_info_from_input(is_new_file_clicked, current_path);
            }

        }
        if(is_new_folder_clicked) {
            if(!(DialogWindow::is_new_folder_window_created)) {
                wind2 = dialog_builder.build("New folder window", current_path);
            } else {
                dialog_builder.set_input_field(wind2, "New folder window");
                wind2->get_info_from_input(is_new_folder_clicked, current_path);
            }
        }
        if(show_app_console) {
            
            console->Draw("Terminal", &show_app_console);
        }
        if(is_open_folder_clicked) {
            if(!(DialogWindow::is_open_folder_window_created)) {
                wind3 = dialog_builder.build("Open folder window", current_path);
                
            } else {
                dialog_builder.set_input_field(wind3, "Open folder window");
                p = wind3->get_info_from_input(is_open_folder_clicked, current_path);
                if(p != "") {
                    true_path = p;
                    show_window_with_files = true;
                    std::cout << "p: " << p << std::endl;
                    
                }
            }
        }
        if(show_window_with_files) {
            wind4 = wf_builder.build("Window with files", true_path, &show_window_with_files);
        }
        ImGui::EndMainMenuBar();
    }
    
    ImGui::End();
    
}


// Window with files on it

WindowWithFilesBuilder::WindowWithFilesBuilder() = default;


void WindowWithFilesBuilder::set_files_list(const std::string& path, const std::string& folder_name, bool* is_opened) {
    
    
    std::cout << "folder name: " << folder_name << " " << path << std::endl;
    if(current_dirs.empty()) {
        current_dirs[path] = folder_name;
    }
    std::map<std::string, std::string> copy = current_dirs;
    std::map<std::string, std::string>::iterator it1;
    // static bool show_hidden = false;
    float window_height = 400.0f;
    std::cout << "asdsfdbgf" << std::endl;
    ImGui::Begin("Window with files", is_opened);
    ImGui::BeginChild("##Files list", ImVec2(0, window_height), true);
    static ImGuiTextFilter filter;
    filter.Draw("##seach bar", 500);
    ImGui::SameLine(530);
    static bool selection_mode = false;
    static bool show_hidden = false;
    ImGui::Checkbox("Selection mode", &selection_mode);
    ImGui::SameLine();
    ImGui::Checkbox("Show hidden", &show_hidden);
    if(ImGui::BeginTabBar("MyTabBar")) {
        ImGui::Spacing();
        for(it1 = copy.begin(); it1 != copy.end(); ++it1) {
            bool open = true;
            if(ImGui::BeginTabItem((it1->second).c_str(), &open)) {
                // boost::filesystem::path dir = (it1->first);
                FileSystemItem fsi;
                std::map<std::string, std::string> dirs = fsi.get_dirs(it1->first);
                std::map<std::string, std::string> files = fsi.get_files(it1->first);
                std::map<std::string, std::string>::iterator it2;
                static bool is_selected[10000];          
                size_t counter = 0;
                for(it2 = dirs.begin(); it2 != dirs.end(); ++it2) {
                    if(filter.PassFilter((it2->second).c_str())) {
                        if(!show_hidden && it2->second[0] == '.') {
                            continue;
                        }
                        if(ImGui::Selectable((ICON_FA_FOLDER + (" " + it2->second)).c_str(), &is_selected[counter], 0, ImVec2(0, 0))) {
                            current_path = it1->first;
                            if(!selection_mode) {
                                is_selected[counter] = !is_selected[counter];
                                current_dir_list.push_back(it2->second);
                                current_dirs[it2->first] = it2->second;
                            }
                        }
                        ImGui::Spacing();
                        ++counter;
                    }
                } 
                
                for(it2 = files.begin(); it2 != files.end(); ++it2) {
                    if(filter.PassFilter((it2->first).c_str())) {
                        if(ImGui::Selectable((ICON_FA_FILE + (" " + it2->second)).c_str(), &is_selected[counter], ImGuiSelectableFlags_AllowDoubleClick)) {
                            
                            if(!selection_mode) {
                                is_selected[counter] = !is_selected[counter];
                                File new_file(it2->first);
                                    // ++counter;          
                                if(new_file.is_executable()) {
                                    new_file.execute();
                                } else {
                                    new_file.open();
                                }
                            }
                            
                        }
                        ImGui::Spacing();
                        ++counter;
                    }
                }
                ImGui::EndTabItem();
            }
            if(!open) {
                current_dirs.erase((it1->first));
            }
        }
        ImGui::EndTabBar();
    }
    ImGui::EndChild();
    ImGui::End();
}

void WindowWithFilesBuilder::set_service_tool_bar(/*ToolBar tool_bar*/) {

}

Window* WindowWithFilesBuilder::build(const std::string& name, const std::string& path, bool* is_opened) {
    ImVec2 pos (400, 400);
    ImVec2 size(915, 455);
    ImGuiStyle* style = &ImGui::GetStyle();
    if(!WindowWithFiles::is_window_with_files_created) WindowWithFiles::is_window_with_files_created = true;
    bool fl = false;
    ImGui::SetNextWindowSize(ImVec2(930, 430));
    ImGui::Begin(name.c_str(), is_opened); 

    style->WindowTitleAlign = ImVec2(0.5, 0.5);
    style->FramePadding = ImVec2(8, 4);
    style->Colors[ImGuiCol_TitleBg] = ImColor(255, 120, 53, 255);
    style->Colors[ImGuiCol_TitleBgActive] = ImColor(255, 120, 53, 255);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(255, 120, 53, 255);
    style->Colors[ImGuiCol_Button] = ImColor(31, 30, 31, 255);
    style->Colors[ImGuiCol_ButtonActive] = ImColor(31, 30, 31, 255);
    style->Colors[ImGuiCol_ButtonHovered] = ImColor(41, 40, 41, 255);
    style->Colors[ImGuiCol_Separator] = ImColor(70, 70, 70, 255);
    style->Colors[ImGuiCol_SeparatorActive] = ImColor(70, 70, 70, 255);
    style->Colors[ImGuiCol_SeparatorHovered] = ImColor(100, 100, 100, 255);
    
    ImGui::End();
    /*if(!boost::filesystem::is_directory(path)) {
        throw std::runtime_error("Not a directory");
    }*/
    boost::filesystem::path p = path;
    std::cout << "path: " << path << std::endl;
    set_files_list(path, str_username, is_opened);
    result = new WindowWithFiles(const_cast<std::string&>(path));
    return result;
}

// Dialog window

DialogWindowBuilder::DialogWindowBuilder() = default;



void DialogWindowBuilder::set_input_field(Window* dw, const std::string& name) {
    // std::cout << "dfdgbf" << std::endl;
    if(name == "New file window") {
        ImGui::Begin(name.c_str(), &is_new_file_clicked);
        // static char name_buff[64] = "";
        
        // std::vector<char*> buffers = dw->get_vector_of_buffers();
        // std::cout << "kkkk: " << (dw->buffs)[0] << std::endl;
        ImGui::InputText("file name", (dw->buffs)[0], 64);
        // static char ext_buff[64] = "";
        ImGui::InputText("extension", (dw->buffs)[1], 64);
        // static char path_buff[64] = "";
        ImGui::InputText("path (optional)", (dw->buffs)[2], 64);
        // char* t = path_buff;
        
        ImGui::End();
    } else if (name == "New folder window") {
        ImGui::Begin(name.c_str(), &is_new_folder_clicked);
        ImGui::InputText("folder name", dw->buffs[0], 64);
        ImGui::InputText("path (optional)", dw->buffs[1], 64);
        ImGui::End();
    } else if (name == "Open folder window") {
        ImGui::SetNextWindowSize(ImVec2(200, 100));
        ImGui::Begin(name.c_str(), &is_open_folder_clicked);
        ImGui::InputText("path", dw->buffs[0], 64);
        ImGui::End();
    }
}

Window* FilesWindow = nullptr;

Window* DialogWindowBuilder::build(const std::string& name, const std::string& cur_path) {
    if(name == "New file window") DialogWindow::is_new_file_window_created = true;
    else if (name == "New folder window") DialogWindow::is_new_folder_window_created = true;
    else if (name == "Open folder window") DialogWindow::is_open_folder_window_created = true;
    ImGuiStyle* style = &ImGui::GetStyle();
    style->WindowPadding = ImVec2(15, 10);
    ImVec2 size(370, 150);
    ImGui::SetNextWindowSize(size);

    if(name == "New file window") result = new DialogWindow(3, name);
    else if (name == "New folder window") result = new DialogWindow(2, name);
    else if (name == "Open folder window") result = new DialogWindow(1, name);
    // static DialogWindow dw(3, name);
    set_input_field(result, name);

    if(name == "New file window") result->get_info_from_input(is_new_file_clicked, cur_path);
    else if (name == "New folder window") result->get_info_from_input(is_new_folder_clicked, cur_path);
    else if (name == "Open folder window") {
        
        result->get_info_from_input(is_open_folder_clicked, cur_path);
        // std::cout << "r: " << r << std::endl;
        // FilesWindow = files_window_builder.build("Files window", p);
    }
    // std::cerr << "iam here" << std::endl;
    return result;
}