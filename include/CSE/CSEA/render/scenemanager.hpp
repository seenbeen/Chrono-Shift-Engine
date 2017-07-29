#ifndef CSEA_RENDER_SCENEMANAGER_HPP
#define CSEA_RENDER_SCENEMANAGER_HPP

#include <vector>

#include <CSE/CSEA/render/camera.hpp>

namespace CSEA { namespace Render {
    class Scene;

    class SceneManager {
    friend class Scene;
        // very abstract class, the internal storing implementation is completely up to the child classes
    protected:
        virtual void getVisibleRenderables(Camera *c, std::vector<Renderable*> resultingRenderables) = 0;
        virtual void addRenderable(Renderable *renderable) = 0;
        virtual void removeRenderable(Renderable *renderable) = 0;
        virtual void update() = 0;
    public:
        SceneManager();
        virtual ~SceneManager() = 0; // incase they need to delete some borrowed heap memory
    };
}}
#endif
