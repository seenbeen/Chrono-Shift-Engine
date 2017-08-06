#ifndef CSEA_RENDER_RENDERABLE_HPP
#define CSEA_RENDER_RENDERABLE_HPP

#include <CSE/CSELL/render/renderer.hpp>

#include <CSE/CSELL/math/transform.hpp>

#include <CSE/CSEA/render/cachemanager.hpp>

namespace CSEA { namespace Render {
    class Scene;
    class Camera;

    class Renderable {
    friend class Renderer;
    friend class Scene;
        Scene *boundScene;
        bool isLoaded;

        bool load(CSELL::Render::Renderer *renderer, CacheManager *cacheManager);
        bool unload(CSELL::Render::Renderer *renderer, CacheManager *cacheManager);

        void update(double deltaTime);
        void render(Camera *camera);

    protected:
        CSELL::Math::Transform xform;

        virtual bool onLoad(CSELL::Render::Renderer *renderer, CacheManager *cacheManager) = 0;
        virtual bool onUnload(CSELL::Render::Renderer *renderer, CacheManager *cacheManager) = 0;
        virtual void onUpdate(double deltaTime) = 0;
        virtual void onRender(Camera *camera) = 0;

    public:
        Renderable();
        virtual ~Renderable();
    };
}}
#endif
