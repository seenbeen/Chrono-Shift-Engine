#include <CSE/CSU/logger.hpp>

#include <cstddef>

#include <CSE/CSELL/render/shaderprogram.hpp>
#include <CSE/CSELL/render/shader.hpp>

namespace CSELL { namespace Render {
    #if RENDERER_WARNING_CHECKS == true
    ShaderProgram *ShaderProgram::activeShaderProgram = NULL;
    #endif

    ShaderProgram::ShaderProgram() {
        #if RENDERER_WARNING_CHECKS == true
        this->isLinked = false;
        #endif
    }

    ShaderProgram::~ShaderProgram() {
        #if RENDERER_WARNING_CHECKS == true
        if (ShaderProgram::activeShaderProgram == this) {
            ShaderProgram::activeShaderProgram = NULL;
        }
        #endif
    }

    bool ShaderProgram::attachShader(Shader *shader) {
        #if RENDERER_WARNING_CHECKS == true
        if (this->renderer != *this->activeRenderer) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - ShaderProgram",
                             "ShaderProgram does not belong to active Renderer!");
            return false;
        }
        if (this->isLinked) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - ShaderProgram",
                             "Cannot attach Shader to a linked ShaderProgram!");
            return false;
        }
        #endif
        return this->attachShaderImplementation(shader);
    }

    bool ShaderProgram::linkShaderProgram() {
        #if RENDERER_WARNING_CHECKS == true
        if (this->renderer != *this->activeRenderer) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - ShaderProgram",
                             "ShaderProgram does not belong to active Renderer!");
            return false;
        }
        if (this->isLinked) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - ShaderProgram",
                             "ShaderProgram has already been linked!");
            return false;
        }

        this->isLinked = this->linkShaderProgramImplementation();
        return this->isLinked;
        #else
        return this->linkShaderProgramImplementation();
        #endif
    }

    bool ShaderProgram::useShaderProgram() {
        #if RENDERER_WARNING_CHECKS == true
        if (this->renderer != *this->activeRenderer) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - ShaderProgram",
                             "ShaderProgram does not belong to active Renderer!");
            return false;
        }
        if (!this->isLinked) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - ShaderProgram",
                             "Unable to use an un-linked ShaderProgram!");
            return false;
        }
        if (ShaderProgram::activeShaderProgram == this) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - ShaderProgram",
                             "ShaderProgram is already active!");
            return false;
        }
        if (this->useShaderProgramImplementation()) {
            ShaderProgram::activeShaderProgram = this;
            return true;
        }
        return false;
        #else
        return this->useShaderProgramImplementation();
        #endif
    }

    bool ShaderProgram::setInt(const char *key, int value) {
        #if RENDERER_WARNING_CHECKS == true
        if (this->renderer != *this->activeRenderer) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - ShaderProgram",
                             "ShaderProgram does not belong to active Renderer!");
            return false;
        }
        if (!this->isLinked) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - ShaderProgram",
                             "Unable to set uniform on an un-linked ShaderProgram!");
            return false;
        }
        if (ShaderProgram::activeShaderProgram != this) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - ShaderProgram",
                             "Unable to set uniform of non-active ShaderProgram!");
            return false;
        }
        #endif
        return this->setIntImplementation(key, value);
    }

    bool ShaderProgram::setFloat(const char *key, float value) {
        #if RENDERER_WARNING_CHECKS == true
        if (this->renderer != *this->activeRenderer) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - ShaderProgram",
                             "ShaderProgram does not belong to active Renderer!");
            return false;
        }
        if (!this->isLinked) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - ShaderProgram",
                             "Unable to set uniform on an un-linked ShaderProgram!");
            return false;
        }
        if (ShaderProgram::activeShaderProgram != this) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - ShaderProgram",
                             "Unable to set uniform of non-active ShaderProgram!");
            return false;
        }
        #endif
        return this->setFloatImplementation(key, value);
    }

    bool ShaderProgram::setMat4f(const char *key, float *value) {
        #if RENDERER_WARNING_CHECKS == true
        if (this->renderer != *this->activeRenderer) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - ShaderProgram",
                             "ShaderProgram does not belong to active Renderer!");
            return false;
        }
        if (!this->isLinked) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - ShaderProgram",
                             "Unable to set uniform on an un-linked ShaderProgram!");
            return false;
        }
        if (ShaderProgram::activeShaderProgram != this) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - ShaderProgram",
                             "Unable to set uniform of non-active ShaderProgram!");
            return false;
        }
        #endif
        return this->setMat4fImplementation(key, value);
    }
}}
