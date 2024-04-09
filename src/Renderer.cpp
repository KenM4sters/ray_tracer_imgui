#include "Renderer.h"
#include "Interface/Interface.h"
#include "Raytracer.h"

std::shared_ptr<Scene> Renderer::m_scene = nullptr;

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

void Renderer::PrepareImage() 
{
    // Firstly, delete the old one.
    delete[] m_sceneData;
    // Regenerate data with new size information (window may have resized).
    m_sceneData = new uint32_t[m_viewportWidth * m_viewportHeight];

    Ray ray;
    ray.Origin = m_camera->GetPosition();

    for(int y = 0; y < m_viewportHeight; y++) 
    {
        for(int x = 0; x < m_viewportWidth; x++) 
        {
            ray.Direction = m_camera->GetRayDirections()[(y*m_viewportWidth) + x];
            glm::vec4 color = FragmentShader(&ray);
            color = glm::clamp(color, glm::vec4(0.0f), glm::vec4(1.0f));
            m_sceneData[(y*m_viewportWidth) + x] = ConvertFromRGBA(color);
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

void Renderer::SetActiveScene(std::shared_ptr<Scene> scene) 
{
    m_scene = scene;

}

glm::vec4 Renderer::FragmentShader(Ray* ray) 
{
    CollisionData collision_data = Raytracer::TraceRay(ray);

    if(collision_data.DistanceFromCamera < 0.0f) {
        // return m_scene->GetBackgroundImageData()->GetData()[(y*viewport_width) + x];
        return glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
    }

    auto& lights = m_scene->GetLights();
    glm::vec3 mat_color = m_scene->GetPBRMaterials()->at(collision_data.object_index).Albedo;

    glm::vec3 light_contribution{0.0f}; 
    
    // I was messing around with std::variant for the lights container to see how well it works in comparaison to polymorphism.
    // Conclusion: It's alright, but I think taking advantage of polymorphism with dynamic_cast is at least a lot neater.
    for(int i = 0; i < lights->size(); i++) 
    {
        if(auto light = std::get_if<PointLight>(&lights->at(i)))
        {
            glm::vec3 N = glm::normalize(collision_data.Normal);
            glm::vec3 D = glm::normalize(collision_data.WorldPosition - light->Position);
            float angle = glm::max(glm::dot(-D, N), 0.0f);
            glm::vec3 color = light->Color * light->Intensity * angle;
            light_contribution += color;
        }
    }
    // WR::Core::Logger::PrintVec3f(light_contribution);
    glm::vec3 final_color = mat_color + light_contribution;
    return glm::vec4(final_color, 1.0f);
}
          