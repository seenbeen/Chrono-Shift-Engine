#include <string>
#include <map>

#include <lib/glad/glad.h>
#include <lib/glfw/glfw3.h>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/core/glfwwindow.hpp>

namespace CSELL { namespace Core {
    static std::map<GLFWwindow *, GlfwWindow *> glfwWindowManager;

    // some todos: translate each of these "inputs" into a unified, framework independent set

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        glfwWindowManager.find(window)->second->handleKeyInput(key, action, mods);
    }

    static void mousePosCallback(GLFWwindow* window, double xpos, double ypos) {
        glfwWindowManager.find(window)->second->handleMousePosInput(xpos, ypos);
    }

    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
        glfwWindowManager.find(window)->second->handleMouseButtonInput(button, action, mods);
    }

    static void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
        glfwWindowManager.find(window)->second->handleMouseScrollInput(xoffset, yoffset);
    }

    static void mouseEnterLeaveCallback(GLFWwindow* window, int entered) {
        glfwWindowManager.find(window)->second->handleMouseEnterLeaveInput(entered);
    }

    bool GlfwWindow::initializeImplementation(Window::Settings settings) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, settings.resizeable);

        this->windowWidth = settings.width;
        this->windowHeight = settings.height;
        this->windowTitle = settings.title;

        // Set up GL Window

        this->window = glfwCreateWindow(this->windowWidth, this->windowHeight, this->windowTitle.c_str(), NULL, NULL);

        if (this->window == NULL) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL, "RenderEngine", "GLFW Unable to create window!");
            return false;
        }

        glfwMakeContextCurrent(this->window);


        // Set up glad loader to load in gl procs
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL, "RenderEngine", "Failed to initialize GLAD!");
            return false;
        }

        glfwWindowManager[this->window] = this;

        return true;
    }

    void GlfwWindow::destroyImplementation() {
        glfwWindowManager.erase(glfwWindowManager.find(this->window));
        glfwDestroyWindow(window);
    }

    void GlfwWindow::updateImplementation() {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    double GlfwWindow::getTimeImplementation() {
        return glfwGetTime();
    }

    void GlfwWindow::useContextImplementation() {
        glfwMakeContextCurrent(this->window);
    }
}}
