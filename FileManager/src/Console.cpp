#include <iostream>
#include <vector>
#include <string>
#include "imgui.h"
#include "imgui_impl_glut.h"
#include <GL/freeglut.h>
#include "settings.h"
#include "font.h"
#include "Console.h"
#include <boost/filesystem/operations.hpp>
#include <unistd.h>
#include <limits.h>
#include "FileSystemFactory.h"
#include "FileSystem.h"

Console::Console() {
    gethostname(user, MAX_USER_NAME);
    cur_path = "/home/roman";
    scroll_to_bottom = false;
    for(int i = 0; i < 64; ++i) {
        InputBuffer[i] = '\0';
    }
}

Console::~Console() = default;

void Console::ClearBuffer() {
    for(int i = 0; i < MAX_BUFFER_SIZE; ++i) {
        InputBuffer[i] = '\0';
    }
}

void Console::ExecCommand(const std::string& command_name, const std::vector<std::string>& args) {
    if(command_name == "help") {
        items.push_back(std::string(user) + ":" + cur_path + "$ " + command_name);
        items.push_back("You enter help command");
    }
    if(command_name == "cd") {
        items.push_back(std::string(user) + ":" + cur_path + "$ " + command_name + " " + args[0]);
        cur_path = args[0];
    }
    if(command_name == "mkdir") {
        items.push_back(std::string(user) + ":" + cur_path + "$ " + command_name + " " + args[0]);
        if(args[0][0] != '/') {
            DirectoryFactory factory;
            FileSystemItem* dir = factory.create_dir(args[0], cur_path + "/");
        } else {
            DirectoryFactory factory;
            FileSystemItem* dir = factory.create_dir_by_path(args[0]);
        }
    }
    if(command_name == "clear") {
        items.push_back(std::string(user) + ": " + cur_path + "$ " + command_name);
        Clear();
    }
    if(command_name == "open") {
        items.push_back(std::string(user) + ":" + cur_path + "$ " + command_name + " " + args[0]);
        FileFactory factory;
        FileSystemItem* file = nullptr;
        if(args[0][0] == '/') {
            file = factory.create_file_by_path(args[0]);
        } else {
            file = factory.create_file(args[0], cur_path + "/");
        }
        file->open();
    }
    if(command_name == "cat") {
        
    }
    ClearBuffer();
    scroll_to_bottom = true;
}

void Console::Clear() {
    items.clear();
}

void Console::Draw(const std::string& title, bool* open) {
    ImGui::SetNextWindowPos(ImVec2(720, 600), ImGuiCond_FirstUseEver);
    ImGui::Begin(title.c_str(), open, 0);
    ImGui::TextWrapped("This is a simple console for managing file system. You can see the list of commands by typing a \" Help \" command. Also you can set the commands you like in settings.");
    filter.Draw("Search commands", 200);
    if(ImGui::SmallButton("Clear")) {
        Clear();
    }
    ImGui::SameLine();
    if(ImGui::SmallButton("Close")) {
        *open = false;
    }
    const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    ImGui::BeginChild("Active area", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);
    for(size_t i = 0; i < items.size(); ++i) {
        if(filter.PassFilter(items[i].c_str())) {
            bool with_color = false;
            ImVec4 color;
            if(items[i][0] == '#') {
                color = ImVec4(0.5f, 0.2f, 0.7f, 1.0f);
                with_color = true;
            }
            if(with_color) {
                ImGui::PushStyleColor(ImGuiCol_Text, color);
            }
            ImGui::Text(items[i].c_str());

            if(with_color) {
                ImGui::PopStyleColor();
            }

        }
    }
    if(scroll_to_bottom) {
        ImGui::SetScrollHereY(1.0f);
    }
    scroll_to_bottom = false;
    ImGui::EndChild();
    if(ImGui::InputText("Input area", InputBuffer, 64, ImGuiInputTextFlags_EnterReturnsTrue)) {
        std::string command = InputBuffer;
        std::vector<std::string> args;
        std::string command_type = "";
        std::string cur_arg = "";
        bool reading_command_type = true;
        bool reading_an_argument = false;
        for(size_t i = 0; i < command.size(); ++i) {
            if(command[i] != ' ' && reading_command_type) {
                command_type.push_back(command[i]);
            } else if(command[i] == ' ' && reading_command_type) {
                reading_command_type = false;
            } else if(command[i] != ' ' && !reading_an_argument) {
                reading_an_argument = true;
                cur_arg.push_back(command[i]);
            } else if(command[i] == ' ' && reading_an_argument) {
                reading_an_argument = false;
                args.push_back(cur_arg);
                cur_arg = "";
            } else if(command[i] != ' ' && reading_an_argument) {
                cur_arg.push_back(command[i]);
            }
        }
        args.push_back(cur_arg);
        ExecCommand(command_type, args);
    }
    ImGui::End();
}