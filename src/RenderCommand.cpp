#include "RenderCommand.h"


void RenderCommand::Flush(uint32_t flags) 
{
    if(flags & BufferBits::COLOR) glClear(GL_COLOR_BUFFER_BIT);
    if(flags & BufferBits::DEPTH) glClear(GL_DEPTH_BUFFER_BIT);
    if(flags & BufferBits::STENCIL) glClear(GL_STENCIL_BUFFER_BIT);
}

void RenderCommand::SetClearColor(glm::vec4 color) 
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void RenderCommand::SwapBuffers(GLFWwindow* window) 
{
    glfwSwapBuffers(window);
}

void RenderCommand::ListenToEvents() 
{
    glfwPollEvents();
}

void RenderCommand::SetViewportDimensions(uint32_t width, uint32_t height) 
{
    glViewport(0, 0, width, height);
}

void RenderCommand::Enable(uint32_t flags) 
{
    if(flags & TestFlags::DEPTH) glEnable(GL_DEPTH_TEST);
    if(flags & TestFlags::STENCIL) glEnable(GL_STENCIL_TEST);
}
