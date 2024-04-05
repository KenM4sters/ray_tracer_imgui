#include "Scene.h"
#include "Interface/Interface.h"

Scene::Scene()
    : Layer("Scene")
{
    m_shouldUpdate = false;
}
void Scene::OnAttach() 
{

}

void Scene::OnDetach() 
{

}

void Scene::Update() 
{
    if(m_shouldUpdate) 
    {
        // m_availableWidth = ImGui::GetContentRegionAvail().x;
        // m_availableHeight = ImGui::GetContentRegionAvail().y;

        if(!m_image) 
        {
            m_image = std::make_shared<Image>(m_availableWidth, m_availableHeight, ImageFormat::RGBA, m_sceneData);

        }
    }
}

void Scene::UpdateInterface() 
{
    ImGui::Begin("Scene Menu"); 
    if(ImGui::Button("Render")) 
    {
        m_shouldUpdate = true;
    }
    
    if(m_shouldUpdate)
        if(ImGui::Button("Finish")) 
            m_shouldUpdate = false;
}

