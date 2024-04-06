#pragma once
#include "Layer.h"

/**
 * Trying out a different application architecture this time for the Renderer, in which
 * the renderer inherits from the Layer class and sits between the 
*/

class Renderer : public Layer {
    public:
        Renderer();
        ~Renderer() {}

        void Render();
        void PrepareImage();
        void PassImage();

        void OnAttach() override;
        void OnDetach() override;
        void UpdateInterface() override;
        Layer* Update(Layer* prev_result) override; 
    private:

};