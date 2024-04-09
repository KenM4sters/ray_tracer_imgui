#include "App.h"
#include "Context/OpenGL/OpenGLContext.h"
#include "RenderCommand.h"
#include "Window.h"


InputState KEY_W = INACTIVE; // Global 
InputState KEY_A = INACTIVE; // Global 
InputState KEY_S = INACTIVE; // Global 
InputState KEY_D = INACTIVE; // Global 
InputState KEY_Q = INACTIVE; // Global 
InputState KEY_E = INACTIVE; // Global 

static void on_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto p_window = static_cast<Window*>(glfwGetWindowUserPointer(window));
    switch(key) 
    {
        case GLFW_KEY_ESCAPE:
            if(action == GLFW_PRESS) p_window->SetStatus(false);
            break;
        case GLFW_KEY_SPACE:
            if(action == GLFW_PRESS) std::cout << "SPACE_BAR pressed!" << std::endl;
            break;
        case GLFW_KEY_W:
            if(action == GLFW_PRESS) std::cout << "W key pressed!" << std::endl; 
            break;
        case GLFW_KEY_A:
            if(action == GLFW_PRESS) std::cout << "A key pressed!" << std::endl; 
            break;
        case GLFW_KEY_S:
            if(action == GLFW_PRESS) std::cout << "S key pressed!" << std::endl;
            break;
        case GLFW_KEY_D:
            if(action == GLFW_PRESS) std::cout << "D key pressed!" << std::endl;
            break;
    } 
}

static void on_mouse_move_callback(GLFWwindow* window, double pos_x, double pos_y) {
    auto p_window = static_cast<Window*>(glfwGetWindowUserPointer(window));
    WindowProps props = p_window->GetWindowProps();

    props.MousePosX = static_cast<float>(pos_x);
    props.MousePosY = static_cast<float>(pos_y);

    if(props.MouseIn) {
        props.PrevMousePosX = props.MousePosX;
        props.PrevMousePosY = props.MousePosY;
        props.MouseIn = false;
    }
    float x_offset = props.MousePosX - props.PrevMousePosX;
    float y_offset = props.PrevMousePosY - props.MousePosY ; // Inverted since up vector is (0, 1, 0)
    props.PrevMousePosX = props.MousePosX;
    props.PrevMousePosY = props.MousePosY;
}

static void on_window_resize_callback(GLFWwindow* window, int width, int height) {
    auto p_window = static_cast<Window*>(glfwGetWindowUserPointer(window));
    App& app = App::GetInstance();
    p_window->HandleResize(width, height);

}

static void on_window_close_callback(GLFWwindow* window) 
{
    auto p_window = static_cast<Window*>(glfwGetWindowUserPointer(window));
    p_window->SetStatus(false);
}

Window::Window(std::string name, uint16_t w, uint16_t h)
{
    m_windowProps.Name = name;
    m_windowProps.Width = w;
    m_windowProps.Height = h;

    glfwInit();
    m_context = std::make_shared<OpenGLContext>(this);
    m_context->Init();  
    m_window = glfwCreateWindow(m_windowProps.Width, m_windowProps.Height, m_windowProps.Name.c_str(), nullptr, nullptr);
    
    std::cout<<"INITIALIZING::GLFWWindow"<<std::endl;
    if(m_window == nullptr) {
        std::cout << "FAILED to create GLFW window!" << std::endl;
    }

    // The following functions are glfw-specific callback functions, where the 2nd parameter
    // takes in one of our application functions and fillts its parameters with the appropriate
    // data. 
    //----------------------------------------------------------------
    glfwSetWindowUserPointer(m_window, this);
    glfwSetKeyCallback(m_window, on_key_callback);
    glfwSetCursorPosCallback(m_window, on_mouse_move_callback);
    glfwSetFramebufferSizeCallback(m_window, on_window_resize_callback);
    glfwMakeContextCurrent(m_window);
    glfwSetWindowCloseCallback(m_window, on_window_close_callback);
    //----------------------------------------------------------------

    // In order to use modern OpenGL (and updated version of OpenGL with more functions, types etc...), 
    // we need to load a library that allows us to access the updated api.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "FAILED to initialize GLAD" << std::endl;
    }

    RenderCommand::Enable(BufferBits::DEPTH);
    RenderCommand::SetViewportDimensions(800*2, 600*2); // (w * h)*pixel ratio of the screen in use (which is 2 for me).
}

void Window::PreRender() 
{
    RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
    RenderCommand::Flush(BufferBits::COLOR | BufferBits::DEPTH);
}
void Window::PostRender() 
{
    RenderCommand::ListenToEvents();
    RenderCommand::SwapBuffers(m_window);
    HandleUserInput();
}

void Window::HandleResize(uint32_t w, uint32_t h) 
{
    RenderCommand::SetViewportDimensions(w, h);
}

void Window::HandleUserInput() 
{
    // Rest InputState keys to inactive at the beginning of each frame.
    KEY_W = INACTIVE;
    KEY_A = INACTIVE;
    KEY_S = INACTIVE;
    KEY_D = INACTIVE;
    KEY_Q = INACTIVE;
    KEY_E = INACTIVE;

    // Test each and hold that state for the rest of the frame.
    if(glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS) { KEY_W = ACTIVE;}
    if(glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS) { KEY_A = ACTIVE;}
    if(glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS) { KEY_S = ACTIVE;}
    if(glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS) { KEY_D = ACTIVE;}
    if(glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS) { KEY_Q = ACTIVE;}
    if(glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS) { KEY_E = ACTIVE;}
} 

