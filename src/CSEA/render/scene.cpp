#include <CSE/CSEA/render/scene.hpp>

#include <set>
#include <vector>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSEA/render/renderer.hpp>
#include <CSE/CSEA/render/scenemanager.hpp>
#include <CSE/CSEA/render/scenemanagerdefault.hpp>

namespace CSEA { namespace Render {
    class Camera;

    Scene::Scene() {
        this->isLoaded = false;
        this->manager = new SceneManagerDefault();
        this->managerIsMine = true;
    }

    Scene::Scene(SceneManager *manager) {
        this->isLoaded = false;
        this->manager = manager;
        this->managerIsMine = false;
    }

    Scene::~Scene() {
        if (this->renderables.size()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Scene",
                             "Not all Renderables have been detached from Scene on deletion!");
        }
        std::set<Renderable*>::iterator it;
        for (it = this->renderables.begin(); it != this->renderables.end(); ++it) {
            (*it)->boundScene = NULL;
        }
        if (this->managerIsMine) {
            delete this->manager;
        }
    }

    void Scene::update(double deltaTime) {
        std::set<Renderable*>::iterator it;
        for (it = this->renderables.begin(); it != this->renderables.end(); ++it) {
            (*it)->update(deltaTime);
            if ((*it)->isDirty) {
                // update Manager
                this->manager->updateRenderable(*it);
            }
        }
    }

    void Scene::render(Camera *camera) {
        std::vector<Renderable*> resultingRenderables;
        this->manager->getVisibleRenderables(camera, resultingRenderables);
        std::vector<Renderable*>::iterator it;
        for (it = resultingRenderables.begin(); it != resultingRenderables.end(); ++it) {
            (*it)->render(camera);
        }
    }

    void Scene::onLoad() {
        if (this->isLoaded) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Scene",
                             "Trying to load already loaded scene!");
            return;
        }
        std::set<Renderable*>::iterator it;
        for (it = this->renderables.begin(); it != this->renderables.end(); ++it) {
            CSEA::Render::Renderer::loadRenderable(*it);
        }
        this->isLoaded = true;
    }

    void Scene::onUnload() {
        if (!this->isLoaded) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Scene",
                             "Trying to unload unloaded Scene!");
            return;
        }
        std::set<Renderable*>::iterator it;
        for (it = this->renderables.begin(); it != this->renderables.end(); ++it) {
            CSEA::Render::Renderer::unloadRenderable(*it);
        }
        this->isLoaded = false;
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
        this->manager->addRenderable(renderable);
        if (this->isLoaded) {
            CSEA::Render::Renderer::loadRenderable(renderable);
        }
        return true;
    }

    bool Scene::removeRenderable(Renderable *renderable) {
        if (renderable->boundScene != this) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Scene",
                             "Trying to remove Renderable not bound to Scene!");
            return false;
        }
        renderable->boundScene = NULL;
        if (this->isLoaded) {
            CSEA::Render::Renderer::unloadRenderable(renderable);
        }
        this->manager->removeRenderable(renderable);
        this->renderables.erase(this->renderables.find(renderable));
        return true;
    }
}}
