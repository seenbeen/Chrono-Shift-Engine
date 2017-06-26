#include <string>

#include <lib/glad/glad.h>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/render/gl/glshaderprogram.hpp>
#include <CSE/CSELL/render/shader.hpp>

namespace CSELL { namespace Render {
    GLShaderProgram::~GLShaderProgram() {
        glDeleteProgram(this->programId);
    }

    bool GLShaderProgram::initShaderProgram() {
        this->programId = glCreateProgram();
        return true;
    }

    bool GLShaderProgram::attachShaderImplementation(Shader *shader) {
        this->shaders.push_back(shader);
        glAttachShader(this->programId, shader->getShaderId());
        return true;
    }

    bool GLShaderProgram::linkShaderProgramImplementation() {
        glLinkProgram(this->programId);
        // check for errors
        int linkSuccess;
        char statusMsg[512];
        glGetProgramiv(this->programId, GL_LINK_STATUS, &linkSuccess);

        for (unsigned int i = 0; i < this->shaders.size(); i++) {
            glDetachShader(this->programId, this->shaders.back()->getShaderId());
            this->shaders.pop_back();
        }

        if (linkSuccess) {
            return true;
        } else {
            glGetProgramInfoLog(this->programId, 512, NULL, statusMsg);
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - GLShaderProgram",
                             std::string("Error linking GLShaderProgram:\n") + statusMsg);

            return false;
        }
    }

    bool GLShaderProgram::useShaderProgramImplementation() {
        glUseProgram(this->programId);
        return true;
    }

    // uniform setter implementations
    bool GLShaderProgram::setIntImplementation(const char *key, int value) {
        glUniform1i(glGetUniformLocation(this->programId, key), value);
        return true;
    }

    bool GLShaderProgram::setFloatImplementation(const char *key, float value) {
        glUniform1f(glGetUniformLocation(this->programId, key), value);
        return true;
    }

    bool GLShaderProgram::setMat4fImplementation(const char *key, float *value) {
        glUniformMatrix4fv(glGetUniformLocation(this->programId, key), 1, GL_FALSE, value);
        return true;
    }
}}
