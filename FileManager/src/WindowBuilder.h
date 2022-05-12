#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Window.h"

class WindowBuilder {
    protected:
    Window* result;
    static bool is_new_file_clicked;
    static bool opening_window;
    static bool is_new_folder_clicked;
    static bool is_open_folder_clicked;
    public:
    WindowBuilder();
    virtual Window* build(const std::string&, const std::string&);
    virtual void set_input_field(Window*, const std::string&) {}
    
};

class TextInfoWindowBuilder: public WindowBuilder {
    private:
    // TextInfoWindow result;
    public:
    TextInfoWindowBuilder();
    void set_text(std::string text);
    Window* build(const std::string&, const std::string&);
};

class MainWindowBuilder: public WindowBuilder {
    private:
    // MainWindow result;
    public:
    MainWindowBuilder();
    void set_service_tool_bar(/*ToolBar*/);
    void set_searching_bar(/*SearchBar*/);
    void add_files_list(std::string, std::string);
    void add_main_menu();
    Window* build(const std::string&, const std::string&);
};

class WindowWithFilesBuilder: public WindowBuilder {
    private:
    // WindowWithFiles result;
    public:
    WindowWithFilesBuilder();
    Window* build(const std::string&, const std::string&, bool*);
    void set_service_tool_bar(/*ToolBar*/);
    void set_files_list(const std::string&, const std::string&, bool*);
    
};

class DialogWindowBuilder: public WindowBuilder {
    private:
    // Window* result;
    public:
    DialogWindowBuilder();
    void set_input_field(Window*, const std::string&) override;
    // Window build(const std::string&, const std::string&);
    Window* build(const std::string&, const std::string&);
};