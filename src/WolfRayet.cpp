#include "Core.h"
#include "Interface/Interface.h"
#include "Scene.h"
#include "App.h"
#include "Renderer.h"

/**
 * Main entry point - acts as a small abstraction from the App class to seperate core functionality
 * from implementation. 
*/

class WolfRayet : public App {
    public:
        WolfRayet(std::string name, uint16_t w, uint16_t h)
            : App(name, w, h) 
        {
            PushOverlay(new Interface());
            PushLayer(new Renderer());
            PushLayer(new Scene());
        }
        ~WolfRayet() 
        {
        }
};


int main() {
    std::unique_ptr<WolfRayet> wolf_rayet = std::make_unique<WolfRayet>("WolfRayet", 800, 600);
    wolf_rayet->Run();
    return 0;
}