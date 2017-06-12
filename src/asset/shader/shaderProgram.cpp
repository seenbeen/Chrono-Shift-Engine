#include <glad/glad.h>

#include <asset/shader/shaderProgram.h>
#include <asset/shader/shader.h>

#include <vector>
#include <iostream>

ShaderProgram::ShaderProgram() {
    this->programId = glCreateProgram();
    this->finalized = false;
}

bool ShaderProgram::attachShader(Shader *shader) {
    if (!this->finalized) {
        this->shaders.push_back(shader);
        glAttachShader(this->programId,shader->getId());
        return true;
    } else {
        std::cout << "WARNING: Trying to attach shader to a linked program!" << std::endl;
        return false;
    }
}

bool ShaderProgram::linkProgram() {
    if (!this->finalized) {
        glLinkProgram(this->programId);

        while(this->shaders.size()) {
            glDetachShader(this->programId,this->shaders.back()->getId());
            this->shaders.pop_back();
        }

        // check for errors
        int linkSuccess;
        char statusMsg[512];
        glGetProgramiv(this->programId, GL_LINK_STATUS, &linkSuccess);

        if (!linkSuccess) {
            glGetProgramInfoLog(this->programId, 512, NULL, statusMsg);
            std::cout << "Error linking Shader Program!" << std::endl << statusMsg << std::endl;
            return false;
        }

        this->finalized = true;
        return true;
    } else {
        std::cout << "WARNING: Trying to re-link a linked program!" << std::endl;
        return false;
    }
}

void ShaderProgram::use() {
    glUseProgram(this->programId);
}

void ShaderProgram::setInt(const char *key, int value) {
    glUseProgram(this->programId);
    glUniform1i(glGetUniformLocation(this->programId, key), value);
    glUseProgram(0);
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(this->programId);
}
