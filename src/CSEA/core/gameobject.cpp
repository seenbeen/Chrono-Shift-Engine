#include <CSE/CSEA/core/gameobject.hpp>

#include <algorithm>
#include <list>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSEA/core/controller.hpp>

namespace CSEA { namespace Core {
    GameObject::GameObject() {}

    GameObject::~GameObject() {
        if (this->controllers.size()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Core - GameObject",
                             "Not all controllers detached on deletion.");
        }
    }

    void GameObject::enter() {
        this->onEnter();
        std::list<ControllerBase*>::iterator it;
        for (it = this->controllers.begin(); it != this->controllers.end(); it++) {
            (*it)->onEnter();
        }
    }

    void GameObject::exit() {
        std::list<ControllerBase*>::iterator it;
        for (it = this->controllers.begin(); it != this->controllers.end(); it++) {
            (*it)->onExit();
        }
        this->onExit();
    }

    void GameObject::update(double deltaTime) {
        std::list<ControllerBase*>::iterator it;
        for (it = this->controllers.begin(); it != this->controllers.end(); it++) {
            (*it)->onUpdate(deltaTime);
        }
        this->onUpdate(deltaTime);
    }

    void GameObject::addController(ControllerBase *controller) {
        std::list<ControllerBase*>::iterator it = std::find(this->controllers.begin(), this->controllers.end(), controller);
        if (it != this->controllers.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Core - GameObject",
                             "Attempting to add already existing Controller.");
            return;
        }
        this->controllers.push_back(controller);
    }

    void GameObject::removeController(ControllerBase *controller) {
        std::list<ControllerBase*>::iterator it = std::find(this->controllers.begin(), this->controllers.end(), controller);
        if (it == this->controllers.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Core - GameObject",
                             "Attempting to remove non-existent Controller.");
            return;
        }
        this->controllers.erase(it);
    }
}}
