#ifndef CSEA_RENDER_WINDOW_HPP
#define CSEA_RENDER_WINDOW_HPP

#include <string>
#include <set>

#include <CSE/CSELL/core/window.hpp>

#include <CSE/CSELL/render/rendererimple.hpp>

#include <CSE/CSEA/render/scene.hpp>
#include <CSE/CSEA/render/viewport.hpp>
#include <CSE/CSEA/render/overlay.hpp>
#include <CSE/CSEA/render/renderable.hpp>
#include <CSE/CSEA/render/overlayrenderable.hpp>

namespace CSEA { namespace Render {
    class Renderer;

    class Window {
    friend class Renderer;
    public:
        struct Settings {
            // some settings.. might get added to
            std::string windowTitle;
            unsigned int width, height;
            bool isResizeable;
            bool fullScreen; // not supported right now. won't do a thing if you include it
        };
    private:
        std::set<Scene*> scenes;
        std::set<Overlay*> overlays;
        std::set<Viewport*> viewports;

        bool successfulInit;

        CSELL::Render::Renderer *renderer;

        // engine decides the renderer implementation
        Window(CSELL::Core::Window *window, CSELL::Render::RendererImple *rImple, Window::Settings &settings);
        ~Window(); // blows shit up

        void update(double deltaTime); // called by the renderer every frame, updates all scenes it holds
    public:
        // how we look into the world
        Viewport *newViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

        // containers
        Scene *newScene();
        Overlay *newOverlay();

        bool loadRenderable(Renderable *renderable);
        bool unloadRenderable(Renderable *renderable);
        bool loadOverlayRenderable(OverlayRenderable *overRend);
        bool unloadOverlayRenderable(OverlayRenderable *overRend);
    };
}}
#endif
