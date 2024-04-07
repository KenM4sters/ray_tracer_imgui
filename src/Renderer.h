#pragma once
#include "Layer.h"
#include "Scene.h"
#include "Image.h"

/**
 * Trying out a different application architecture this time for the Renderer, in which
 * the renderer inherits from the Layer class and sits between the 
*/

class Renderer : public Layer {
    public:
        Renderer();
        ~Renderer() {}

        void OnAttach() override;
        void OnDetach() override;
        void Update() override; 
        void UpdateInterface() override;
        static void SetActiveScene(const std::shared_ptr<Scene> const scene);
    private:
        void PrepareImage();
        void PassImage();
        void Render();
        uint32_t FragmentShader(glm::vec2 uv);

    private:
        std::shared_ptr<Image> m_image = nullptr;
        uint32_t* m_sceneData = nullptr;
        uint32_t m_viewportWidth = 0;
        uint32_t m_viewportHeight = 0;

        static std::shared_ptr<Scene> m_scene;


};