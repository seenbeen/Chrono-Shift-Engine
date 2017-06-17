#ifndef CSELL_CORE_INPUTCALLBACKHANDLER_HPP
#define CSELL_CORE_INPUTCALLBACKHANDLER_HPP

namespace CSELL { namespace Core {
    class InputCallbackHandler {
        friend class Window;
        protected:
            virtual void handleKeyInput(int key, int action, int mods);
            virtual void handleMousePosInput(double xpos, double ypos);
            virtual void handleMouseButtonInput(int button, int action, int mods);
            virtual void handleMouseScrollInput(double xoffset, double yoffset);
            virtual void handleMouseEnterLeaveInput(int entered);
    };
}}

#endif
