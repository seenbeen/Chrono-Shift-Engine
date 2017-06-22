#ifndef CSELL_RENDER_MESH_HPP
#define CSELL_RENDER_MESH_HPP

#include <lib/glm/glm.hpp>

namespace CSELL { namespace Render {
    class Renderer;

    class Mesh {
    friend class Renderer;
    public:
        struct Vertex {
            glm::vec3 pos;
            glm::vec3 normal;
            glm::vec2 texCoord;
        };
    private:
        #if RENDERER_WARNING_CHECKS == true
        Renderer *renderer;
        Renderer **activeRenderer;
        #endif

    protected:
        Mesh();
        virtual ~Mesh();
        virtual bool initMesh(unsigned int nVertices, const Mesh::Vertex *vertices,
                              unsigned int nElements, const unsigned int *elements) = 0;
    };
}}

#endif
