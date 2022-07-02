#pragma once

#include "Maple/Core/Common.h"
#include "Maple/Math/Vector2.h"

#include <glfw/glfw3.h>

namespace Maple
{
    using WindowCloseFunction  = std::function<void()>;
    using WindowMoveFunction   = std::function<void(int, int)>;
    using WindowResizeFunction = std::function<void(uint32_t, uint32_t)>;

    struct WindowProps
    {
        Vector2<uint32_t> size;
        Vector2i position;

        const char* title;
        bool VSync;

        GLFWwindow* glfwWindow;

        WindowCloseFunction  closeEvent;
        WindowMoveFunction   moveEvent;
        WindowResizeFunction resizeEvent;
    };

    class Window
    {
    public:
        Window(const Vector2<uint32_t>& wndSize, const char* title);
        ~Window();

        void OnUpdate() const;

        bool SetVSync(bool enabled);
        bool IsVSync() const { return m_Props.VSync; }

        const char* SetTitle(const char* title);
        const char* GetTitle() const { return m_Props.title; }

        Vector2<uint32_t> SetSize(const Vector2<uint32_t>& size);
        Vector2<uint32_t> GetSize() const { return m_Props.size; }

        Vector2i SetPosition(const Vector2i& position);
        Vector2i GetPosition() const { return m_Props.position; }

        bool ShouldClose() const { return glfwWindowShouldClose(m_Props.glfwWindow); }

        WindowMoveFunction SetMoveCallback(const WindowMoveFunction& clbk) { return m_Props.moveEvent = clbk; }
        WindowResizeFunction SetResizeCallback(const WindowResizeFunction& clbk) { return m_Props.resizeEvent = clbk; }

        WindowCloseFunction SetCloseCallback(const WindowCloseFunction& clbk) { return m_Props.closeEvent = clbk; }

    private:
        void _SetWindowCallbacks();

    private:
        WindowProps m_Props;
        static uint8_t s_WindowCount;
    };

    using WindowPtr = ScopePtr<Window>;

    WindowPtr OpenWindow(const Vector2<uint32_t>& wndSize, const char* title);
    WindowPtr OpenWindow(uint32_t width, uint32_t height, const char* title);
}