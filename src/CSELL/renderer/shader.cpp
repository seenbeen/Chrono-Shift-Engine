#include <lib/glad/glad.h>

#include <CSE/CSELL/renderer/shader.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

namespace CSELL { namespace Renderer {
    Shader::Shader(const char *path, const GLenum shaderType) {
        const char *charShaderType;
        if (shaderType == GL_VERTEX_SHADER) {
            charShaderType = "vertex";
        } else if (shaderType == GL_FRAGMENT_SHADER) {
            charShaderType = "fragment";
        } else {
            std::cout << "Error compiling Shader! Please specify a valid shader Type!" << std::endl;
        }

        this->shaderId = glCreateShader(shaderType);

        std::ostringstream oss;
        std::ifstream shaderFile;


        shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            shaderFile.open(path);
            oss << shaderFile.rdbuf();
            shaderFile.close();
        } catch (std::ifstream::failure e) {
            std::cout << "Failed to read shader file " << path << "." << std::endl;
        }

        const char *shaderContents = oss.str().c_str();

        glShaderSource(this->shaderId, 1, &shaderContents, NULL);
        glCompileShader(this->shaderId);

        // check for success

        int compileSuccess;
        char statusMsg[512];
        glGetShaderiv(this->shaderId, GL_COMPILE_STATUS, &compileSuccess);
        if (compileSuccess) {
            this->successCompiled = true;
        } else {
            glGetShaderInfoLog(this->shaderId, 512, NULL, statusMsg);
            std::cout << "Something went wrong with compiling " << charShaderType << " shader:" << std::endl << statusMsg << std::endl;
            this->successCompiled = false;
        }
    }

    unsigned int Shader::getId() {
        return this->shaderId;
    }

    bool Shader::compileSuccess() {
        return this->successCompiled;
    }

    Shader::~Shader() {
        glDeleteShader(this->shaderId);
    }
}}
