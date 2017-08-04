#ifndef CSEA_CORE_STAGE_HPP
#define CSEA_CORE_STAGE_HPP
#include <queue>
#include <set>

#include <CSE/CSEA/core/gameobject.hpp>

namespace CSEA { namespace Core {
    class Stage {
        friend class Engine;

        struct StageTask {
            enum TaskType { ADD_OBJECT, REMOVE_OBJECT };
            TaskType type;
            GameObject *target;
        };

        std::queue<StageTask*> tasks;

        std::set<GameObject*> gameObjects; // objects that we manage

        void update(double deltaTime);
        void resolveTasks();
        void resolveTask(StageTask *task);

        void load(); // NOTE: DO NOT ASSIGN TASKS IN THESE FUNCTIONS
        void unload(); // HERE TOO. THESE ARE MEANT TO BE ONE TIME LOADS INTO RAM AND OUT

        void transitionInto();
        void transitionOutOf();

    protected:
        virtual void onLoad() = 0;      // used to load assets
        virtual void onUnload() = 0;

        virtual void onTransitionInto() = 0;    // the part when the stage is set up
        virtual void onTransitionOutOf() = 0;   // the part when the stage is cleaned up

    public:
        void addObject(GameObject *obj);
        void removeObject(GameObject *obj);

        Stage();
        virtual ~Stage();
    };
}}
#endif
