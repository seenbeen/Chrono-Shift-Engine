#ifndef CSEA_RENDER_SCENE_HPP
#define CSEA_RENDER_SCENE_HPP
#include <set>

#include <CSE/CSEA/render/renderable.hpp>

namespace CSEA { namespace Render {
    class Window;
    class Viewport;
    class Camera;

    class Scene {
    friend class Window;
    friend class Viewport;
        bool isActive;
        // active meaning does this scene update. Saves you some frame ops if you need it - still renders just fine

        std::set<Renderable*> renderables;

        Scene();

        void update(double deltaTime);
        void render(Camera *c); // scene objects require a camera in order to render properly

    public:
        ~Scene();

        bool addRenderable(Renderable *renderable);
        bool removeRenderable(Renderable *renderable);
        void setIsActive(bool isActive);
        bool getIsActive();
    };
}}
#endif
