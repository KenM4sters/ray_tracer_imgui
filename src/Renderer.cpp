#include "Renderer.h"
#include "Interface/Interface.h"
#include "Raytracer.h"


std::shared_ptr<Scene> Renderer::m_scene = nullptr;

Renderer::Renderer()
{
    m_shouldUpdate = false;
}

void Renderer::OnAttach() 
{

}

void Renderer::OnDetach() 
{
    delete[] m_sceneData;
}

void Renderer::Update() 
{
    // if(m_sceneObjects) 
    // {
    //     WR::Core::Logger::PrintInteger(m_sceneObjects->at(0).Radius);
    // }
} 

void Renderer::PrepareImage() 
{
    // Firstly, delete the old one.
    delete[] m_sceneData;
    // Regenerate data with new size information (window may have resized).
    m_sceneData = new uint32_t[m_viewportWidth * m_viewportHeight];
    // Fill data.
    for(int y = 0; y < m_viewportHeight; y++) 
    {
        for(int x = 0; x < m_viewportWidth; x++) 
        {
            glm::vec2 uv = {x / (float)m_viewportWidth, y / (float)m_viewportHeight};
            m_sceneData[(y*m_viewportWidth) + x] = FragmentShader(uv);
        }
    }
    m_image->SetData(m_sceneData);
}

void Renderer::PassImage() 
{
    ImGui::Image((void*)(intptr_t)m_image->m_ID, ImVec2((float)m_image->GetWidth(), (float)m_image->GetHeight()), ImVec2(0, 1), ImVec2(1, 0));
}

void Renderer::UpdateInterface() 
{
    // Editor Window.
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
    ImGui::Begin("Viewport");
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

void Renderer::Render() 
{

}

void Renderer::SetActiveScene(std::shared_ptr<Scene> scene) 
{
    m_scene = scene;

}

uint32_t Renderer::FragmentShader(glm::vec2 uv) 
{
    uint8_t r = (uint8_t)(uv.r * 255.0f);   
    uint8_t g = (uint8_t)(uv.g * 255.0f);

    // y = mx + c
    Ray ray;
    ray.Origin = glm::vec3(0.0f, 0.0f, 0.0f);
    ray.Direction = glm::vec3(uv.x, uv.y, -1.0f);

    CollisionData collision_data = Raytracer::TraceRay(&ray);
    // WR::Core::Logger::PrintInteger(collision_data.DistanceFromCamera);

    if(collision_data.DistanceFromCamera < 0.0f) {} 

    return 0xff0000ff;
}
