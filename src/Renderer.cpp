#include "Renderer.h"
#include "Interface/Interface.h"
#include "Raytracer.h"
#include <future>

Scene* Renderer::m_scene = nullptr;

static uint32_t ConvertFromRGBA(const glm::vec4& color) 
{
    uint8_t r = static_cast<uint8_t>(color.r*255.0f);
    uint8_t g = static_cast<uint8_t>(color.g*255.0f);
    uint8_t b = static_cast<uint8_t>(color.b*255.0f);
    uint8_t a = static_cast<uint8_t>(color.a*255.0f);

    return static_cast<uint32_t>((a << 24) | (b << 16) | (g << 8) | r);
}


Renderer::Renderer(std::shared_ptr<PerspectiveCamera>* camera)
{
    m_shouldUpdate = false;
    m_camera = *camera;
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
    m_camera->Update();
}

void Renderer::ProcessPixels(int x, int y) 
{
    glm::vec4 color = RayGen(x, y);
    color = glm::clamp(color, glm::vec4(0.0f), glm::vec4(1.0f));
    m_sceneData[(y*m_viewportWidth) + x] = ConvertFromRGBA(color);
}

void Renderer::PrepareImage() 
{
    // Firstly, delete the old one.
    delete[] m_sceneData;
    // Regenerate data with new size information (window may have resized).
    m_sceneData = new uint32_t[m_viewportWidth * m_viewportHeight];

    // Allocating threads for each pixel processing function.
    std::vector<std::future<void>> futures;
    for(int y = 0; y < m_viewportHeight; y++) 
    {
        for(int x = 0; x < m_viewportWidth; x++) 
        {
            futures.push_back(std::async(std::launch::async, [this, x, y](){
                ProcessPixels(x, y);
            }));
        }
    }
    // Wait until all threads are finished. 
    for(const auto& f : futures) 
    {
        f.wait();
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
    ImGui::Begin("Render Controls"); 
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
            m_camera->Resize(m_viewportWidth, m_viewportHeight);
            PrepareImage();
        }
        PassImage();
    }

    ImGui::End(); // Needs to be called after any ImGui::Begin() call to siginify that we're done adding to the currently active viewport.

}

void Renderer::Render() 
{

}

void Renderer::SetActiveScene(Scene* scene) 
{
    m_scene = scene;

}

glm::vec4 Renderer::RayGen(uint32_t x, uint32_t y) 
{   
    Ray ray;
    ray.Origin = m_camera->GetPosition();
    ray.Direction = m_camera->GetRayDirections()[(y*m_viewportWidth) + x];

    auto& lights = m_scene->GetLights();

    glm::vec3 colour{0.0f};

    float multiplier = 1.0f;
    constexpr uint8_t nBounces = 2;
    for(int i = 0 ; i < nBounces; i++) 
    {
        CollisionData collision_data = Raytracer::TraceRay(&ray);
        PBRMaterial mat = m_scene->GetPBRMaterials()->at(collision_data.object_index);

        if(collision_data.DistanceFromCamera < 0.0f) {
            glm::vec3 sky_colour = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
            colour += sky_colour * multiplier;
            break;
        }

        // I was messing around with std::variant for the lights container to see how well it works in comparison to polymorphism.
        // Conclusion: It's alright, but I think taking advantage of polymorphism with dynamic_cast is at least a lot neater.
        for(int i = 0; i < lights->size(); i++) 
        {
            if(auto light = std::get_if<PointLight>(&lights->at(i)))
            {
                glm::vec3 N = glm::normalize(collision_data.Normal);
                glm::vec3 D = glm::normalize(collision_data.WorldPosition - light->Position);
                float angle = glm::max(glm::dot(-D, N), 0.0f);
                glm::vec3 light_contribution = light->Colour * light->Intensity * angle;
                colour += light_contribution * mat.Albedo * multiplier + mat.A0;

            }
        } 
        
        multiplier *= 0.75f;


        ray.Origin = collision_data.WorldPosition;
        ray.Direction = glm::reflect(ray.Direction, collision_data.Normal);
    }


    return glm::vec4(colour, 1.0f);
}
          