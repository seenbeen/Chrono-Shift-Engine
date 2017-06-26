#include <lib/SDL2/SDL.h>

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

    const CSELL::Render::Mesh::Vertex vertices[] = {
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, { 0.0f, 0.0f,}},
        {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, { 1.0f, 0.0f,}},
        {{0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, { 1.0f, 1.0f,}},
        {{0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, { 1.0f, 1.0f,}},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, { 0.0f, 1.0f,}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, { 0.0f, 0.0f,}},
        {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, { 0.0f, 0.0f,}},
        {{0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, { 1.0f, 0.0f,}},
        {{0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, { 1.0f, 1.0f,}},
        {{0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, { 1.0f, 1.0f,}},
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, { 0.0f, 1.0f,}},
        {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, { 0.0f, 0.0f,}},
        {{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, { 1.0f, 0.0f,}},
        {{-0.5f,  0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, { 1.0f, 1.0f,}},
        {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, { 0.0f, 1.0f,}},
        {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, { 0.0f, 1.0f,}},
        {{-0.5f, -0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, { 0.0f, 0.0f,}},
        {{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, { 1.0f, 0.0f,}},
        {{0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, { 1.0f, 0.0f,}},
        {{0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, { 1.0f, 1.0f,}},
        {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, { 0.0f, 1.0f,}},
        {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, { 0.0f, 1.0f,}},
        {{0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, { 0.0f, 0.0f,}},
        {{0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, { 1.0f, 0.0f,}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, { 0.0f, 1.0f,}},
        {{0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, { 1.0f, 1.0f,}},
        {{0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, { 1.0f, 0.0f,}},
        {{0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, { 1.0f, 0.0f,}},
        {{-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, { 0.0f, 0.0f,}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, { 0.0f, 1.0f,}},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, { 0.0f, 1.0f,}},
        {{0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, { 1.0f, 1.0f,}},
        {{0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, { 1.0f, 0.0f,}},
        {{0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, { 1.0f, 0.0f,}},
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, { 0.0f, 0.0f,}},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, { 0.0f, 1.0f}}
    };

    unsigned int elements[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
        12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
        24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35
    };

    mesh = renderer->newMesh(36, vertices, 36, elements);

    //begin program

    glm::mat4 model, identity;
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), SCREEN_WIDTH / (float) SCREEN_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = glm::translate(identity, glm::vec3(0.0f, 0.0f, -4.0f));

    shaderProgram->useShaderProgram();

    shaderProgram->setMat4f("view", glm::value_ptr(view));
    shaderProgram->setMat4f("projection", glm::value_ptr(projection));

    shaderProgram->setInt("tex1", 0);
    shaderProgram->setInt("tex2", 1);
    tex1->useActiveTexture(0);
    tex2->useActiveTexture(1);

    mesh->useMesh();

    glm::vec3 cubePositions[] = {
      glm::vec3( 0.0f,  0.0f,  0.0f),
      glm::vec3( 2.0f,  5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f),
      glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3( 2.4f, -0.4f, -3.5f),
      glm::vec3(-1.7f,  3.0f, -7.5f),
      glm::vec3( 1.3f, -2.0f, -2.5f),
      glm::vec3( 1.5f,  2.0f, -2.5f),
      glm::vec3( 1.5f,  0.2f, -1.5f),
      glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    while(running) {
        // Draw stuff
        renderer->clearColour(0.0f, 0.0f, 0.0f, 1.0f);
        renderer->clearDepth(1.0f);
        for(unsigned int i = 0; i < 10; i++) {
            model = glm::translate(identity, cubePositions[i]);
            float angle = glm::radians(20.0f * i) + window->getTime() * glm::radians(60.0f);
            model = glm::rotate(model, (i%2 ? 1 : -1)*angle, glm::vec3(1.0f, 0.3f, 0.5f));
            shaderProgram->setMat4f("model", glm::value_ptr(model));
            mesh->renderMesh();
        }
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
