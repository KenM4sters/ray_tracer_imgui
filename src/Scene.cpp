#include "Scene.h"
#include "Interface/Interface.h"
#include "Renderer.h"
Scene::Scene()
    : Layer("Scene")
{
    // Test Sphere.
    m_sceneObjects.emplace_back(SceneObject({
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        0.5f
    }));

    m_materials.emplace_back(PBRMaterial({
        glm::vec3(1.0f),
        0.2f,
        0.8f,
        0.4f
    }));
}

void Scene::OnAttach() {
    PushSceneToRenderer();
}

void Scene::OnDetach() {
}

void Scene::Update() {}


void Scene::UpdateInterface() 
{

}

void Scene::PushSceneToRenderer() 
{
    Renderer::SetActiveScene(std::make_shared<Scene>(*this));
}
