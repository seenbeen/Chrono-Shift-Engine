#include <vector>

#include <glad/glad.h>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/renderer/shaderProgram.hpp>
#include <CSE/CSELL/renderer/shader.hpp>


namespace CSELL { namespace Renderer {
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
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Renderer - Shader",
                             "Trying to attach shader to a linked program!");
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
                CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Renderer - ShaderProgram",
                                 std::string("Error linking Shader Program:\n") + statusMsg);
                return false;
            }

            this->finalized = true;
            return true;
        } else {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Renderer - ShaderProgram",
                             "Trying to re-link a linked program!");
            return false;
        }
    }

    void ShaderProgram::use() {
        glUseProgram(this->programId);
    }

    void ShaderProgram::setInt(const char *key, int value) {
        glUseProgram(this->programId);
        glUniform1i(glGetUniformLocation(this->programId, key), value);
    }

    void ShaderProgram::setFloat(const char *key, float value) {
        glUseProgram(this->programId);
        glUniform1f(glGetUniformLocation(this->programId, key), value);
    }

    void ShaderProgram::setMat4fv(const char *key, float *value) {
        glUseProgram(this->programId);
        glUniformMatrix4fv(glGetUniformLocation(this->programId, key), 1, GL_FALSE, value);
    }

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(this->programId);
    }
}}
