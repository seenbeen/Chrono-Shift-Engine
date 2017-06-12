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

int main() {

    GLFWwindow *window = NULL;

    if (!init(WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT, window)) {
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // register our callback


    glViewport(0, 0, 800, 600); // Plswerk ;~;

    // Set up shaders :3

    Shader *fragmentShader = new Shader("assets/shaders/fragmentShader1.fs",GL_FRAGMENT_SHADER);
    Shader *vertexShader = new Shader("assets/shaders/vertexShader1.vs",GL_VERTEX_SHADER);

    ShaderProgram *shaderProgram = new ShaderProgram();

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


    // matrix glm stuff
    glm::mat4 trans, temp;
    trans = glm::translate(trans, glm::vec3(0.5f,-0.5f,0.0f));

    // begin program
    shaderProgram->setInt("tex1", 0);
    shaderProgram->setInt("tex2", 1);

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        processInput(window);

        // Draw stuff
        glClearColor(0.53f, 0.88f, 0.98f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        temp = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
        shaderProgram->setMat4fv("transform", glm::value_ptr(temp));

        shaderProgram->use();
        tex1->useActiveTexture(GL_TEXTURE0);
        tex2->useActiveTexture(GL_TEXTURE1);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
    glViewport(0, 0, width, height); // simply resize the window accordingly
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
