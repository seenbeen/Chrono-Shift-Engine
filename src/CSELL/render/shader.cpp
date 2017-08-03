#include <string>

#include <CSE/CSELL/render/shader.hpp>

namespace CSELL { namespace Render {
    Shader::Shader() {
        #if RENDERER_WARNING_CHECKS == true
        this->renderer = NULL;
        this->activeRenderer = NULL;
        #endif
    }
    Shader::~Shader() {}
}}
