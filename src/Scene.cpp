#include "Scene.h"
#include "Interface/Interface.h"

Scene::Scene()
    : Layer("Scene")
{
    m_shouldUpdate = false;
}

void Scene::OnAttach() {}

void Scene::OnDetach() 
{
    delete[] m_sceneData;
}

void Scene::PrepareImage() 
{
    // Firstly, delete the old one.
    delete[] m_sceneData;
    // Regenerate data with new size information (window may have resized).
    m_sceneData = new uint32_t[m_viewportWidth * m_viewportHeight];
    // Fill data.
    for(uint32_t i = 0; i < m_viewportWidth * m_viewportHeight; i++) 
    {
        m_sceneData[i] = 0xffff00ff;
    }
    m_image->SetData(m_sceneData);
}

void Scene::PassImage() 
{
    ImGui::Image((void*)(intptr_t)m_image->m_ID, ImVec2((float)m_image->GetWidth(), (float)m_image->GetHeight()), ImVec2(0, 1), ImVec2(1, 0));
}

void Scene::UpdateInterface() 
{
    // Editor Window.
    ImGui::DockSpaceOverViewport();
    ImGui::ShowMetricsWindow();
    ImGui::Begin("Editor Menu"); 
    if(ImGui::Button("Render")) 
    {
        m_shouldUpdate = true;
    }
    if(m_shouldUpdate)
        if(ImGui::Button("Finish")) 
        {
            m_shouldUpdate = false;
            m_image.reset();
        } 

    ImGui::End();

    // Main Scene View Window.
    ImGui::Begin("Scene");
    if(m_shouldUpdate) 
    {
        m_viewportWidth = ImGui::GetContentRegionAvail().x;
        m_viewportHeight = ImGui::GetContentRegionAvail().y;

        if(!m_image || m_viewportWidth != m_image->GetWidth() || m_viewportHeight != m_image->GetHeight()) 
        {

            m_image = std::make_shared<Image>(m_viewportWidth, m_viewportHeight, ImageFormat::RGBA);
            PrepareImage();
        }
        PassImage();
    }
    // End() is called from the interface in case you forget to call it here, but there's no harm
    // in doing it anywhere for clarity.
}

Layer* Scene::Update(Layer* prev_result) {
    return this;
}

