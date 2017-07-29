#ifndef CSEA_RENDER_RENDERER_HPP
#define CSEA_RENDER_RENDERER_HPP

#include <CSE/CSEA/render/window.hpp>

namespace CSEA { namespace Core {
    class Engine; // forward decls
}}

namespace CSEA { namespace Render {
    class Renderer {
    friend class CSEA::Core::Engine;
        static bool isInitialized;
        static Window* window;
        static CSELL::Render::RendererImple *rimple;

        Renderer();
        ~Renderer();

        // only engine should be able to do this
        static bool initialize();
        static void update();
        static void shutdown();

    public:
        static Window *initWindow(Window::Settings &settings);
        static void deleteWindow();
    };
}}
#endif
