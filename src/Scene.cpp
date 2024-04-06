#include "Scene.h"
#include "Interface/Interface.h"
#include "Renderer.h"
Scene::Scene()
    : Layer("Scene")
{
    // Test Sphere.
    m_sceneObjects.emplace_back(SceneObject({
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        2.0f
    }));

    m_materials.emplace_back(PBRMaterial({
        glm::vec3(1.0f),
        0.2f,
        0.8f,
        0.4f
    }));
}

void Scene::OnAttach() {
    PushObjectsToRenderer();
}

void Scene::OnDetach() {
}

void Scene::Update() {}


void Scene::UpdateInterface() 
{

}

void Scene::PushObjectsToRenderer() 
{
    Renderer::InsertSceneObjects(std::make_shared<std::vector<SceneObject>>(m_sceneObjects));
}
