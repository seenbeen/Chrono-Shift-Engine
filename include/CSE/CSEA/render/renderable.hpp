#ifndef CSEA_RENDER_RENDERABLE_HPP
#define CSEA_RENDER_RENDERABLE_HPP

#include <CSE/CSELL/render/renderer.hpp>

namespace CSEA { namespace Render {
    class Window;
    class Scene;
    class Camera;

    class Renderable {
    friend class Window;
    friend class Scene;
        Scene *boundScene;
        bool isLoaded;

        bool load(CSELL::Render::Renderer *renderer);
        bool unload(CSELL::Render::Renderer *renderer);

        void update(double deltaTime);
        void render(Camera *camera);

    protected:
        virtual bool onLoad(CSELL::Render::Renderer *renderer) = 0;
        virtual bool onUnload(CSELL::Render::Renderer *renderer) = 0;
        virtual void onUpdate(double deltaTime) = 0;
        virtual void onRender(Camera *camera) = 0;

    public:
        Renderable();
        virtual ~Renderable();
    };
}}
#endif
