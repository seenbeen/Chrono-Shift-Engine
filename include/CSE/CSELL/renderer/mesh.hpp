#ifndef CSELL_RENDERER_MESH_HPP
#define CSELL_RENDERER_MESH_HPP

#include <lib/glm/glm.hpp>

namespace CSELL { namespace Renderer {
    class Mesh {
    public:
        struct Vertex {
            glm::vec3 pos;
            glm::vec3 normal;
            glm::vec2 texCoord;
        };
    };
}}

#endif
