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

class SimpleEditor {
    private:
    char BigBuffer[1024 * 100];
    public:
    SimpleEditor();
};