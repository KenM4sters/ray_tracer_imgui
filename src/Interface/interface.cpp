#include "Interface.h"
#include "../App.h"


Interface::Interface()
    : Layer("Interface")
{
    
}
void Interface::OnAttach() 
{
    App& app = App::GetInstance();
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking Controls

    // Personal Preferences for ImGui Styles - not necessary.
    ImGui::StyleColorsDark();
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(app.GetWindow()->GetNativeWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

}

void Interface::OnDetach() 
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Interface::Begin() 
{
    bool bShowDemoWindow = false;
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    
    ImGui::NewFrame();
    if (bShowDemoWindow)
        ImGui::ShowDemoWindow(&bShowDemoWindow);
    
    ImGui::DockSpaceOverViewport();
    ImGui::ShowMetricsWindow();
} 

void Interface::End() 
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
} 
