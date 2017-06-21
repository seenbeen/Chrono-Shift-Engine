#ifndef CSELL_RENDER_GL_GLMESH_HPP
#define CSELL_RENDER_GL_GLMESH_HPP

#include <CSE/CSELL/render/mesh.hpp>

namespace CSELL { namespace Render {
    class GLMesh: public Mesh {
    protected:
        ~GLMesh();
        bool initMesh(unsigned int nVertices, const Mesh::Vertex *vertices,
                      unsigned int nElements, const unsigned int *elements);
    };
}}

#endif
