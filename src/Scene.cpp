#include "Scene.h"
#include "Interface/Interface.h"
#include "Renderer.h"
Scene::Scene()
    : Layer("Scene")
{
    // // Sphere1
    // m_sceneObjects.emplace_back(SceneObject({
    //     glm::vec3(-2.0f, 0.0f, 0.0f),
    //     glm::vec3(1.0f, 1.0f, 1.0f),
    //     glm::vec3(0.0f, 0.0f, 0.0f),
    //     0.5f
    // }));

    // m_materials.emplace_back(PBRMaterial({
    //     glm::vec3(1.0f, 0.0f, 0.0f),
    //     0.2f,
    //     0.8f,
    //     0.4f
    // }));

    // Sphere2
    m_sceneObjects.emplace_back(SceneObject({
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        0.5f
    }));

    m_materials.emplace_back(PBRMaterial({
        glm::vec3(0.0f, 0.0f, 0.0f),
        0.2f,
        0.8f,
        0.4f
    }));

    // // Sphere3
    // m_sceneObjects.emplace_back(SceneObject({
    //     glm::vec3(2.0f, 0.0f, 0.0f),
    //     glm::vec3(1.0f, 1.0f, 1.0f),
    //     glm::vec3(0.0f, 0.0f, 0.0f),
    //     0.5f
    // }));

    // m_materials.emplace_back(PBRMaterial({
    //     glm::vec3(0.0f, 0.0f, 1.0f),
    //     0.2f,
    //     0.8f,
    //     0.4f
    // }));


    // Lights
    m_lights.emplace_back(PointLight({
        glm::vec3(3.0f, 3.0f, 2.0f),
        glm::vec3(1.0f, 0.8f, 0.4f),
        0.8f
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
    ImGui::Text("Spherical Objects");
    std::string object_name = "Sphere";
    // Spheres
    for(int i = 0; i < m_sceneObjects.size(); i++) 
    {
        std::string name = object_name + std::to_string(i) + "Position";
        std::string x_name = object_name + "x";
        std::string y_name = object_name + "y";
        std::string z_name = object_name + "z";
        ImGui::SliderFloat(x_name.c_str(), &m_sceneObjects[i].Position.x, -1.0f, 1.0f);
        ImGui::SliderFloat(y_name.c_str(), &m_sceneObjects[i].Position.y, -1.0f, 1.0f);
        ImGui::SliderFloat(z_name.c_str(), &m_sceneObjects[i].Position.z, -1.0f, 1.0f);
    }

    ImGui::Text("Lights");
    std::string light_name = "Light";
    for(int i =0; i < m_lights.size(); i++) 
    {
        if(auto light = std::get_if<PointLight>(&m_lights[i]))
        {
            std::string name = light_name + std::to_string(i) + "Color";
            std::string r_name = light_name + "r";
            std::string g_name = light_name + "g";
            std::string b_name = light_name + "b";
            std::string i_name = "Intensity";
            ImGui::SliderFloat(r_name.c_str(), &light->Color.r, 0.0f, 1.0f);
            ImGui::SliderFloat(g_name.c_str(), &light->Color.g, 0.0f, 1.0f);
            ImGui::SliderFloat(b_name.c_str(), &light->Color.b, 0.0f, 1.0f);
            ImGui::SliderFloat(i_name.c_str(), &light->Intensity, 0.0f, 10.0f);
        }
    }

    ImGui::End();


}

void Scene::PushSceneToRenderer() 
{
    Renderer::SetActiveScene(std::make_shared<Scene>(*this));
}
