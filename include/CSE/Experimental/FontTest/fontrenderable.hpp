#ifndef EXPERIMENTAL_FONTTEST_FONTRENDERABLE_HPP
#define EXPERIMENTAL_FONTTEST_FONTRENDERABLE_HPP

#include <CSE/CSEA/render/renderable.hpp>
#include <CSE/CSEA/render/camera.hpp>
#include <CSE/CSEA/render/cachemanager.hpp>
#include <CSE/CSELL/render/renderer.hpp>
#include <CSE/CSELL/render/mesh.hpp>
#include <CSE/CSELL/render/shaderProgram.hpp>
#include <CSE/CSELL/render/texture.hpp>

#include <CSE/CSEA/font/fontrasterizer.hpp>
#include <CSE/CSEA/font/rasterizedfont.hpp>

namespace Experimental { namespace FontTest {
    class FontRenderable: public CSEA::Render::Renderable {
        CSEA::Font::RasterizedFont *rFont;
        CSELL::Render::Mesh *mesh;
        CSELL::Render::Texture *texture;
        CSELL::Render::ShaderProgram *shaderProgram;
    protected:
        bool onLoad(CSELL::Render::Renderer *renderer, CSEA::Render::CacheManager *cacheManager);
        bool onUnload(CSELL::Render::Renderer *renderer, CSEA::Render::CacheManager *cacheManager);
        void onUpdate(double deltaTime);
        void onRender(CSEA::Render::Camera *camera);

    public:
        FontRenderable();
        ~FontRenderable();
    };
}}
#endif // EXPERIMENTAL_FONTTEST_FONTRENDERABLE_HPP
