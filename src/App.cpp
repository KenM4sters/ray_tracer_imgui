#include "App.h"

App* App::s_instance = nullptr;

void App::Run() 
{
    while(m_window->IsRunning())
    {
        m_window->PreRender();

        // Loops through each layer (Only the Scene for now).
        for(const auto& layer : *m_layerStack.get()) 
        {
            layer->Update();
        }

        m_layerStack->GetOverlay()->Begin(); // Overlay is the interface in our case.
        for(const auto& layer : *m_layerStack.get()) 
        {
            layer->UpdateInterface();
        }
        m_layerStack->GetOverlay()->End();

        m_window->PostRender();
        WolfRayet::Core::Time::Update(); // Useful for getting the time between frames.
    }
}

void App::PushLayer(Layer* layer) 
{       
    m_layerStack->PushLayer(layer);
}
void App::PushOverlay(Layer* layer) 
{
    m_layerStack->PushOverlay(layer);
}