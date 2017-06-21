#include <CSE/CSU/logger.hpp>

#include <cstddef>

#include <CSE/CSELL/render/shaderprogram.hpp>
#include <CSE/CSELL/render/shader.hpp>

namespace CSELL { namespace Render {
    ShaderProgram *ShaderProgram::activeShaderProgram = NULL;

    bool ShaderProgram::ensureContext() {
        if (this->renderer != *this->activeRenderer) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - ShaderProgram",
                             "ShaderProgram does not belong to active Renderer!");
            return false;
        }
        if (ShaderProgram::activeShaderProgram != this) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - ShaderProgram",
                             "ShaderProgram is not currently active ShaderProgram!");
            return false;
        }
        return true;
    }

    ShaderProgram::ShaderProgram() {}
    ShaderProgram::~ShaderProgram() {}

    bool ShaderProgram::attachShader(Shader *shader) {
        if (this->renderer == *this->activeRenderer) {
            return this->attachShaderImplementation(shader);
        }
        CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - ShaderProgram",
                         "ShaderProgram does not belong to active Renderer!");
        return false;
    }

    bool ShaderProgram::linkShaderProgram() {
        if (this->renderer == *this->activeRenderer) {
            return this->linkShaderProgramImplementation();
        }
        CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - ShaderProgram",
                         "ShaderProgram does not belong to active Renderer!");
        return false;
    }

    bool ShaderProgram::useShaderProgram() {
        if (ShaderProgram::activeShaderProgram != this) {
            if (this->useShaderProgramImplementation()) {
                ShaderProgram::activeShaderProgram = this;
                return true;
            }
        }
        CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - ShaderProgram",
                         "ShaderProgram is already active!");
        return false;
    }

    bool ShaderProgram::setInt(const char *key, int value) {
        if (this->ensureContext()) {
            return this->setIntImplementation(key, value);
        }
        return false;
    }

    bool ShaderProgram::setFloat(const char *key, float value) {
        if (this->ensureContext()) {
            return this->setFloatImplementation(key, value);
        }
        return false;
    }

    bool ShaderProgram::setMat4f(const char *key, float *value) {
        if (this->ensureContext()) {
            return this->setMat4fImplementation(key, value);
        }
        return false;
    }
}}
