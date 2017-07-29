#include <set>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSEA/render/scene.hpp>

namespace CSEA { namespace Render {
    class Camera;

    Scene::Scene() {}

    Scene::~Scene() {
        if (this->renderables.size()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Scene",
                             "Not all Renderables have been detached from Scene on deletion!");
        }
        std::set<Renderable*>::iterator it;
        for (it = this->renderables.begin(); it != this->renderables.end(); it++) {
            (*it)->boundScene = NULL;
        }
    }

    void Scene::update(double deltaTime) {
        if (this->isActive) {
            std::set<Renderable*>::iterator it;
            for (it = this->renderables.begin(); it != this->renderables.end(); it++) {
                (*it)->update(deltaTime);
            }
        }
    }

    void Scene::render(Camera *camera) {
        std::set<Renderable*>::iterator it;
        for (it = this->renderables.begin(); it != this->renderables.end(); it++) {
            (*it)->render(camera);
        }
    }

    bool Scene::addRenderable(Renderable *renderable) {
        if (renderable->boundScene != NULL) {
            if (renderable->boundScene == this) {
                CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Scene",
                                 "Trying to add Renderable already bound to this Scene!");
            } else {
                CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Scene",
                                 "Trying to add Renderable already bound to a Scene!");
            }
            return false;
        }
        renderable->boundScene = this;
        this->renderables.insert(renderable);
        return true;
    }

    bool Scene::removeRenderable(Renderable *renderable) {
        if (renderable->boundScene != this) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Scene",
                             "Trying to remove Renderable not bound to Scene!");
            return false;
        }
        renderable->boundScene = NULL;
        this->renderables.erase(this->renderables.find(renderable));
        return true;
    }

    void Scene::setIsActive(bool isActive) {
        this->isActive = isActive;
    }

    bool Scene::getIsActive() {
        return this->isActive;
    }
}}
