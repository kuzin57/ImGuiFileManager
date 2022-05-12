#include <iostream>
#include <string>
#include <vector>
#include "Window.h"
#include "imgui.h"
#include "imgui_impl_glut.h"
#include "imgui_impl_opengl2.h"
#include <GL/freeglut.h>
#include "FileSystem.h"
#include "FileSystemFactory.h"

FileSystemItem* new_file;
FileSystemItem* new_dir;

Window::Window() {
    
}

Window::~Window() {
    
}

void Window::close() {

}

void Window::show() {

}

void Window::click_on_button() {
    // std::cout << "click" << '\n';
}

// TextWindow

void TextInfoWindow::set_text(std::string text) {

}

// MainWindow

MainWindow::MainWindow() {}
MainWindow::MainWindow(std::string n) {
    name = n;
}

bool MainWindow::search_file(std::string name) {

}


void MainWindow::click_on_item(FileSystemItem item) {

}

void MainWindow::click_on_button() {
    std::cout << "sdvfnvdfvb" << std::endl;
}

std::vector<FileSystemItem> MainWindow::select_items() {

}

// DialogWindow

DialogWindow::DialogWindow() = default;
DialogWindow::DialogWindow(int n, const std::string& name): number_of_buffers(n), window_name(name) {
    // buffs = std::vector<char*>(n);
    char* arr;
    for(int i = 0; i < n; ++i) {
        arr = new char[64];
        // buffs[i] = new char[64];
        buffs.push_back(arr);
        for(int j = 0; j < 64; ++j) {
            buffs[i][j] = '\0';
        }
    }
}

DialogWindow::~DialogWindow() {
    /*if(window_name == "New file window" ) is_new_file_window_created = false;
    for(int i = 0; i < number_of_buffers; ++i) {
        delete[] buffs[i];
    }*/
    for(int i = 0; i < buffs.size(); ++i) {
        delete[] buffs[i];
    }
    // std::cerr << "kkkkkkk" << std::endl;
}

std::string DialogWindow::get_info_from_input(bool& is_opened, const std::string& cur_path) {
    std::string result = "";
    if(window_name == "New file window") {
        ImGui::Begin(window_name.c_str(), &is_opened);
        if(ImGui::Button("create file")) {
            FileFactory factory;
            std::string full_name = std::string(buffs[0]) + std::string(buffs[1]);
            std::string path_to_new_file = cur_path;
            // char* t = buffs[2];
            if(buffs[2][0] == '/') {
                path_to_new_file = std::string(buffs[2]);
            }
            std::cout << (path_to_new_file + full_name) << std::endl;
            new_file = factory.create_file(full_name, path_to_new_file);
            new_file->open();
        }
        ImGui::End();
    } 
    if (window_name == "New folder window") {
        ImGui::Begin(window_name.c_str(), &is_opened);
        if(ImGui::Button("create folder")) {
            std::cout << "buffs: " << buffs[1] << std::endl;
            DirectoryFactory factory;
            std::string full_name = std::string(buffs[0]);
            std::string path_to_new_folder = cur_path;
            if(buffs[1][0] == '/') {
                path_to_new_folder = std::string(buffs[1]);
            }
            std::cout << (path_to_new_folder + full_name) << std::endl;
            new_dir = factory.create_dir(full_name, path_to_new_folder);
            
        }
        ImGui::End();
    }
    if(window_name == "Open folder window") {
        ImGui::Begin(window_name.c_str(), &is_opened);
        if(ImGui::Button("open folder")) {
            std::cout << "result: " << buffs[0] << std::endl;
            result = std::string(buffs[0]);
            delete[] buffs[0];
            buffs[0] = new char[1];
            buffs[0][0] = '\0';
            // buffs[0] = "\0";
        }
        ImGui::End();
    }
    return result;
}


WindowWithFiles::WindowWithFiles() = default;

WindowWithFiles::WindowWithFiles(std::string& p): path(p) {}

//bool DialogWindow::is_new_file_window_created = false;

std::vector<char*> DialogWindow::get_vector_of_buffers() const {
    return buffs;
}