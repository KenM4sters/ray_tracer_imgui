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
*/

struct SceneObject {
    glm::vec3 Position;
    glm::vec3 Scale;
    glm::vec3 Rotation;
    float Radius = 10;
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
        void PushObjectsToRenderer();
    private:
        std::vector<SceneObject> m_sceneObjects; 

};