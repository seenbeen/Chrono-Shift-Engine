#include <CSE/CSEA/render/scenemanagerdefault.hpp>

#include <algorithm>
#include <vector>
#include <list>

#include <CSE/CSEA/render/renderable.hpp>
#include <CSE/CSEA/render/camera.hpp>

namespace CSEA { namespace Render {
    void SceneManagerDefault::getVisibleRenderables(Camera *camera, std::vector<Renderable*> &resultingRenderables) {
        // just return our list
        std::list<Renderable*>::iterator it;
        for (it = this->renderables.begin(); it != this->renderables.end(); ++it) {
            resultingRenderables.push_back(*it);
        }
    }

    void SceneManagerDefault::addRenderable(Renderable *renderable) {
        this->renderables.push_back(renderable);
    }

    void SceneManagerDefault::removeRenderable(Renderable *renderable) {
        this->renderables.erase(std::find(this->renderables.begin(), this->renderables.end(), renderable));
    }

    void SceneManagerDefault::updateRenderable(Renderable *renderable) {
        // blank. default implementation ignores renderable dirtyness
    }

    SceneManagerDefault::SceneManagerDefault() {}

    SceneManagerDefault::~SceneManagerDefault() {}
}}
