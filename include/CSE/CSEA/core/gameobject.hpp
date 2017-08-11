#ifndef CSEA_CORE_GAMEOBJECT_HPP
#define CSEA_CORE_GAMEOBJECT_HPP

#include <list>

#include <CSE/CSEA/core/controller.hpp>

namespace CSEA { namespace Core {
    class Stage;

    class GameObject {
    friend class Stage;
        std::list<ControllerBase*> controllers; // our controllers

        // these hook-ins are called by the managing stage
        void enter();
        void exit();
        void update(double deltaTime);

    protected:
        // this happens whenever the object enters the stage, or the stage is transitioned into
        virtual void onEnter() = 0;

        // this happens wheenver the object leaves the stage, or the stage is transitioned out of
        virtual void onExit() = 0;

        // standard update
        virtual void onUpdate(double deltaTime) = 0;

    public:
        GameObject();
        virtual ~GameObject();

        void addController(ControllerBase *controller);
        void removeController(ControllerBase *controller);
    };
}}
#endif
