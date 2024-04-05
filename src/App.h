#pragma once
#include "Core.h"
#include "Window.h"
#include "LayerStack.h"

/**
 * Going to try out a different architecture for this project, in which each layer will recieve
 * the "result" from the previous layer, which could just be the layer itself, or some new 
 * class, LayerResult etc... 
 * 
 * The idea is that we can order the layers such that it emulates the lifetime of our generated
 * pixels:
 * 
 *  - Scene (Generates important data (position, normals etc..) for each object in our scene)
 *  - Renderer (Uses data from the scene to cast rays towards the scene and calculate what color
 *    each pixel should be based on any colllisions with scene objects).
 *  - ImGUI Interface (Uses data from the Renderer to project a 2D Image to the screen, containg the
 *    pixel data which is the ouput from the Renderer's ray casting.)
 * 
 * Not sure how it will it turn out, but it sure sounds interesting and only time will tell.
*/

class App {
    public:
        App(std::string app_name, uint16_t w, uint16_t h) 
        {
            s_instance = this;

            m_window = std::make_shared<Window>(app_name, w, h);
            m_layerStack = std::make_unique<LayerStack>();
        
        }
        void Run(); 
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
        
        inline static App& GetInstance() {return *s_instance;}
        inline std::shared_ptr<Window>& GetWindow() {return m_window;} 
    protected:
        std::shared_ptr<Window> m_window = nullptr;
        std::unique_ptr<LayerStack> m_layerStack = nullptr;
        static App* s_instance;
        
};