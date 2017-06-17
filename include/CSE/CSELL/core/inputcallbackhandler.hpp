#ifndef CSELL_CORE_INPUTCALLBACKHANDLER_HPP
#define CSELL_CORE_INPUTCALLBACKHANDLER_HPP

namespace CSELL { namespace Core {
    class InputCallbackHandler {
        friend class Window;
        protected:
            virtual void handleKeyInput(int key, int action, int mods) = 0;
            virtual void handleMousePosInput(double xpos, double ypos) = 0;
            virtual void handleMouseButtonInput(int button, int action, int mods) = 0;
            virtual void handleMouseScrollInput(double xoffset, double yoffset) = 0;
            virtual void handleMouseEnterLeaveInput(int entered) = 0;
    };
}}

#endif
