#ifndef CSELL_CORE_GLFWWINDOW_HPP
#define CSELL_CORE_GLFWWINDOW_HPP

#include <string>

#include <lib/glad/glad.h>
#include <lib/glfw/glfw3.h>

#include <CSE/CSELL/core/window.hpp>
#include <CSE/CSELL/core/inputcallbackhandler.hpp>

namespace CSELL { namespace Core {
    class GlfwWindow : public Window {
        unsigned int windowWidth, windowHeight;
        std::string windowTitle;
        GLFWwindow *window;

    protected:
        bool initializeImplementation(Window::Settings settings);
        void destroyImplementation();
        void updateImplementation();
        double getTimeImplementation();
        void useContextImplementation();
    };
}}

#endif
