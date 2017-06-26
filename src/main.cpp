#include <iostream>

#include <SDL2/SDL.h>

#include <lib/glm/glm.hpp>
#include <lib/glm/gtc/matrix_transform.hpp>
#include <lib/glm/gtc/type_ptr.hpp>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/core/window.hpp>
#include <CSE/CSELL/core/sdlwindow.hpp>
#include <CSE/CSELL/core/inputcallbackhandler.hpp>

#include <CSE/CSELL/asset/assetmanager.hpp>
#include <CSE/CSELL/asset/image.hpp>
#include <CSE/CSELL/asset/text.hpp>

#include <CSE/CSELL/render/renderer.hpp>
#include <CSE/CSELL/render/gl/glrendererimple.hpp>
#include <CSE/CSELL/render/gl/glshader.hpp>
#include <CSE/CSELL/render/gl/glshaderprogram.hpp>
#include <CSE/CSELL/render/gl/gltexture.hpp>

static bool running = true;
static const char *WINDOW_TITLE = "EVABEVAdoesnotSUX";
static const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;

static CSELL::Render::ShaderProgram *shaderProgram;

static CSELL::Core::Window *window;
static CSELL::Render::Renderer *renderer;
static CSELL::Render::Mesh *mesh;

void serpinski(float tx, float ty, float lx, float ly, float rx, float ry, int depth, float scale) {
    glm::mat4 temp;
    temp = glm::translate(temp, glm::vec3((tx+lx+rx)/3.0f,(ty+ly+ry)/3.0f,0.0f));
    temp = glm::rotate(temp, (depth%2 == 1? -1:1)*(float)window->getTime(), glm::vec3(0.0, 0.0, 1.0));
    temp = glm::scale(temp, glm::vec3(scale,scale,scale));
    shaderProgram->setMat4f("transform", glm::value_ptr(temp));

    mesh->renderMesh();

    if (depth == 1) {
        return;
    }
    serpinski(tx,ty,(tx+lx)/2.0f,(ty+ly)/2.0f,(tx+rx)/2.0f,(ty+ry)/2.0f,depth-1,scale/2.0f);
    serpinski((tx+lx)/2.0f,(ty+ly)/2.0f,lx,ly,(lx+rx)/2.0f,(ly+ry)/2.0f,depth-1,scale/2.0f);
    serpinski((tx+rx)/2.0f,(ty+ry)/2.0f,(lx+rx)/2.0f,(ly+ry)/2.0f,rx,ry,depth-1,scale/2.0f);
}

class TestCallbackHandler : public CSELL::Core::InputCallbackHandler {
    void handleKeyInput(InputCallbackHandler::KeyboardKey key, InputCallbackHandler::InputAction action) {
        if (key == InputCallbackHandler::K_ESCAPE && action == InputCallbackHandler::ACTION_PRESS) {
            running = false;
        }
        if (key == InputCallbackHandler::K_SPACE) {
            if (action == InputCallbackHandler::ACTION_PRESS) {
                renderer->setPolygonMode(true);
            } else if (action == InputCallbackHandler::ACTION_RELEASE) {
                renderer->setPolygonMode(false);
            }
        }
        if (key == InputCallbackHandler::K_TAB) {
            if (action == InputCallbackHandler::ACTION_PRESS) {
                window->setCursorMode(false);
            } else if (action == InputCallbackHandler::ACTION_RELEASE) {
                window->setCursorMode(true);
            }
        }
    }

    void handleMousePosInput(double xpos, double ypos, double xrel, double yrel) {
        //std::cout << xpos << ", " << ypos << " | " << xrel << ", " << yrel << std::endl;
    }

    void handleMouseButtonInput(InputCallbackHandler::MouseButton button, InputCallbackHandler::InputAction action) {
        if (button == InputCallbackHandler::MOUSE_UNKNOWN) {
            CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::CSELL, "Main", "Random Mouse Pressed");
        }
    }
    void handleMouseScrollInput(double xoffset, double yoffset) {}
    void handleMouseEnterLeaveInput(bool entered) {}

    void handleWindowResizeInput(unsigned int width, unsigned int height) {
        renderer->setViewport(0, 0, width, height);
    }
    void handleWindowCloseInput() {
        running = false;
    };
};

