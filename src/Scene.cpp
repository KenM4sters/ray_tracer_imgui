#include "Scene.h"
#include "Interface/Interface.h"
#include "Renderer.h"
Scene::Scene()
    : Layer("Scene")
{
    // Sphere1
    m_sceneObjects.emplace_back(SceneObject({
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        0.5f
    }));

    m_materials.emplace_back(PBRMaterial({
        glm::vec3(0.1f, 0.0f, 0.0f),
        0.2f,
        0.8f,
        0.4f
    }));

    // Sphere2
    m_sceneObjects.emplace_back(SceneObject({
        glm::vec3(0.0f, -203.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        200.0f
    }));

    m_materials.emplace_back(PBRMaterial({
        glm::vec3(0.0f, 0.1f, 0.0f),
        0.2f,
        0.8f,
        0.4f
    }));

    // // Sphere3
    m_sceneObjects.emplace_back(SceneObject({
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        0.5f
    }));

    m_materials.emplace_back(PBRMaterial({
        glm::vec3(0.0f, 0.05f, 0.05f),
        0.2f,
        0.8f,
        0.4f
    }));


    // Lights
    m_lights.emplace_back(PointLight({
        glm::vec3(3.0f, 3.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        0.5f
    }));

    // Background Image
    m_backgroundImage.LoadTextureFromFIle("Assets/Textures/brotherhood.jpg");
    
}

void Scene::OnAttach() {
    PushSceneToRenderer();
}

void Scene::OnDetach() {
}

void Scene::Update() {}


void Scene::UpdateInterface() 
{
    ImGui::Begin("Scene Editor");
    std::string object_name = "Sphere";
    // Spheres
    for(int i = 0; i < m_sceneObjects.size(); i++) 
    {
        std::string index = std::to_string(i);
        ImGui::Text(std::string("Sphere" + index).c_str());
        std::string name = object_name + index + "pos";
        ImGui::InputFloat3(name.c_str(), (float*)&m_sceneObjects[i].Position);
    }

    std::string mat_name = "Sphere";
    for(int i = 0; i < m_materials.size(); i++) 
    {
        std::string index = std::to_string(i);
        ImGui::Text(std::string("Mat" + index).c_str());
        std::string name = mat_name + index + "Albedo";
        ImGui::InputFloat3(name.c_str(), (float*)&m_materials[i].Albedo);
        
        name = mat_name + index + "Roughness";
        ImGui::SliderFloat(name.c_str(), &m_materials[i].Roughness, -1.0f, 1.0f);
        name = mat_name + index + "Metallic";
        ImGui::SliderFloat(name.c_str(), &m_materials[i].Metallic, -1.0f, 1.0f);
        
    }

    std::string light_name = "Light";
    for(int i = 0; i < m_lights.size(); i++) 
    {
        if(auto light = std::get_if<PointLight>(&m_lights[i]))
        {
            std::string index = std::to_string(i);
            ImGui::Text(std::string("Light" + index).c_str());
            std::string name = light_name + index + "col";
            std::string i_name = "Intensity";
            ImGui::InputFloat3(name.c_str(), (float*)&light->Colour);
            ImGui::SliderFloat(i_name.c_str(), &light->Intensity, 0.0f, 10.0f);
        }
    }

    ImGui::End();


}

void Scene::PushSceneToRenderer() 
{
    Renderer::SetActiveScene(this);
}
