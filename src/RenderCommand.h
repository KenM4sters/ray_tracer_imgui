#pragma once
#include "Core.h"

/**
 * The RenderCommand class a unified version of what would normally be 2 indivdual
 * classes (Renderer and RenderAPI), since we won't actually be using graphics APIs ourselves
 * very often in this project. They're really only here so that ImGUI can use them to draw
 * our interface, but we will eventually end up ray tracing on the GPU, which will require
 * the use of (probably) Vulkan.
 * 
 * OpenGL is a lot simpler for now though to get things up and running.
*/

// Messing around with bitwise operators - could just use the OpenGL ones.
enum BufferBits {
    COLOR = 1 << 0,
    DEPTH = 1 << 2,
    STENCIL = 1 << 3
};
enum TestFlags {
    DEPTH = 1 << 0,
    STENCIL = 1 << 1
};

class RenderCommand {
    public:
        static void Flush(uint32_t flags);
        static void SetClearColor(glm::vec4 color);
        static void SwapBuffers(GLFWwindow* window);
        static void ListenToEvents();
        static void SetViewportDimensions(uint32_t width, uint32_t height);
        static void Enable(uint32_t flags);
};