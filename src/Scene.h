#pragma once
#include "Layer.h"

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
 * - As you can see, the only member variables are two containers of SceneObjects and PBRMaterials
 * respectively. This is a new design that I'm tesiting out which I really like the idea of, where
 * instead of each scene object holding a material object, it simply holds a uint32_t index into
 * the material's container where the appropraite material can be pulled.
 * 
 * I've got high hopes for this new design and am very excited to see how well it works in the
 * application. 
 * 
*/

struct SceneObject {
    glm::vec3 Position{0.0f};
    glm::vec3 Scale{1.0f};
    glm::vec3 Rotation{0.0f};
    float Radius = 2.0f;

    uint32_t MaterialIndex = 0;
};

struct PBRMaterial {
    glm::vec3 Albedo{1.0f};
    float Metallic = 0.2;
    float Roughness = 0.8;
    float A0 = 0.4f;
};



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
    private:
        std::vector<SceneObject> m_sceneObjects; 
        std::vector<PBRMaterial> m_materials;

};