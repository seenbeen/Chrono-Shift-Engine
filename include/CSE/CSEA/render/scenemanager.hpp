#ifndef CSEA_RENDER_SCENEMANAGER_HPP
#define CSEA_RENDER_SCENEMANAGER_HPP

#include <vector>

#include <CSE/CSEA/render/renderable.hpp>
#include <CSE/CSEA/render/camera.hpp>

namespace CSEA { namespace Render {
    class Scene;

    class SceneManager {
    friend class Scene;
        // very abstract class, the internal storing implementation is completely up to the implementing classes
    protected:
        virtual void getVisibleRenderables(Camera *camera, std::vector<Renderable*> &resultingRenderables) = 0;
        virtual void addRenderable(Renderable *renderable) = 0;
        virtual void removeRenderable(Renderable *renderable) = 0;
        virtual void updateRenderable(Renderable *renderable) = 0;

    public:
        SceneManager();
        virtual ~SceneManager();
    };
}}
#endif
