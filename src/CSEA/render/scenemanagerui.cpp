#include <CSE/CSEA/render/scenemanagerui.hpp>

#include <algorithm>
#include <vector>
#include <list>

#include <CSE/CSELL/math/transform.hpp>
#include <CSE/CSELL/math/vector3f.hpp>

#include <CSE/CSEA/render/renderable.hpp>
#include <CSE/CSEA/render/camera.hpp>

namespace CSEA { namespace Render {
    static bool compareRenderables(Renderable *A, Renderable *B) {
        CSELL::Math::Vector3f &aPos = A->getTransform()->position;
        CSELL::Math::Vector3f &bPos = B->getTransform()->position;
        return aPos.z < bPos.z;
    }

    void SceneManagerUI::getVisibleRenderables(Camera *camera, std::vector<Renderable*> &resultingRenderables) {
        this->renderables.sort(compareRenderables);
        std::list<Renderable*>::iterator it;
        for (it = this->renderables.begin(); it != this->renderables.end(); ++it) {
            resultingRenderables.push_back(*it);
        }
    }

    void SceneManagerUI::addRenderable(Renderable *renderable) {
        this->renderables.push_back(renderable);
    }

    void SceneManagerUI::removeRenderable(Renderable *renderable) {
        this->renderables.erase(std::find(this->renderables.begin(), this->renderables.end(), renderable));
    }

    void SceneManagerUI::updateRenderable(Renderable *renderable) {
        // for now; will probably use a quadtree to organize this later
    }

    SceneManagerUI::SceneManagerUI() {}
    SceneManagerUI::~SceneManagerUI() {}
}}


