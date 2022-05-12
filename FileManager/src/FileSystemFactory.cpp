#include <iostream>
#include "FileSystemFactory.h"
#include <boost/filesystem/operations.hpp>
#include <vector>
#include <string>
#include <fstream>

FileSystemItem FileSystemFactory::create(std::string name, std::string type) {}

FileSystemItem* FileFactory::create_file(const std::string& name, const std::string& path_to) {
    std::ofstream file;
    file.open((path_to + name).c_str());
    result = new File;
    File new_file = (path_to + name);
    *result = new_file;
    return result;
}

FileSystemItem* FileFactory::create_file_by_path(const std::string& path) {
    std::ofstream file;
    file.open(path.c_str());
    result = new File;
    File new_file = path;
    *result = new_file;
    return result;
}

Archive ArchiveFactory::create_zip_archive(std::initializer_list<File> files) {

}

Archive ArchiveFactory::create_tar_archive(std::initializer_list<File> files) {

}

FileSystemItem* DirectoryFactory::create_dir(const std::string& name, const std::string& path) {
    boost::filesystem::create_directory(path + name);
    result = new Directory;
    Directory new_dir = (path + name);
    *result = new_dir;
    return result;
}

FileSystemItem* DirectoryFactory::create_dir_by_path(const std::string& path) {
    boost::filesystem::create_directories(path);
    result = new Directory;
    Directory new_dir = path;
    *result = new_dir;
    return result;
}