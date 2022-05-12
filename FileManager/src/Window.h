#pragma once 
#include <iostream>
#include <string>
#include <vector>
#include "FileSystem.h"
#include "FileSystemFactory.h"
// #include <qt>

class Window {
    public:
    std::vector<char*> buffs;
    Window();
    Window(const Window&) {
        
    }
    virtual ~Window();
    void close();
    void show();
    void click_on_button();
    
    virtual std::string get_info_from_input(bool&, const std::string&) {}
};


class TextInfoWindow: public Window {
    private:
    std::string text;
    // TextField text;
    public:
    void set_text(std::string);
};

class MainWindow: public Window {
    private:
    // ToolBar service_tool_bar;
    // SearchBar searching_bar
    // ListView files_list
    FileSystemFactory factory_for_new_items;
    std::string name;
    public:
    MainWindow();
    MainWindow(std::string);
    bool search_file(std::string);
    void click_on_item(FileSystemItem);
    void click_on_button();
    std::vector<FileSystemItem> select_items();
};

class WindowWithFiles: public Window {
    private:
    FileSystemFactory factory;
    std::string path;
    public:
    static bool is_window_with_files_created;
    WindowWithFiles();
    WindowWithFiles(std::string&);

};


class DialogWindow: public Window {
    private:
    // InputField input;
    // char name_buff[64] = "";
    
    int number_of_buffers;
    std::string window_name;
    public:
    
    static bool is_new_file_window_created;
    static bool is_new_folder_window_created;
    static bool is_open_folder_window_created;
    DialogWindow();
    DialogWindow(int, const std::string&);
    ~DialogWindow();
    std::string get_info_from_input(bool&, const std::string&);
    std::vector<char*> get_vector_of_buffers() const;
};