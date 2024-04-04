#pragma once
#include "Layer.h"

class Scene : Layer {
    public:
        Scene();
        ~Scene() {
            OnDetach();
        }
        void OnAttach() override;
        void OnDetach() override;
        void Begin() override; 
        void End() override; 

};