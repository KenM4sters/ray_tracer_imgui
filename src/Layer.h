#pragma once
#include "Core.h"

class Layer {
    public:
        Layer(const std::string& name = "Layer")
            : m_debugName(name) 
        {

        }
        virtual ~Layer() {}

        virtual void OnAttach() = 0;
        virtual void OnDetach() = 0;
        // Some layers may or may not need a mismatch of these functions, so we'll make it 
        // optional to override them.
        virtual Layer* Update(Layer* prev_result) {}
        virtual void UpdateInterface() {};
        virtual void Begin() {}
        virtual void End() {}
        inline std::string GetName() const { return m_debugName; }

        bool m_shouldUpdate = true;
    private:
        std::string m_debugName;
};