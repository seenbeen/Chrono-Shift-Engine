#ifndef CSEA_UI_UI_HPP
#define CSEA_UI_UI_HPP
namespace CSEA { namespace UI {
    class UI: public CSEA::Input::InputCallbackHandler {
    public:
        explicit UI(CSELL::Render::Renderer renderer);
        void update(float deltaTime);
    }
}}
#endif
