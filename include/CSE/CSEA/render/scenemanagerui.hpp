#ifndef CSEA_RENDER_SCENEMANAGERUI_HPP
#define CSEA_RENDER_SCENEMANAGERUI_HPP
#include <CSE/CSEA/render/scenemanager.hpp>

#include <vector>
#include <list>

#include <CSE/CSEA/render/renderable.hpp>
#include <CSE/CSEA/render/camera.hpp>

namespace CSEA { namespace Render {
    class SceneManagerUI: public SceneManager {
        std::list<Renderable*> renderables; // for easy adding and removing
    protected:
        void getVisibleRenderables(Camera *camera, std::vector<Renderable*> &resultingRenderables);
        void addRenderable(Renderable *renderable);
        void removeRenderable(Renderable *renderable);
        void updateRenderable(Renderable *renderable);

    public:
        SceneManagerUI();
        ~SceneManagerUI();
    };
}}
#endif


