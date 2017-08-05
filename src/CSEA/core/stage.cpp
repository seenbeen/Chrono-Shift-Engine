#include <CSE/CSEA/core/stage.hpp>

#include <queue>
#include <set>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSEA/core/gameobject.hpp>

namespace CSEA { namespace Core {
    void Stage::update(double deltaTime) {
        std::set<GameObject*>::iterator it;
        for (it = this->gameObjects.begin(); it != this->gameObjects.end(); ++it) {
            (*it)->onUpdate(deltaTime);
        }
        this->resolveTasks();
    }

    void Stage::resolveTasks() {
        while (this->tasks.size()) {
            this->resolveTask(this->tasks.front());
            delete this->tasks.front();
            this->tasks.pop();
        }
    }

    void Stage::resolveTask(Stage::StageTask *task) {
        std::set<GameObject*>::iterator it;
        if (task->type == Stage::ADD_OBJECT) {
            this->addObject(task->target);
        } else if (task->type == Stage::REMOVE_OBJECT) {
            this->removeObject(task->target);
        }
    }

    void Stage::load() {
        this->onLoad();
    }

    void Stage::unload() {
        this->onUnload();
    }

    void Stage::transitionInto() {
        this->onTransitionInto();
    }

    void Stage::transitionOutOf() {
        this->onTransitionOutOf();
    }

    void Stage::addObject(GameObject *obj) {
        std::set<GameObject*>::iterator it = this->gameObjects.find(obj);
        if (it != this->gameObjects.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Core - Stage",
                             "Trying to add already-existent GameObject into Stage!");
            return;
        }
        this->gameObjects.insert(obj);
        obj->onEnter();
    }

    void Stage::removeObject(GameObject *obj) {
        std::set<GameObject*>::iterator it = this->gameObjects.find(obj);
        if (it == this->gameObjects.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Core - Stage",
                             "Trying to remove non-existent GameObject from Stage!");
            return;
        }
        obj->onExit();
        this->gameObjects.erase(it);
    }

    void Stage::addTask(TaskType type, GameObject *target) {
        Stage::StageTask *e = new Stage::StageTask();
        e->type = type;
        e->target = target;
        this->tasks.push(e);
    }

    Stage::Stage() {};
    Stage::~Stage() {};
}}
