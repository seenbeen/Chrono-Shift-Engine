#include <string>

#include <glad/glad.h>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/render/shaderProgram.hpp>


namespace CSELL { namespace Render {
    unsigned int ShaderProgram::activeProgram = 0;

    ShaderProgram::ShaderProgram(const std::string &programName, unsigned int nShaders, const Shader **shaders) {
        this->programName = programName;
        this->programId = glCreateProgram();

        for (unsigned int i = 0; i < nShaders; i++) {
            glAttachShader(this->programId, shaders[i]->shaderId);
        }

        glLinkProgram(this->programId);
        // check for errors
        int linkSuccess;
        char statusMsg[512];
        glGetProgramiv(this->programId, GL_LINK_STATUS, &linkSuccess);

        if (linkSuccess) {
            for (unsigned int i = 0; i < nShaders; i++) {
                glDetachShader(this->programId, shaders[i]->shaderId);
            }

            this->successfulLink = true;
        } else {
            glGetProgramInfoLog(this->programId, 512, NULL, statusMsg);
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - ShaderProgram",
                             std::string("Error linking Shader Program \"" + this->programName + "\":\n") + statusMsg);

            this->successfulLink = false;
        }
    }

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(this->programId);
    }

    std::string ShaderProgram::getName() {
        return this->programName;
    }

    void ShaderProgram::use() {
        if (ShaderProgram::activeProgram == this->programId) {
            return;
        }
        glUseProgram(this->programId);
        ShaderProgram::activeProgram = this->programId;
    }

    void ShaderProgram::setInt(const char *key, int value) {
        if (ShaderProgram::activeProgram != this->programId) {
            this->use();
        }
        glUniform1i(glGetUniformLocation(this->programId, key), value);
    }

    void ShaderProgram::setFloat(const char *key, float value) {
        if (ShaderProgram::activeProgram != this->programId) {
            this->use();
        }
        glUniform1f(glGetUniformLocation(this->programId, key), value);
    }

    void ShaderProgram::setMat4fv(const char *key, float *value) {
        if (ShaderProgram::activeProgram != this->programId) {
            this->use();
        }
        glUniformMatrix4fv(glGetUniformLocation(this->programId, key), 1, GL_FALSE, value);
    }
}}
