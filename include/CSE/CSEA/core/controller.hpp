#ifndef CSEA_CORE_CONTROLLER_HPP
#define CSEA_CORE_CONTROLLER_HPP

#include <CSE/CSU/logger.hpp>

namespace CSEA { namespace Core {
    class ControllerBase {
    public:
        ControllerBase();
        virtual ~ControllerBase();

        virtual void onEnter() = 0;
        virtual void onExit() = 0;
        virtual void onUpdate(double deltaTime) = 0;
    };

    template <class T>
    class Controller : ControllerBase {
    protected:
        T *gameObject;
    public:
        Controller() {
            this->gameObject = NULL;
        }

        ~Controller() {
            if (this->gameObject != NULL) {
                CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Core - Controller",
                                 "Controller still bound to object on deletion.");
            }
        }

        void bindTo(T *obj) {
            if (this->gameObject != NULL) {
                CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Core - Controller",
                                 "Attempting to bind an already bound Controller.");
                return;
            } else if (obj == NULL) {
                CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Core - Controller",
                                 "Attempting to bind controller to NULL object.");
                return;
            }
            this->gameObject = obj;
            this->gameObject->addController(this);
        }

        void unbindFrom() {
            if (this->gameObject == NULL) {
                CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Core - Controller",
                                 "Attempting to unbind an unbound Controller.");
                return;
            }
            this->gameObject->removeController(this);
            this->gameObject = NULL;
        }

        virtual void onEnter() = 0;
        virtual void onExit() = 0;
        virtual void onUpdate(double deltaTime) = 0;
    };
}}
#endif // CSEA_CORE_CONTROLLER_HPP
