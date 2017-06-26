#include <lib/glad/glad.h>

#include <CSE/CSELL/render/gl/glmesh.hpp>

#include <iostream>

namespace CSELL { namespace Render {
    GLMesh::~GLMesh() {
        // empty for now
    }

    bool GLMesh::initMesh(unsigned int nVertices, const Mesh::Vertex *vertices,
                          unsigned int nElements, const unsigned int *elements) {

        this->nVertices = nVertices;
        this->nElements = nElements;

        glGenBuffers(1, &this->EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, nElements*sizeof(unsigned int), elements, GL_STATIC_DRAW);

        glGenBuffers(1, &this->VBO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, nVertices*sizeof(Mesh::Vertex), vertices, GL_STATIC_DRAW);

        // set up vertex array obj
        glGenVertexArrays(1, &this->VAO);
        glBindVertexArray(this->VAO);

        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);

        // pos
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void*)0);

        // normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex),
                              (void*)(offsetof(Mesh::Vertex, normal)));

        // textures
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex),
                              (void*)(offsetof(Mesh::Vertex, texCoord)));

        glBindVertexArray(0);
        return true;
    }

    bool GLMesh::useMeshImplementation() {
        glBindVertexArray(this->VAO);
        return true;
    }

    bool GLMesh::renderMeshImplementation() {
        glDrawElements(GL_TRIANGLES, this->nElements, GL_UNSIGNED_INT, 0);
        return true;
    }
}}
