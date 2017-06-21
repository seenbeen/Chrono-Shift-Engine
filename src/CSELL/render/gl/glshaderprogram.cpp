#include <string>

#include <glad/glad.h>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/render/gl/glshaderprogram.hpp>
#include <CSE/CSELL/render/shader.hpp>

namespace CSELL { namespace Render {
    GLShaderProgram *GLShaderProgram::activeShaderProgram = NULL;

    static bool ensureContext(bool isLinked, bool isActiveShader) {
        if (!isLinked) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - GLShaderProgram",
                             "Unable to use an un-linked ShaderProgram!");
            return false;
        }
        if (!isActiveShader) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - GLShaderProgram",
                             "ShaderProgram is not the active ShaderProgram!");
            return false;
        }
        return true;
    }

    GLShaderProgram::~GLShaderProgram() {
        glDeleteProgram(this->programId);
        if (GLShaderProgram::activeShaderProgram == this) {
            GLShaderProgram::activeShaderProgram = NULL;
        }
    }

    bool GLShaderProgram::initShaderProgram() {
        this->programId = glCreateProgram();
        this->isLinked = false;
        return true;
    }

    bool GLShaderProgram::attachShaderImplementation(Shader *shader) {
        if (this->isLinked) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - GLShaderProgram",
                             "Cannot attach Shader to a linked ShaderProgram!");
            return false;
        }
        this->shaders.push_back(shader);
        glAttachShader(this->programId, shader->getShaderId());
        return true;
    }

    bool GLShaderProgram::linkShaderProgramImplementation() {
        if (this->isLinked) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - GLShaderProgram",
                             "ShaderProgram has already been linked!");
            return false;
        }
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
            this->isLinked = true;
            return true;
        } else {
            glGetProgramInfoLog(this->programId, 512, NULL, statusMsg);
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - GLShaderProgram",
                             std::string("Error linking GLShaderProgram:\n") + statusMsg);

            return false;
        }
    }

    bool GLShaderProgram::useShaderProgramImplementation() {
        if (!this->isLinked) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - GLShaderProgram",
                             "Unable to use an un-linked ShaderProgram!");
            return false;
        }
        if (GLShaderProgram::activeShaderProgram == this) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - GLShaderProgram",
                             "ShaderProgram is already active!");
        }
        glUseProgram(this->programId);
        GLShaderProgram::activeShaderProgram = this;
        return true;
    }

    // uniform setter implementations
    bool GLShaderProgram::setIntImplementation(const char *key, int value) {
        if (!ensureContext(this->isLinked, GLShaderProgram::activeShaderProgram == this)) {
            return false;
        }
        glUniform1i(glGetUniformLocation(this->programId, key), value);
        return true;
    }

    bool GLShaderProgram::setFloatImplementation(const char *key, float value) {
        if (!ensureContext(this->isLinked, GLShaderProgram::activeShaderProgram == this)) {
            return false;
        }
        glUniform1f(glGetUniformLocation(this->programId, key), value);
        return true;
    }

    bool GLShaderProgram::setMat4fImplementation(const char *key, float *value) {
        if (!ensureContext(this->isLinked, GLShaderProgram::activeShaderProgram == this)) {
            return false;
        }
        glUniformMatrix4fv(glGetUniformLocation(this->programId, key), 1, GL_FALSE, value);
        return true;
    }
}}
