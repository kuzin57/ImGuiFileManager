#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "FileSystem.h"


class FileSystemFactory {
    public:
    FileSystemItem create(std::string, std::string);
};

class FileFactory: public FileSystemFactory {
    private:
    File* result;
    public:
    FileSystemItem* create_file(const std::string&, const std::string&);
    FileSystemItem* create_file_by_path(const std::string&);
};

class ArchiveFactory: public FileSystemFactory {
    private:
    Archive* result;
    public:
    Archive create_zip_archive(std::initializer_list<File>);
    Archive create_tar_archive(std::initializer_list<File>);
};

class DirectoryFactory: public FileSystemFactory {
    private:
    Directory* result;
    public:
    FileSystemItem* create_dir(const std::string&, const std::string&);
    FileSystemItem* create_dir_by_path(const std::string&);
};  