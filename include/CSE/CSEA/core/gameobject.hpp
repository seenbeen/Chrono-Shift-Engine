#ifndef CSEA_CORE_GAMEOBJECT_HPP
#define CSEA_CORE_GAMEOBJECT_HPP

namespace CSEA { namespace Core {
    class Stage;

    class GameObject {
    friend class Stage;
        // this happens whenever the object enters the stage, or the stage is transitioned into
        virtual void onEnter() = 0;

        // this happens wheenver the object leaves the stage, or the stage is transitioned out of
        virtual void onExit() = 0;

        virtual void onUpdate(double deltaTime) = 0;
    };
}}
#endif
