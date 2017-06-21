#include <CSE/CSU/logger.hpp>

#include <cstddef>

#include <CSE/CSELL/render/shaderprogram.hpp>
#include <CSE/CSELL/render/shader.hpp>

namespace CSELL { namespace Render {
    static bool ensureContext(bool isActiveRenderer) {
        if (!isActiveRenderer) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - ShaderProgram",
                             "ShaderProgram does not belong to active Renderer!");
            return false;
        }
        return true;
    }

    ShaderProgram::ShaderProgram() {}
    ShaderProgram::~ShaderProgram() {}

    bool ShaderProgram::attachShader(Shader *shader) {
        if (ensureContext(this->renderer == *this->activeRenderer)) {
            return this->attachShaderImplementation(shader);
        }
        return false;
    }

    bool ShaderProgram::linkShaderProgram() {
        if (ensureContext(this->renderer == *this->activeRenderer)) {
            return this->linkShaderProgramImplementation();
        }
        return false;
    }

    bool ShaderProgram::useShaderProgram() {
        if (ensureContext(this->renderer == *this->activeRenderer)) {
            return this->useShaderProgramImplementation();
        }
        return false;
    }

    bool ShaderProgram::setInt(const char *key, int value) {
        if (ensureContext(this->renderer == *this->activeRenderer)) {
            return this->setIntImplementation(key, value);
        }
        return false;
    }

    bool ShaderProgram::setFloat(const char *key, float value) {
        if (ensureContext(this->renderer == *this->activeRenderer)) {
            return this->setFloatImplementation(key, value);
        }
        return false;
    }

    bool ShaderProgram::setMat4f(const char *key, float *value) {
        if (ensureContext(this->renderer == *this->activeRenderer)) {
            return this->setMat4fImplementation(key, value);
        }
        return false;
    }
}}
