#include <CSE/CSEA/core/stage.hpp>

#include <queue>
#include <set>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSEA/core/gameobject.hpp>

namespace CSEA { namespace Core {
    void Stage::update(double deltaTime) {
        std::set<GameObject*>::iterator it;
        for (it = this->gameObjects.begin(); it != this->gameObjects.end(); it++) {
            (*it)->onUpdate(deltaTime);
        }
        while (this->tasks.size()) {
            this->resolveTask(this->tasks.front());
            delete this->tasks.front();
            this->tasks.pop();
        }
    }

    void Stage::resolveTask(Stage::StageTask *task) {
        std::set<GameObject*>::iterator it;
        if (task->type == Stage::StageTask::ADD_OBJECT) {
            it = this->gameObjects.find(task->target);
            if (it != this->gameObjects.end()) {
                CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Core - Stage",
                                 "Trying to add already-existent GameObject into Stage!");
                return;
            }
            this->gameObjects.insert(task->target);
            task->target->onEnter();
        } else if (task->type == Stage::StageTask::REMOVE_OBJECT) {
            it = this->gameObjects.find(task->target);
            if (it == this->gameObjects.end()) {
                CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Core - Stage",
                                 "Trying to delete non-existent GameObject from Stage!");
                return;
            }
            task->target->onExit();
            this->gameObjects.erase(it);
        }
    }

    void Stage::addObject(GameObject *obj) {
        Stage::StageTask *e = new Stage::StageTask();
        e->type = Stage::StageTask::ADD_OBJECT;
        e->target = obj;
        this->tasks.push(e);
    }

    void Stage::removeObject(GameObject *obj) {
        Stage::StageTask *e = new Stage::StageTask();
        e->type = Stage::StageTask::REMOVE_OBJECT;
        e->target = obj;
        this->tasks.push(e);
    }

    Stage::Stage() {};
    Stage::~Stage() {};
}}
