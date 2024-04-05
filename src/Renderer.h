#pragma once
#include "Layer.h"

/**
 * Trying out a different application architecture this time for the Renderer, in which
 * the renderer inherits from the Layer class and sits between the 
*/

class Renderer : public Layer {
    public:
        Renderer() {}
        ~Renderer() {}

        void OnAttach() override;
        void OnDetach() override;
        void Update() override; // Currently does nothing, since we're not moving objects/lights/cameras currently.
        void PrepareImage();
        void PassImage();
        void UpdateInterface() override;
        void Render();
    private:

};