#include <CSE/CSEA/render/scenemanager2d.hpp>

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
        if (aPos.z < bPos.z) {
            return true;
        } else if (aPos.z > bPos.z) {
            return false;
        } else {
            if (aPos.y > bPos.y) {
                return true;
            }
            return false;
        }
    }

    void SceneManager2D::getVisibleRenderables(Camera *camera, std::vector<Renderable*> &resultingRenderables) {
        this->renderables.sort(compareRenderables);
        std::list<Renderable*>::iterator it;
        for (it = this->renderables.begin(); it != this->renderables.end(); ++it) {
            resultingRenderables.push_back(*it);
        }
    }

    void SceneManager2D::addRenderable(Renderable *renderable) {
        this->renderables.push_back(renderable);
    }

    void SceneManager2D::removeRenderable(Renderable *renderable) {
        this->renderables.erase(std::find(this->renderables.begin(), this->renderables.end(), renderable));
    }

    void SceneManager2D::updateRenderable(Renderable *renderable) {
        // for now; will probably use a quadtree to organize this later
    }

    SceneManager2D::SceneManager2D() {}
    SceneManager2D::~SceneManager2D() {}
}}

