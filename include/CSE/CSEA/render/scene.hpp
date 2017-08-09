#ifndef CSEA_RENDER_SCENE_HPP
#define CSEA_RENDER_SCENE_HPP
#include <set>

#include <CSE/CSEA/render/renderable.hpp>
#include <CSE/CSEA/render/scenemanager.hpp>

namespace CSEA { namespace Render {
    class Renderer;
    class Viewport;
    class Camera;

    class Scene {
    friend class Renderer;
    friend class Viewport;
        // active meaning does this scene update. Saves you some frame ops if you need it - still renders just fine
        bool isLoaded, managerIsMine;

        SceneManager *manager;
        std::set<Renderable*> renderables;

        void update(double deltaTime);
        void render(Camera *c); // scene objects require a camera in order to render properly

        // used to load/unload all bound renderables, and also to decide whether loading on add is necessary
        void onLoad();
        void onUnload();

    public:
        Scene(SceneManager *manager);
        Scene();
        ~Scene();

        bool addRenderable(Renderable *renderable);
        bool removeRenderable(Renderable *renderable);
        void setIsActive(bool isActive);
        bool getIsActive();
    };
}}
#endif