int main(int argc, char *argv[]) {
    // init assetManager
    CSELL::Assets::AssetManager::initialize();

    SDL_Init(SDL_INIT_EVERYTHING);

    window = new CSELL::Core::SDLWindow();

    CSELL::Core::Window::Settings windowSettings;
    windowSettings.width = SCREEN_WIDTH;
    windowSettings.height = SCREEN_HEIGHT;
    windowSettings.title = WINDOW_TITLE;
    windowSettings.resizeable = true;

    if (!window->initialize(windowSettings)) {
        window->destroy();
        SDL_Quit();
        return -1;
    }

    TestCallbackHandler handler;

    window->registerInputCallbackHandler(&handler);

    CSELL::Render::GLRendererImple glrimple;
    renderer = CSELL::Render::Renderer::newRenderer(window, &glrimple);

    renderer->makeActiveRenderer();

    renderer->setViewport(0, 0, 800, 600); // Plswerk ;~;

    // Set up shaders :3
    CSELL::Assets::TextAsset *shaderContent;
    CSELL::Render::Shader *fragmentShader, *vertexShader;

    shaderContent = CSELL::Assets::AssetManager::loadFile("assets/shaders/fragmentShader1.fs");
    fragmentShader = renderer->newShader(shaderContent->getContents()->c_str(),
                                         CSELL::Render::Shader::FRAGMENT_SHADER);

    CSELL::Assets::AssetManager::freeAsset(shaderContent);

    shaderContent = CSELL::Assets::AssetManager::loadFile("assets/shaders/vertexShader1.vs");
    vertexShader = renderer->newShader(shaderContent->getContents()->c_str(),
                                       CSELL::Render::Shader::VERTEX_SHADER);

    CSELL::Assets::AssetManager::freeAsset(shaderContent);

    shaderProgram = renderer->newShaderProgram();
    shaderProgram->attachShader(vertexShader);
    shaderProgram->attachShader(fragmentShader);
    shaderProgram->linkShaderProgram();

    renderer->deleteShader(fragmentShader);
    fragmentShader = NULL;

    renderer->deleteShader(vertexShader);
    vertexShader = NULL;

    // Set up texture

    CSELL::Assets::ImageAsset *img = CSELL::Assets::AssetManager::loadImage("assets/textures/texturesLesson/container.jpg");
    CSELL::Render::Texture *tex1 = renderer->newTexture(img->width(), img->height(), img->data());

    CSELL::Assets::AssetManager::freeAsset(img);

    img = CSELL::Assets::AssetManager::loadImage("assets/textures/texturesLesson/awesomeface.png");
    CSELL::Render::Texture *tex2 = renderer->newTexture(img->width(), img->height(), img->data());

    CSELL::Assets::AssetManager::freeAsset(img);

    // set up mesh
    const CSELL::Render::Mesh::Vertex vertices[] = {{{-0.5f,  -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
                                                    {{0.5f,  -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
                                                    {{0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
                                                    {{-0.5f,  0.5f, 0.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f}}};
    unsigned int elements[] = {0,1,2,0,2,3};

    mesh = renderer->newMesh(4, vertices, 6, elements);

    //begin program
    mesh->useMesh();

    shaderProgram->useShaderProgram();
    shaderProgram->setInt("tex1", 0);
    shaderProgram->setInt("tex2", 1);

    while(running) {
        // Draw stuff
        renderer->clearColour(0.53f, 0.88f, 0.98f, 1.0f);

        tex1->useActiveTexture(0);
        tex2->useActiveTexture(1);

        serpinski(0.0f,1.0f,-1.0f,-1.0f,1.0f,-1.0f,5,0.65f);

        // display.flip
        window->update();
    }

    renderer->deleteShaderProgram(shaderProgram);
    shaderProgram = NULL;

    renderer->deleteTexture(tex1);
    tex1 = NULL;

    renderer->deleteTexture(tex2);
    tex2 = NULL;

    renderer->deleteMesh(mesh);
    mesh = NULL;

    delete renderer;

    window->destroy();
    SDL_Quit();
    CSELL::Assets::AssetManager::shutdown();
    return 0;
}
