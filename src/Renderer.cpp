#include "Renderer.h"
#include "Scene.h"

Renderer::Renderer()
    : Layer("Renderer")
{
    
}

void Renderer::OnAttach() 
{

}

void Renderer::OnDetach() 
{

}

Layer* Renderer::Update(Layer* prev_result) 
{
    auto layer = dynamic_cast<Scene*>(prev_result);
    WolfRayetCore::Logger::PrintInteger(layer->GetWidth());

    return this;
}


void Renderer::PrepareImage() 
{

}

void Renderer::PassImage() 
{

}

void Renderer::UpdateInterface() 
{

}

void Renderer::Render() 
{

}
