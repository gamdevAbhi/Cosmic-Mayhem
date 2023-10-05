#ifndef WINDOW_HPP
#define WINDOW_HPP
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <windows.h>
#include <iostream>

namespace engine
{
    // engine window class for creating and displaying window
    class Window
    {
    public:
        inline static const int screen_width = GetSystemMetrics(SM_CXSCREEN);
        inline static const int screen_height = GetSystemMetrics(SM_CYSCREEN);
        std::tuple<int, int> getSize();
        void makeWindowClose();
    private:
        explicit Window(const char* title, int width, int height);
        void updateWindow();
        void close();
        bool shouldClose();
        GLFWwindow* getWindow();
        GLFWwindow* glfwWindow;
        friend class Input;
    };
}

#endif