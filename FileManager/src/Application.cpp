#pragma execution_character_set("utf-8")
#include <iostream>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glut.h"
#include "imgui_impl_opengl2.h"
#include <GL/freeglut.h>
#include "Application.h"
#include "Window.h"
#include "WindowBuilder.h"
#include "FileSystemFactory.h"
#include "FileSystem.h"
#include "IconsFontAwesome4.h"
#include "font.h"
// #include "WindowsDirector.h"

/*Window Application::create_window_using_director() {

}*/

static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

Application::Application(int argc, char** argv) {
    
    /*for(size_t i = 0; i < files.size(); ++i) {
        std::cout << files[i] << '\n';
    }*/
    glutInit(&argc, argv);
#ifdef __FREEGLUT_EXT_H__
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
#endif
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("File Manager");

    // Setup GLUT display function
    // We will also call ImGui_ImplGLUT_InstallFuncs() to get all the other functions installed for us,
    // otherwise it is possible to install our own functions and call the imgui_impl_glut.h functions ourselves.
    
    
    glutDisplayFunc(init);
    
    
    // std::cout << "ok" << std::endl;
    // Setup Dear ImGui context


    //************************
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;  
             // Enable Docking
    io.Fonts->AddFontDefault();
    /*io.Fonts->AddFontFromFileTTF("./fontawesome-webfont.ttf", 16.f);
    io.Fonts->AddFontFromFileTTF("./forkawesome-webfont.ttf", 16.f);*/
    static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
    ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
    io.Fonts->AddFontFromFileTTF("./fontawesome-webfont.ttf", 16.0f, &icons_config, icons_ranges );
    // ImFontConfig icons_config; icons_config.MergeMode = false; icons_config.PixelSnapH = true;
    io.Fonts->AddFontFromFileTTF("./arial.ttf", 12.7f, &icons_config, io.Fonts->GetGlyphRangesCyrillic());
    // io.Fonts->AddFontFromFileTTF("/home/roman/TRUE_FILE_MANANGER/FileManager/MyFileManager/FileManager/src/OpenFontIcons.ttf", 16.f);
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGLUT_Init();
    ImGui_ImplGLUT_InstallFuncs();
    ImGui_ImplOpenGL2_Init();

    //***************************

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    glutMainLoop();
    // Cleanup

    //**********************************************
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();
}

void init() {
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGLUT_NewFrame();
    ImGuiIO& io = ImGui::GetIO();
    
    // io.Fonts->Build();
    // Window new_window;
    MainWindowBuilder builder;
    // ImGui::ShowDemoWindow();
    Window* main_window = builder.build("main", "b");
    /*MainWindow mw;
    main_window.click_on_button();*/
    /*TextInfoWindowBuilder text_win_builder;
    Window text_window = text_win_builder.build("text1");*/

    // WindowDirector director("main_window");
    // my_display_code();

    // Rendering
    // io.Fonts->AddFontFromFileTTF("./fontawesome-webfont.ttf", 16.f);
    ImGui::Render();

    
    /*io.Fonts->AddFontFromFileTTF("./fontawesome-webfont.ttf", 16.f);
    io.Fonts->Build();*/
    // ImGui_ImplGLUT_NewFrame();
    /*io.Fonts->AddFontDefault();
    ImFontConfig icons_config;
    io.Fonts->AddFontFromFileTTF("OpenFontIcons.ttf", 16.f, &icons_config);*/
    //*****************************************************************

    glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound, but prefer using the GL3+ code.
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

    glutSwapBuffers();
    glutPostRedisplay();
}