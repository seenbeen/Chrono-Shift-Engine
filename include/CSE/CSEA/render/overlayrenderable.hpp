#ifndef CSEA_RENDER_OVERLAYRENDERABLE_HPP
#define CSEA_RENDER_OVERLAYRENDERABLE_HPP

#include <CSE/CSELL/render/renderer.hpp>
#include <CSE/CSEA/render/cachemanager.hpp>

namespace CSEA { namespace Render {
    class Overlay;

    class OverlayRenderable {
    friend class Renderer;
    friend class Overlay;
        Overlay *boundOverlay;
        bool isLoaded;

        bool load(CSELL::Render::Renderer *renderer, CacheManager *cacheManager);
        bool unload(CSELL::Render::Renderer *renderer, CacheManager *cacheManager);

        void update(double deltaTime);
        void render(unsigned int viewportWidth, unsigned int viewportHeight);

    protected:
        virtual bool onLoad(CSELL::Render::Renderer *renderer, CacheManager *cacheManager) = 0;
        virtual bool onUnload(CSELL::Render::Renderer *renderer, CacheManager *cacheManager) = 0;
        virtual void onUpdate(double deltaTime) = 0;
        virtual void onRender(unsigned int viewportWidth, unsigned int viewportHeight) = 0;

    public:
        OverlayRenderable();
        virtual ~OverlayRenderable();
    };
}}
#endif
