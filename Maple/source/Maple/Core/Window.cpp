#include "pch.h"
#include "Maple/Core/Window.h"

#define MPL_GET_WINDOWPROPS(glfwWindow) *(WindowProps*)glfwGetWindowUserPointer(glfwWindow)

namespace Maple
{
    uint8_t Window::s_WindowCount = 0;

    static void glfwErrorCallback(int error, const char* description)
    {
        // Ex: [Maple]: GLFW Error 1, description.
        MPL_ERROR("GLFW Error {0}, {1}", error, description);
    }

    Window::Window(const Vector2<uint32_t>& wndSize, const char* title)
    {
        // If the window count equals zero, initialize GLFW and set the error callback.
        if (s_WindowCount == 0)
        {
            int initSuccess = glfwInit();
            MPL_CRIT_ASSERT(initSuccess, "Failed to initialize GLFW.");

            glfwSetErrorCallback(glfwErrorCallback);
        }

        // Create the window using GLFW and make the window's context current.
        m_Props.glfwWindow = glfwCreateWindow(wndSize.x, wndSize.y, title, nullptr, nullptr);
        glfwMakeContextCurrent(m_Props.glfwWindow);
        
        // Turn on VSync.
        SetVSync(true);

        // Set the window's members.
        m_Props.size.x = wndSize.x;
        m_Props.size.y = wndSize.y;
        m_Props.title  = title;

        glfwGetWindowPos(m_Props.glfwWindow, &m_Props.position.x, &m_Props.position.y);

        // Set the window's event callbacks.
        _SetWindowCallbacks();

        // Log the GLFW library's version.
        // Ex: Using GLFW Version 3.3.7
        MPL_LOG(
            "Using GLFW Version {0}.{1}.{2}",
            GLFW_VERSION_MAJOR,
            GLFW_VERSION_MINOR,
            GLFW_VERSION_REVISION);

        // Increment the window count.
        ++s_WindowCount;
    }

    Window::~Window()
    {
        // Decrement the window count and destroy the window.
        --s_WindowCount;
        glfwDestroyWindow(m_Props.glfwWindow);

        // Terminate GLFW if the window count equals zero.
        if (s_WindowCount == 0)
        {
            glfwTerminate();
        }
    }

    // This function should be called in the main loop.
    void Window::OnUpdate() const
    {
        glfwSwapBuffers(m_Props.glfwWindow);
        glfwPollEvents();
    }

    //=========================================//
    //===============| Setters |===============//
    //=========================================//
    
    // Set's the window's VSync.
    bool Window::SetVSync(bool enabled)
    {
        glfwSwapInterval((int)enabled);
        return m_Props.VSync = enabled;
    }

    // Sets the window's title.
    const char* Window::SetTitle(const char* title)
    {
        glfwSetWindowTitle(m_Props.glfwWindow, title);
        return m_Props.title = title;
    }

    // Sets the window's position.
    Vector2i Window::SetPosition(const Vector2i& position)
    {
        glfwSetWindowPos(m_Props.glfwWindow, position.x, position.y);
        return m_Props.position = position;
    }

    // Sets the window's size.
    Vector2<uint32_t> Window::SetSize(const Vector2<uint32_t>& size)
    {
        glfwSetWindowSize(m_Props.glfwWindow, size.x, size.y);
        return m_Props.size = size;
    }

    //===========================================//
    //===============| Callbacks |===============//
    //===========================================//

    static void _WindowCloseCallback(GLFWwindow* glfwWindow)
    {
        WindowProps& props = MPL_GET_WINDOWPROPS(glfwWindow);
        if (props.closeEvent) props.closeEvent();
    }

    static void _WindowMoveCallback(GLFWwindow* glfwWindow, int posX, int posY)
    {
        WindowProps& props = MPL_GET_WINDOWPROPS(glfwWindow);
        props.position.x = posX;
        props.position.y = posY;

        if (props.moveEvent) props.moveEvent(posX, posY);
    }

    static void _WindowSizeCallback(GLFWwindow* glfwWindow, int sizeX, int sizeY)
    {
        WindowProps& props = MPL_GET_WINDOWPROPS(glfwWindow);
        props.size.x = sizeX;
        props.size.y = sizeY;

        if (props.resizeEvent) props.resizeEvent((uint32_t)sizeX, (uint32_t)sizeY);
    }

    void Window::_SetWindowCallbacks()
    {
        // Set the window's user-defined pointer.
        // Used for getting the window wrapper in a lambda function.
        glfwSetWindowUserPointer(m_Props.glfwWindow, (void*)&m_Props);

        // Set window close callback.
        glfwSetWindowCloseCallback(m_Props.glfwWindow, _WindowCloseCallback);

        // Set window position callback.
        glfwSetWindowPosCallback(m_Props.glfwWindow, _WindowMoveCallback);

        // Set window resize callback.
        glfwSetWindowSizeCallback(m_Props.glfwWindow, _WindowSizeCallback);
    }

    //=============================================//
    //===============| Not Setters |===============//
    //=============================================//

    // Opens a window.
    WindowPtr OpenWindow(const Vector2<uint32_t>& wndSize, const char* title)
    {
        return MakeScope<Window>(wndSize, title);
    }

    // Opens a window.
    WindowPtr OpenWindow(uint32_t width, uint32_t height, const char* title)
    {
        return MakeScope<Window>(
            Vector2<uint32_t>(width, height),
            title);
    }
}

#undef MPL_GET_WINDOWPROPS