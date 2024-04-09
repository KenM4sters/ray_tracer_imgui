#include "Core.h"
#include "Interface/Interface.h"
#include "Scene.h"
#include "App.h"
#include "Renderer.h"
#include "Camera.h"

/**
 * Main entry point - acts as a small abstraction from the App class to seperate core functionality
 * from implementation. 
*/

class WolfRayet : public App {
    public:
        WolfRayet(std::string name, uint16_t w, uint16_t h)
            : App(name, w, h) 
        {
            if(m_window) 
            {
                const auto& props = m_window->GetWindowProps();
                m_camera = std::make_shared<PerspectiveCamera>(45.0f, 0.1f, 100.0f);
            }
            PushLayer(new Scene());
            PushLayer(new Renderer(&m_camera));
            PushOverlay(new Interface());
        }
        ~WolfRayet() 
        {
            
        }
    private:
        std::shared_ptr<PerspectiveCamera> m_camera = nullptr;
};


int main() {
    std::unique_ptr<WolfRayet> wolf_rayet = std::make_unique<WolfRayet>("WolfRayet", 800, 600);
    wolf_rayet->Run();
    return 0;
}