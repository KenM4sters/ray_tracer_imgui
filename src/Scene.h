#pragma once
#include "Layer.h"
#include "Image.h"

// Each object in our scene is an instance of this struct and are added to a container of Scene Objects
// which our renderer loops through.
struct SceneObject {
    glm::vec3 Position{0.0f};
    glm::vec3 Scale{1.0f};
    glm::vec3 Rotation{0.0f};
    float Radius = 0.5f;

    uint32_t MaterialIndex = 0;
};

// Each SceneObjet has a respective PBRMaterial that helps the renderer to shade the scene object in realistic way.
struct PBRMaterial {
    glm::vec3 Albedo{1.0f};
    float Metallic = 0.2;
    float Roughness = 0.8;
    float A0 = 0.4f;
};

// The simplest type of light in our scene - emits 360deg light of some color and intensity (brightness).
struct PointLight {
    glm::vec3 Position{0.0f};
    glm::vec3 Colour{1.0f, 1.0f, 0.5f};
    float Intensity = 1.0f;
};

/**
 * The main Scene class is responsible for the prepartion and delivery of the most important 
 * aspect of this application - the texture itself that displays our scene. 
 * 
 * To start with, All parts of that pipepline will be handled here, from preparing textures, to
 * generating scene objects, to casting rays, but eventually they'll be moved into their own 
 * classes once things get more complicated.
 * 
 * This class needs to inherit from the Layer class so that the main App can loop through its
 * functions in the right order: 
 * - (OnAttach() -> Begin() -> End() -> OnImGUIUpdate() -> OnDetach()).
 * 
 * NOTES:
 * - As you can see, there are two member variables that are containers of SceneObjects and PBRMaterials 
 * respectively. This is a new design that I'm tesiting out which I really like the idea of, where
 * instead of each scene object holding a material object, it simply holds a uint32_t index into
 * the material's container where the appropriate material can be pulled.
 * 
*/
class Scene : public Layer {
    public:
        Scene();
        ~Scene() {
            OnDetach();
        }
        void OnAttach() override;
        void OnDetach() override;
        void Update() override; // Currently does nothing, since we're not moving objects/lights/cameras currently.
        void UpdateInterface() override;
        void PushSceneToRenderer();

        // Getters
        inline const std::shared_ptr<std::vector<SceneObject>> GetSceneObjects() const { return std::make_shared<std::vector<SceneObject>>(m_sceneObjects); }
        inline const std::shared_ptr<std::vector<PBRMaterial>> GetPBRMaterials() const { return std::make_shared<std::vector<PBRMaterial>>(m_materials); }
        inline const std::shared_ptr<Image> GetBackgroundImageData() const { return std::make_shared<Image>(m_backgroundImage); }
        inline const std::shared_ptr<std::vector<std::variant<PointLight>>> GetLights() const {return std::make_shared<std::vector<std::variant<PointLight>>>(m_lights); }

    private:
        std::vector<SceneObject> m_sceneObjects; 
        std::vector<PBRMaterial> m_materials;
        std::vector<std::variant<PointLight>> m_lights; // Wanted to try out std::variant here since I've heard that it's faster at runtime than relying on polymorphism(?).
        Image m_backgroundImage;
};

