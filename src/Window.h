#pragma once
#include "Core.h"
#include "GraphicsContext.h"


// Since this application doesn't really involve much user interaction (we can only move the camera around)
// I've just defined a really simple global state variable that holds the current state of important
// keys. 
enum InputState {
    INACTIVE,
    ACTIVE
};

extern InputState KEY_W; // Global 
extern InputState KEY_A; // Global 
extern InputState KEY_S; // Global 
extern InputState KEY_D; // Global 
extern InputState KEY_Q; // Global 
extern InputState KEY_E; // Global 

/**
 * The Window class is resonsible for handling everything to do with our window, from simply
 * setting it up (using GLFW), creating a graphics context and handling user input.
*/

struct WindowProps {
    uint16_t Width = 600;
    uint16_t Height = 800;
    std::string Name;

    uint16_t MousePosX = 0;
    uint16_t MousePosY = 0;
    uint16_t PrevMousePosX = 0;
    uint16_t PrevMousePosY = 0;
    bool MouseIn = false;
};

class Window {
    public:
        Window(std::string name, uint16_t w, uint16_t h);
        ~Window() {}
        void PreRender();
        void PostRender();
        void HandleUserInput();

        // Getters
        inline GLFWwindow* GetNativeWindow() const {return m_window;}
        inline void SetNativeWindow(GLFWwindow* window) {m_window = window;}
        inline bool IsRunning() const {return m_isRunning;}
        inline void SetStatus(bool status) {m_isRunning = status;}
        void HandleResize(uint32_t w, uint32_t h); 
        inline WindowProps GetWindowProps() const {return m_windowProps;}

    private:
        GLFWwindow* m_window = nullptr;
        std::shared_ptr<GraphicsContext> m_context = nullptr;
        WindowProps m_windowProps;
        bool m_isRunning = true;
};