#include "Core.h"
#include "Interface/Interface.h"
#include "Scene.h"
#include "App.h"

/**
 * Main entry point - acts as a small abstraction from the App class to seperate core functionality
 * from implementation. 
*/

class Reach : public App {
    public:
        Reach(std::string name, uint16_t w, uint16_t h)
            : App(name, w, h) 
        {
            PushLayer(new Scene());
            PushOverlay(new Interface());
        }
        ~Reach() 
        {
            for(const auto& layer : *m_layerStack) 
            {
                delete layer;
            }
        }
};


int main() {
    std::unique_ptr<Reach> reach = std::make_unique<Reach>("Reach", 800, 600);
    reach->Run();
    return 0;
}