#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/render/mesh.hpp>

namespace CSELL { namespace Render {
    Mesh *Mesh::activeMesh = NULL;

    Mesh::Mesh() {
        #if RENDERER_WARNING_CHECKS == true
        this->renderer = NULL;
        this->activeRenderer = NULL;
        #endif
    }

    Mesh::~Mesh() {}

    bool Mesh::useMesh() {
        #if RENDERER_WARNING_CHECKS == true
        if (Mesh::activeMesh == this) {
            //CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - Mesh",
            //                 "Current Mesh is already active.");
            return false;
        }
        #endif
        Mesh::activeMesh = this;
        return this->useMeshImplementation();
    }

    bool Mesh::renderMesh() {
        #if RENDERER_WARNING_CHECKS == true
        if (Mesh::activeMesh != this) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - Mesh",
                             "Unable to render non-active Mesh.");
            return false;
        }
        #endif
        return this->renderMeshImplementation();
    }

    bool Mesh::renderMesh(unsigned int startElement, unsigned int endElement) {
        #if RENDERER_WARNING_CHECKS == true
        if (Mesh::activeMesh != this) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - Mesh",
                             "Unable to render non-active Mesh.");
            return false;
        }
        #endif
        return this->renderMeshImplementation(startElement, endElement);
    }
}}
