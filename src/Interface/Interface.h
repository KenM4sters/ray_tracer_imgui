#pragma once
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>
#include "../Layer.h"

/**
 * This class is mostly for the initial setup of ImGUI so that we can use it in our main 
 * application, and for handling its destruction when we're finished. 
 * 
 * Almost all of the actual implementation will be done in each layer's OnImguiUpdate() 
 * function which gets called between the Begin() and End() functions here.
 * 
 * Think of this more as an "InterfaceConfig" class. 
*/

class Window;

class Interface : public Layer {
    public:
        Interface();
        ~Interface() {
            OnDetach();
        }
        void OnAttach() override;
        void OnDetach() override;
        void Begin() override; 
        void End() override; 
        Layer* Update(Layer* prev_result) override;
        
};