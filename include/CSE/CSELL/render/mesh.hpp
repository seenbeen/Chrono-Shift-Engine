#ifndef CSELL_RENDER_MESH_HPP
#define CSELL_RENDER_MESH_HPP

namespace CSELL { namespace Render {
    class Renderer;

    class Mesh {
    friend class Renderer;
    public:
        struct Vertex {
            float pos[3];
            float normal[3];
            float texCoord[2];
        };
    private:
        static Mesh *activeMesh;
        #if RENDERER_WARNING_CHECKS == true
        Renderer *renderer;
        Renderer **activeRenderer;
        #endif

    protected:
        Mesh();
        virtual ~Mesh();
        virtual bool initMesh(unsigned int nVertices, const Mesh::Vertex *vertices,
                              unsigned int nElements, const unsigned int *elements) = 0;
        virtual bool useMeshImplementation() = 0;
        virtual bool renderMeshImplementation() = 0;
        virtual bool renderMeshImplementation(unsigned int startElement, unsigned int endElement) = 0;
    public:
        bool useMesh();
        bool renderMesh();
        bool renderMesh(unsigned int startElement, unsigned int endElement);
    };
}}

#endif
