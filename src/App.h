#pragma once
#include "Core.h"
#include "Window.h"
#include "LayerStack.h"

/**
 * The App class is very barebones and essentially just handles the creation of the window,
 * the LayerStack which we push our layers onto in the main WolfRayet.cpp file, and iterates
 * over those layers in the right order to make sure that functions are called in the order that 
 * they should be called in.
 * 
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