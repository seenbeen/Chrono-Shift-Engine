#ifndef CSEA_CORE_STAGE_HPP
#define CSEA_CORE_STAGE_HPP
#include <queue>
#include <set>

#include <CSE/CSEA/core/gameobject.hpp>

namespace CSEA { namespace Core {
    class Stage {
        friend class Engine;
    public:
        enum TaskType { ADD_OBJECT, REMOVE_OBJECT };
    private:
        struct StageTask {
            TaskType type;
            GameObject *target;
        };
        std::queue<StageTask*> tasks;

        std::set<GameObject*> gameObjects; // objects that we manage

        void update(double deltaTime);
        void resolveTasks();
        void resolveTask(StageTask *task);

        void load();
        void unload();

        void transitionInto();
        void transitionOutOf();

    protected:
        virtual void onLoad() = 0;   // NOTE: DO NOT ASSIGN TASKS IN THESE FUNCTIONS
        virtual void onUnload() = 0; // HERE TOO. THESE ARE MEANT TO BE ONE TIME LOADS INTO RAM AND OUT

        virtual void onTransitionInto() = 0;    // the part when the stage is set up
        virtual void onTransitionOutOf() = 0;   // the part when the stage is cleaned up

        void addObject(GameObject *obj);
        void removeObject(GameObject *obj);
    public:
        void addTask(TaskType type, GameObject *target); // queues a task for when the stage is running

        Stage();
        virtual ~Stage();
    };
}}
#endif
