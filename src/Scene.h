#pragma once
#include "Layer.h"
#include "Image.h"

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

class Scene : public Layer {
    public:
        Scene();
        ~Scene() {
            OnDetach();
        }
        void OnAttach() override;
        void OnDetach() override;
        Layer* Update(Layer* prev_result) override; // Currently does nothing, since we're not moving objects/lights/cameras currently.
        void PrepareImage();
        void PassImage();
        void UpdateInterface() override;
        uint32_t GetWidth() {return m_viewportWidth;}
    private:
        std::shared_ptr<Image> m_image = nullptr;
        uint32_t* m_sceneData = nullptr;
        uint32_t m_viewportWidth = 0;
        uint32_t m_viewportHeight = 0;

};