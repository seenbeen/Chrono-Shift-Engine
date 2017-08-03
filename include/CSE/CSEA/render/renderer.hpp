#ifndef CSEA_RENDER_RENDERER_HPP
#define CSEA_RENDER_RENDERER_HPP
#include <set>

#include <CSE/CSELL/core/window.hpp>
#include <CSE/CSELL/render/rendererimple.hpp>
#include <CSE/CSELL/render/renderer.hpp>

#include <CSE/CSEA/render/scene.hpp>
#include <CSE/CSEA/render/overlay.hpp>
#include <CSE/CSEA/render/viewport.hpp>
#include <CSE/CSEA/render/renderable.hpp>
#include <CSE/CSEA/render/overlayrenderable.hpp>

#include <CSE/CSEA/render/cachemanager.hpp>

namespace CSEA { namespace Core {
    class Engine; // forward decls
}}

namespace CSEA { namespace Render {
    class Renderer {
    friend class CSEA::Core::Engine;
    public:
        struct WindowSettings {
            // some settings.. might get added to
            std::string windowTitle;
            unsigned int width, height;
            bool isResizeable;
            bool fullScreen; // not supported right now. won't do a thing if you include it
        };

    private:
        static bool isInitialized;

        static CSELL::Core::Window *window;
        static CSELL::Render::RendererImple *rimple;
        static CSELL::Render::Renderer *renderer;
        static CacheManager *cacheManager;

        static std::set<Scene*> scenes;
        static std::set<Overlay*> overlays;
        static std::set<Viewport*> viewports;

        Renderer();
        ~Renderer();

        // only engine should be able to do this
        static bool initialize(WindowSettings &settings);
        static void shutdown();

        static void update(double deltaTime); // called every frame, updates all scenes it holds

        // misc for registering with the input manager
        static bool registerInputCallbackHandler(CSELL::Core::InputCallbackHandler *handler);

    public:
        static bool addViewport(Viewport *viewport);
        static bool addScene(Scene *scene);
        static bool addOverlay(Overlay *overlay);

        static bool removeViewport(Viewport *viewport);
        static bool removeScene(Scene *scene);
        static bool removeOverlay(Overlay *overlay);

        static bool loadRenderable(Renderable *renderable);
        static bool unloadRenderable(Renderable *renderable);

        static bool loadOverlayRenderable(OverlayRenderable *overRend);
        static bool unloadOverlayRenderable(OverlayRenderable *overRend);
    };
}}
#endif
