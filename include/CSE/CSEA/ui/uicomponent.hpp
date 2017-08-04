#ifndef CSEA_UI_UICOMPONENT_HPP
#define CSEA_UI_UICOMPONENT_HPP
namespace CSEA { namespace UI {
    class UIComponent {
    protected:
        virtual bool init() = 0;
        virtual bool update(float deltaTime) = 0;
    public:
        explicit UIComponent(CSELL::Render::Renderer renderer);
        virtual ~UIComponent() = 0;
    }
}}
#endif
