#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "imgui.h"
#include "imgui_impl_glut.h"
#include <GL/freeglut.h>
#include "settings.h"
#include "font.h"
#include <boost/filesystem/operations.hpp>
#include "FileSystem.h"
#include "FileSystemFactory.h"
// #include <boost/filesystem>

const int MAX_USER_NAME = 64;
const int MAX_BUFFER_SIZE = 64;

class Console {
    private:
    char InputBuffer[MAX_BUFFER_SIZE];
    std::vector<std::string> commands;
    std::vector<std::string> history;
    std::vector<std::string> items;
    std::string cur_path;
    ImGuiTextFilter filter;
    int history_position;
    bool scroll_to_bottom;
    char user[MAX_USER_NAME];
    void ClearBuffer();
    public:
    Console();
    ~Console();
    void ExecCommand(const std::string& command_name, const std::vector<std::string>&);
    void Draw(const std::string&, bool*);
    void Clear();
};