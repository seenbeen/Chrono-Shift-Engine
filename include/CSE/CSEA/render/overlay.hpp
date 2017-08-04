#ifndef CSEA_RENDER_OVERLAY_HPP
#define CSEA_RENDER_OVERLAY_HPP
#include <set>

#include <CSE/CSEA/render/overlayrenderable.hpp>

namespace CSEA { namespace Render {
    class Renderer;
    class Viewport;

    class Overlay {
    friend class Renderer;
    friend class Viewport;
        std::set<OverlayRenderable*> renderables;
        bool isLoaded;

        void update(double deltaTime);
        void render(unsigned int viewportWidth, unsigned int viewportHeight);

        // used to load/unload all bound renderables, and also to decide whether loading on add is necessary
        void onLoad();
        void onUnload();
    public:
        Overlay();
        ~Overlay();
        bool addOverlayRenderable(OverlayRenderable *overRend);
        bool removeOverlayRenderable(OverlayRenderable *overRend);
    };
}}
#endif
