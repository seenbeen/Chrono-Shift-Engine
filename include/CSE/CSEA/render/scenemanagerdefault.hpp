#ifndef CSEA_RENDER_SCENEMANAGERDEFAULT_HPP
#define CSEA_RENDER_SCENEMANAGERDEFAULT_HPP
#include <CSE/CSEA/render/scenemanager.hpp>

#include <vector>
#include <list>

#include <CSE/CSEA/render/renderable.hpp>
#include <CSE/CSEA/render/camera.hpp>

/*
    Very simple class, serving as the default implementation for a Scene.
    Returns all renderables in the scene in order of addition.
*/
namespace CSEA { namespace Render {
    class SceneManagerDefault: public SceneManager {
        std::list<Renderable*> renderables;
    protected:
        void getVisibleRenderables(Camera *camera, std::vector<Renderable*> &resultingRenderables);
        void addRenderable(Renderable *renderable);
        void removeRenderable(Renderable *renderable);
        void updateRenderable(Renderable *renderable);

    public:
        SceneManagerDefault();
        ~SceneManagerDefault();
    };
}}
#endif


