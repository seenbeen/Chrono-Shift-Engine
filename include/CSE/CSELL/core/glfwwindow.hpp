#ifndef CSELL_CORE_GLFWWINDOW_HPP
#define CSELL_CORE_GLFWWINDOW_HPP

#include <string>

#include <lib/glfw/glfw3.h>

#include <CSE/CSELL/core/window.hpp>

namespace CSELL { namespace Core {
    class GlfwWindow : public Window {
        unsigned int windowWidth, windowHeight;
        std::string windowTitle;
        GLFWwindow *window;
        double oMouseX, oMouseY;
        bool firstMouseMove;
    protected:
        bool initializeImplementation(Window::Settings settings);
        void destroyImplementation();
        bool updateImplementation();
        double getTimeImplementation();
        bool useContextImplementation();
        bool setCursorModeImplementation(bool enable);
    public:
        GlfwWindow();
        bool callMouseCallback(double mx, double my);
    };
}}

#endif
