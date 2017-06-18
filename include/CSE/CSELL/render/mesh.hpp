#ifndef CSELL_RENDER_MESH_HPP
#define CSELL_RENDER_MESH_HPP

#include <lib/glm/glm.hpp>

namespace CSELL { namespace Render {
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
