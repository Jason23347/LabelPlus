#include "gui.h"
#include "imgui.h"
#include "imgui_helpers.hpp"

#include <stdio.h>
#include <string.h>

void Gui::showDebugWindow()
{
    static float f = 0.0f;

    imgui_helpers::show_im_gui_menu();

    ImGui::Text("Hello, world!");
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    ImGui::ColorEdit3("clear color", (float*)&clear_color);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

void Gui::showMainMenuBar()
{
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Plugin")) {

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help")) {

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

void Gui::showMainToolBar()
{
    static ImGui::Toolbar toolbar("myFirstToolbar##foo");

    // run once only
     if (toolbar.getNumButtons()==0)  {
        fprintf(stderr,"add to toolbar\n");
        char tmp[1024];ImVec2 uv0(0,0),uv1(0,0);
        for (int i=0;i<9;i++) {
            strcpy(tmp,"toolbutton ");
            sprintf(&tmp[strlen(tmp)],"%d",i+1);
            uv0 = ImVec2((float)(i%3)/3.f,(float)(i/3)/3.f);
            uv1 = ImVec2(uv0.x+1.f/3.f,uv0.y+1.f/3.f);

            toolbar.addButton(ImGui::Toolbutton(tmp, NULL,uv0,uv1));
        }
        toolbar.addSeparator(16);

        toolbar.addButton(ImGui::Toolbutton("toolbutton 11", NULL,uv0,uv1,ImVec2(32,32),true,false,ImVec4(0.8,0.8,1.0,1)));  // Note that separator "eats" one toolbutton index as if it was a real button
        toolbar.addButton(ImGui::Toolbutton("toolbutton 12", NULL,uv0,uv1,ImVec2(48,24),true,false,ImVec4(1.0,0.8,0.8,1)));  // Note that separator "eats" one toolbutton index as if it was a real button

        toolbar.setProperties(false,false,true,ImVec2(0.5f,0.f));
    }

    const int pressed = toolbar.render();
    if (pressed>=0)
        fprintf(stderr,"Toolbar1: pressed:%d\n",pressed);

}

void Gui::showStatusBar()
{

}


void Gui::frame()
{
    // imgui has no "root window", so we build one
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize, ImGuiCond_Always);
    ImGui::SetNextWindowCollapsed(false, ImGuiCond_Always);
    auto winflags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar |
                    ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                    ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav |
                    ImGuiWindowFlags_NoBringToFrontOnFocus;
    ImGui::Begin("Same title as another window##1", NULL, winflags);
    ImGui::Text("This is window 1.\nMy title is the same as window 2, but my identifier is unique.");

    static char name[32] = "Label1";
    ImGui::Text("Edit name:");
    ImGui::InputText("##edit", name, IM_ARRAYSIZE(name));

    // Child 2: rounded border
    {
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
        ImGui::BeginChild("Child2", ImVec2(0, 260), true);
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Menu"))
            {
                // ShowExampleMenuFile();
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
        ImGui::Columns(2);
        for (int i = 0; i < 100; i++)
        {
            char buf[32];
            sprintf(buf, "%03d", i);
            ImGui::Button(buf, ImVec2(-FLT_MIN, 0.0f));
            ImGui::NextColumn();
        }
        ImGui::EndChild();
        ImGui::PopStyleVar();
    }


    ImGui::End();


    // showMainMenuBar();
    // showMainToolBar();

    // showStatusBar();

    showDebugWindow();
}
