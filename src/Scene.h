#pragma once
#include "Layer.h"

class Scene : public Layer {
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