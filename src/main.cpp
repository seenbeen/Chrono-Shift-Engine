#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <asset/image/image.h>
#include <asset/shader/shaders.h>
#include <asset/texture/texture.h>

// le initializer
bool init(const char *windowTitle, const int windowWidth, const int windowHeight, GLFWwindow *&window);
// le window resizer
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// input handler
void processInput(GLFWwindow *window);

const char *WINDOW_TITLE = "EVABEVAdoesnotSUX";
const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;
ShaderProgram *shaderProgram;

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

    GLFWwindow *window = NULL;

    if (!init(WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT, window)) {
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // register our callback


    glViewport(400, 300, 800/2, 600/2); // Plswerk ;~;

    // Set up shaders :3

    Shader *fragmentShader = new Shader("assets/shaders/fragmentShader1.fs",GL_FRAGMENT_SHADER);
    Shader *vertexShader = new Shader("assets/shaders/vertexShader1.vs",GL_VERTEX_SHADER);

    shaderProgram = new ShaderProgram();

    shaderProgram->attachShader(vertexShader);
    shaderProgram->attachShader(fragmentShader);

    shaderProgram->linkProgram();

    delete fragmentShader;
    fragmentShader = NULL;

    delete vertexShader;
    vertexShader = NULL;

    // Set up texture

    // number 1
    ImageAsset *img = new ImageAsset("assets/textures/texturesLesson/container.jpg", false);
    Texture2D *tex1 = new Texture2D(img);
    delete img;

    // number 2
    img = new ImageAsset("assets/textures/texturesLesson/awesomeface.png", true);
    Texture2D *tex2 = new Texture2D(img);
    delete img;
    img = NULL;

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

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        processInput(window);

        // Draw stuff
        glClearColor(0.53f, 0.88f, 0.98f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram->use();
        tex1->useActiveTexture(GL_TEXTURE0);
        tex2->useActiveTexture(GL_TEXTURE1);
        glBindVertexArray(VAO);

        serpinski(0.0f,1.0f,-1.0f,-1.0f,1.0f,-1.0f,5,0.65f);

        // display.flip
        glfwSwapBuffers(window);
    }

    delete shaderProgram;
    shaderProgram = NULL;

    delete tex1;
    tex1 = NULL;

    delete tex2;
    tex2 = NULL;

    glfwTerminate();

    return 0;
}

bool init(const char *windowTitle, const int windowWidth, const int windowHeight, GLFWwindow *&window) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Set up GL Window

    window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);

    // Set up glad loader to load in gl procs
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    return true;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(width/2, height/2, width/2, height/2); // simply resize the window accordingly
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window,true);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}
