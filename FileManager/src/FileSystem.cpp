#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "FileSystem.h"
#include <boost/filesystem/operations.hpp>
#include <unistd.h>

FileSystemItem::FileSystemItem() = default;

std::string FileSystemItem::find() {

}

bool FileSystemItem::is_dir() {
    return boost::filesystem::is_directory(path);
}

bool FileSystemItem::is_file() {
    return boost::filesystem::is_regular_file(path);
}

bool FileSystemItem::exists() {
    return boost::filesystem::exists(path);
}

bool FileSystemItem::is_archive() {
    
}

void FileSystemItem::change_permission(int new_permission) {

}

std::string FileSystemItem::get_name() {
    return name;
}

void FileSystemItem::rename(std::string new_name) {
    name = new_name;
}

void FileSystemItem::open() const { }

void FileSystemItem::remove() {}

FileSystemItem FileSystemItem::clone(const std::string& destination) {

}

std::map<std::string, std::string> FileSystemItem::get_dirs(const std::string& path_name) {
    boost::filesystem::path dir = path_name;
    std::map<std::string, std::string> dirs;
    for(boost::filesystem::directory_iterator it(dir), end; it != end; ++it) {
        if(boost::filesystem::is_directory(it->path())) {
            dirs[(it->path()).string()] = (it->path()).filename().string();
        }
    }
    return dirs;
}

std::map<std::string, std::string> FileSystemItem::get_files(const std::string& path_name) {
    boost::filesystem::path dir = path_name;
    std::map<std::string, std::string> files;
    for(boost::filesystem::directory_iterator it(dir), end; it != end; ++it) {
        if(!boost::filesystem::is_directory(it->path())) {
            files[(it->path()).string()] = (it->path()).filename().string();
        }
    }
    return files;
}


File::File() = default;

File::~File() = default;

File& File::operator=(const File& other) {
    ext = other.ext;
    path_to_file = other.path_to_file;
    size = other.size;
    return *this;
}

File::File(const std::string& path_to): path_to_file(path_to) {
    boost::filesystem::path p = path_to_file;
    ext = p.extension().string();
    size = boost::filesystem::file_size(p);
}

bool File::is_executable() {
    return (!access(path_to_file.c_str(), X_OK));
}

void File::execute() {
    if(!is_executable()) {
        throw std::runtime_error("file is not executable");
    }
    system(path_to_file.c_str());
}

void File::open() const {
    if(ext == ".txt") {
        system(("gedit " + path_to_file).c_str());
    } else if(ext == ".pdf") {
        system(("evince " + path_to_file).c_str());
    } else if(ext == ".docx" || ext == ".pptx" || ext == ".doc" || ext == ".csv" || ext == ".odt" || ext == ".ods" || ext == ".rtf") {
        system(("libreoffice " + path_to_file).c_str());
    } else if(ext == ".jpg" || ext == ".jpeg" || ext == ".png") {
        system(("eog " + path_to_file).c_str());
    } else if(ext == ".mp3") {
        system(("rhythmbox " + path_to_file).c_str());
    } else {
        system(("gedit " + path_to_file).c_str());
    }
}

void File::remove() {
    boost::filesystem::remove(path_to_file);
}

FileSystemItem File::clone(const std::string& destination) {
    boost::filesystem::copy(path_to_file, destination);
    File new_file(destination);
    return new_file;
}

void File::fully_remove() {

}

std::string File::get_extension() {
    return ext;
}

long long File::get_size() {
    return size;
}

// Archive:

Archive::Archive() {

}

Archive::Archive(std::string name) {
    
}

FileSystemItem& Archive::make_archive(const std::vector<File>& files) {

}

std::vector<File> Archive::dearchive() {

}

void Archive::remove() {

}

FileSystemItem Archive::clone(const std::string& destination) {

}

std::string Archive::get_extension() {
    return extension;
}

long long Archive::get_size() {
    return size;
}

void Archive::open() const {

}

// Directory:
Directory::Directory () = default;

Directory::Directory(const std::string& name) {

}



void Directory::remove() {

}

FileSystemItem Directory::clone(const std::string& destination) {

}

int Directory::get_number_of_files() {
    return files_number;
}

void Directory::open() const {

}