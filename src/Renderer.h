#pragma once
#include "Layer.h"
#include "Scene.h"
#include "Image.h"
#include "Camera.h"
#include "Raytracer.h"

/**
 * Trying out a different application architecture this time for the Renderer, in which
 * the renderer inherits from the Layer class and sits between the ImGUI interface and the Scene.
 * 
 * You can see that there's a couple of static functions here that are used exclusively by the 
 * scene and the raytracer. I really like using static functions instead of passing parameters
 * around everywhere, for example to constructors, but I'm aware of the dangers of having globally accesible functions
 * and variables, so I'm mostly just experimenting here. 
 *
*/

class Renderer : public Layer {
    public:
        Renderer(std::shared_ptr<PerspectiveCamera>* camera); // Experiment - Is Passing a raw pointer to a shared_ptr ever worth it for the smaller memory overhead?
        ~Renderer() {}

        void OnAttach() override;
        void OnDetach() override;
        void Update() override; 
        void UpdateInterface() override;
        static void SetActiveScene(std::shared_ptr<Scene> scene);
        static inline const std::shared_ptr<const Scene> GetActiveScene() { return m_scene;}
    private:
        void PrepareImage();
        void PassImage();
        void Render();
        glm::vec4 RayGen(uint32_t x, uint32_t y);

    private:
        std::shared_ptr<Image> m_image = nullptr;
        uint32_t* m_sceneData = nullptr;
        uint32_t m_viewportWidth = 0;
        uint32_t m_viewportHeight = 0;

        // Playing around with two different ways of obtaining important information from the scene and camera.
        static std::shared_ptr<Scene> m_scene;
        std::shared_ptr<PerspectiveCamera> m_camera = nullptr;


};