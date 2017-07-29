#ifndef CSEA_RENDER_OVERLAYRENDERABLE_HPP
#define CSEA_RENDER_OVERLAYRENDERABLE_HPP

#include <CSE/CSELL/render/renderer.hpp>

namespace CSEA { namespace Render {
    class Overlay;
    class Window;

    class OverlayRenderable {
    friend class Overlay;
    friend class Window;
        Overlay *boundOverlay;
        bool isLoaded;

        bool load(CSELL::Render::Renderer *renderer);
        bool unload(CSELL::Render::Renderer *renderer);
        void update(double deltaTime);
        void render(unsigned int viewportWidth, unsigned int viewportHeight);

        protected:
            virtual bool onLoad(CSELL::Render::Renderer *renderer) = 0;
            virtual bool onUnload(CSELL::Render::Renderer *renderer) = 0;
            virtual void onUpdate(double deltaTime) = 0;
            virtual void onRender(unsigned int viewportWidth, unsigned int viewportHeight) = 0;

        public:
            OverlayRenderable();
            virtual ~OverlayRenderable();
    };
}}
#endif
