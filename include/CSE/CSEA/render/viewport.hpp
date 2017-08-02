#ifndef CSEA_RENDER_VIEWPORT_HPP
#define CSEA_RENDER_VIEWPORT_HPP

#include <CSE/CSELL/render/renderer.hpp>

#include <CSE/CSEA/render/scene.hpp>
#include <CSE/CSEA/render/camera.hpp>
#include <CSE/CSEA/render/overlay.hpp>

namespace CSEA { namespace Render {
    class Viewport {
    friend class Renderer;
        unsigned int x, y, width, height;

        Camera *boundCamera;
        Overlay *boundOverlay;
        Scene *boundScene;

        void render(CSELL::Render::Renderer *renderer);
    public:
        Viewport(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
        ~Viewport();

        // bind functions can be null to unbind
        void bindCamera(Camera *cam);
        void bindOverlay(Overlay *overlay);
        void bindScene(Scene *scene);

        void setPosition(unsigned int x, unsigned int y);
        void setDimensions(unsigned int w, unsigned int h);
    };
}}
#endif
