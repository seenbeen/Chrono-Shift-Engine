#include <iostream>

#include <lib/glm/glm.hpp>
#include <lib/glm/gtc/matrix_transform.hpp>
#include <lib/glm/gtc/type_ptr.hpp>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/core/window.hpp>
#include <CSE/CSELL/core/glfwwindow.hpp>

#include <CSE/CSELL/asset/assetmanager.hpp>
#include <CSE/CSELL/asset/image.hpp>
#include <CSE/CSELL/renderer/shaders.hpp>
#include <CSE/CSELL/renderer/texture.hpp>

// le initializer
bool init(const char *windowTitle, const int windowWidth, const int windowHeight, GLFWwindow *&window);
// le window resizer
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// input handler
void processInput(GLFWwindow *window);

const char *WINDOW_TITLE = "EVABEVAdoesnotSUX";
const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;

CSELL::Renderer::ShaderProgram *shaderProgram;

void serpinski(float tx, float ty, float lx, float ly, float rx, float ry, int depth, float scale) {
    glm::mat4 temp;
    temp = glm::translate(temp, glm::vec3((tx+lx+rx)/3.0f,(ty+ly+ry)/3.0f,0.0f));
    temp = glm::rotate(temp, (depth%2 == 1? -1:1)*(float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
    temp = glm::scale(temp, glm::vec3(scale,scale,scale));
    shaderProgram->setMat4fv("transform", glm::value_ptr(temp));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    if (depth == 1) {
        return;
    }
    serpinski(tx,ty,(tx+lx)/2.0f,(ty+ly)/2.0f,(tx+rx)/2.0f,(ty+ry)/2.0f,depth-1,scale/2.0f);
    serpinski((tx+lx)/2.0f,(ty+ly)/2.0f,lx,ly,(lx+rx)/2.0f,(ly+ry)/2.0f,depth-1,scale/2.0f);
    serpinski((tx+rx)/2.0f,(ty+ry)/2.0f,(lx+rx)/2.0f,(ly+ry)/2.0f,rx,ry,depth-1,scale/2.0f);
}

int main() {
    glfwInit();

    CSELL::Core::Window *window = new CSELL::Core::GlfwWindow();

    CSELL::Core::Window::Settings windowSettings;
    windowSettings.width = SCREEN_WIDTH;
    windowSettings.height = SCREEN_HEIGHT;
    windowSettings.title = WINDOW_TITLE;
    windowSettings.resizeable = false;

    if (!window->initialize(windowSettings)) {
        window->destroy();
        glfwTerminate();
        return -1;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0, 0, 800, 600); // Plswerk ;~;

    // init assetManager
    CSELL::Assets::AssetManager::initialize();

    // Set up shaders :3

    CSELL::Assets::TextAsset *shaderContent;
    CSELL::Renderer::Shader *fragmentShader, *vertexShader;

    shaderContent = CSELL::Assets::AssetManager::loadFile("assets/shaders/fragmentShader1.fs");
    fragmentShader = new CSELL::Renderer::Shader(shaderContent->getContents()->c_str(), CSELL::Renderer::Shader::FRAGMENT_SHADER);

    CSELL::Assets::AssetManager::freeAsset(shaderContent);

    shaderContent = CSELL::Assets::AssetManager::loadFile("assets/shaders/vertexShader1.vs");
    vertexShader = new CSELL::Renderer::Shader(shaderContent->getContents()->c_str(), CSELL::Renderer::Shader::VERTEX_SHADER);

    CSELL::Assets::AssetManager::freeAsset(shaderContent);

    shaderProgram = new CSELL::Renderer::ShaderProgram();

    shaderProgram->attachShader(vertexShader);
    shaderProgram->attachShader(fragmentShader);

    shaderProgram->linkProgram();

    delete fragmentShader;
    fragmentShader = NULL;

    delete vertexShader;
    vertexShader = NULL;

    // Set up texture

    // number 1
    CSELL::Assets::ImageAsset *img = CSELL::Assets::AssetManager::loadImage("assets/textures/texturesLesson/container.jpg", false);
    CSELL::Renderer::Texture *tex1 = new CSELL::Renderer::Texture(img->width(), img->height(), img->data());

    CSELL::Assets::AssetManager::freeAsset(img);

    // number 2
    img = CSELL::Assets::AssetManager::loadImage("assets/textures/texturesLesson/awesomeface.png", false);
    CSELL::Renderer::Texture *tex2 = new CSELL::Renderer::Texture(img->width(), img->height(), img->data());

    CSELL::Assets::AssetManager::freeAsset(img);


    // set up vertices
    const float vertices[] = {-0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                               0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                               0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
                              -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f};
    // set up elements
    unsigned int elements[] = {0,1,2,0,2,3};

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);


    unsigned int VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // set up vertex array obj
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // colours
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // textures
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    // begin program
    shaderProgram->setInt("tex1", 0);
    shaderProgram->setInt("tex2", 1);

    while(true) {
        // Draw stuff
        glClearColor(0.53f, 0.88f, 0.98f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram->use();
        tex1->useActiveTexture(GL_TEXTURE0);
        tex2->useActiveTexture(GL_TEXTURE1);
        glBindVertexArray(VAO);

        serpinski(0.0f,1.0f,-1.0f,-1.0f,1.0f,-1.0f,5,0.65f);

        // display.flip
        window->update();
    }

    delete shaderProgram;
    shaderProgram = NULL;

    delete tex1;
    tex1 = NULL;

    delete tex2;
    tex2 = NULL;

    CSELL::Assets::AssetManager::shutdown();

    glfwTerminate();

    return 0;
}
