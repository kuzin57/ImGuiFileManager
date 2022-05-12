#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <boost/filesystem/operations.hpp>

class FileSystemItem {
    protected:
        std::string path;
        int last_change; // in seconds
        int permission; //code of permission
        std::string name;
    public:
        FileSystemItem();
        std::string find();
        bool is_dir();
        bool is_file();
        bool is_archive();
        // virtual FileSystemItem clone();
        void change_permission(int);
        std::string get_name();
        void rename(std::string);
        bool exists();
        virtual void open()const;
        virtual void remove();
        virtual FileSystemItem clone(const std::string&);
        std::map<std::string, std::string> get_dirs(const std::string&);
        std::map<std::string, std::string> get_files(const std::string&);
};


class File: public FileSystemItem {
    private:
    std::string ext = "";
    std::string path_to_file;
    long long size;
    public:
    File();
    File(const std::string&);
    ~File();
    File& operator=(const File&);
    bool is_executable();
    void execute();
    void open() const override;
    void remove() override;
    void fully_remove();
    FileSystemItem clone(const std::string&) override;
    std::string get_extension();
    long long get_size();
};

class Archive: public FileSystemItem {
    private:
    std::string extension;
    long long size;

    public:
    Archive();
    Archive(std::string);
    FileSystemItem& make_archive(const std::vector<File>&);
    std::vector<File> dearchive();
    void remove() override;
    FileSystemItem clone(const std::string&) override;
    std::string get_extension();
    long long get_size();
    void open() const override;
};


class Directory: public FileSystemItem {
    private:
    int files_number;
    // Directory* parent;
    bool is_secret;

    public:
    Directory();
    Directory(const std::string&);
    operator Archive() {
        
    }
    Directory& operator=(const Directory& other) {
        std::cout << "asfdf" << std::endl;
        files_number = other.files_number;
        
    }
    void remove() override;
    FileSystemItem clone(const std::string&) override;
    int get_number_of_files();
    void open() const override;
};