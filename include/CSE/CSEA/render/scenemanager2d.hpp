#ifndef CSEA_RENDER_SCENEMANAGER2D_HPP
#define CSEA_RENDER_SCENEMANAGER2D_HPP
#include <CSE/CSEA/render/scenemanager.hpp>

#include <vector>
#include <list>

#include <CSE/CSEA/render/renderable.hpp>
#include <CSE/CSEA/render/camera.hpp>

namespace CSEA { namespace Render {
    class SceneManager2D: public SceneManager {
        std::list<Renderable*> renderables; // for easy adding and removing
    protected:
        void getVisibleRenderables(Camera *camera, std::vector<Renderable*> &resultingRenderables);
        void addRenderable(Renderable *renderable);
        void removeRenderable(Renderable *renderable);
        void updateRenderable(Renderable *renderable);

    public:
        SceneManager2D();
        ~SceneManager2D();
    };
}}
#endif

