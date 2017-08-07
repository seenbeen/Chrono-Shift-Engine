#ifndef CSEA_RENDER_SPRITERENDERABLE_HPP
#define CSEA_RENDER_SPRITERENDERABLE_HPP
#include <CSE/CSEA/render/renderable.hpp>

#include <string>
#include <map>

#include <CSE/CSELL/render/renderer.hpp>
#include <CSE/CSELL/render/mesh.hpp>
#include <CSE/CSELL/render/texture.hpp>
#include <CSE/CSELL/render/shaderProgram.hpp>

#include <CSE/CSEA/render/cachemanager.hpp>
#include <CSE/CSEA/render/camera.hpp>

#include <CSE/CSEA/asset/spriteanimationset.hpp>

namespace CSEA { namespace Render {
    class SpriteRenderable: public CSEA::Render::Renderable {
        bool isInitialized;

        CSELL::Render::Texture *spriteSheet;
        CSELL::Render::Mesh *cutOuts;
        CSELL::Render::ShaderProgram *shaderProgram;
        CSEA::Assets::SpriteAnimationSet *animSet;

        std::string currentAnimation;
        float currentAnimationLength;
        float currentTime;

    protected:
        virtual bool onLoad(CSELL::Render::Renderer *renderer, CSEA::Render::CacheManager *cacheManager) = 0;
        virtual bool onUnload(CSELL::Render::Renderer *renderer, CSEA::Render::CacheManager *cacheManager) = 0;

        void onUpdate(double deltaTime);
        void onRender(CSEA::Render::Camera *camera);

        // set-up / clean-up methods called by child classes

        bool setup(CSEA::Assets::SpriteAnimationSet *animSet, CSELL::Render::Texture *spriteSheet, CSELL::Render::Mesh *cutOuts, CSELL::Render::ShaderProgram *shaderProgram);
    public:
        SpriteRenderable();
        ~SpriteRenderable();

        // for manipulating animations and frames
        bool setCurrentAnimation(const std::string &name);
        std::string getCurrentAnimation();

        bool setCurrentAnimationTime(float time);
        float getCurrentAnimationTime();

        unsigned int registerSpriteTrigger();
        bool unregisterSpriteTrigger();
    };
}}
#endif

