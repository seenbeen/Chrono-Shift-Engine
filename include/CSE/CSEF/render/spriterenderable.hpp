#ifndef CSEF_RENDER_SPRITERENDERABLE_HPP
#define CSEF_RENDER_SPRITERENDERABLE_HPP
#include <CSE/CSEA/render/renderable.hpp>

#include <string>
#include <map>

#include <CSE/CSELL/render/renderer.hpp>
#include <CSE/CSELL/render/mesh.hpp>
#include <CSE/CSELL/render/texture.hpp>
#include <CSE/CSELL/render/shaderProgram.hpp>

#include <CSE/CSEA/render/cachemanager.hpp>
#include <CSE/CSEA/render/camera.hpp>

namespace CSEF { namespace Render {
    class SpriteRenderable: public CSEA::Render::Renderable {
        // note that animation uses data which should persist at an outer scope
        // this saves time and memory if many many instances of the same sprite are being constructed
        class Animation {
            unsigned int nFrames;
            unsigned int *frames;
            int *originXs;
            int *originYs;
            float *delays;

            float animationLength; // for quick fast-track lookups

        public:
            Animation(unsigned int nFrames, unsigned int *frames, int *originXs, int *originYs, float *delays);
            ~Animation();
            void getDataAtTime(float time, unsigned int &resultFrame, int &originX, int &originY);
            float getAnimationLength();
        };

        bool isInitialized;

        std::map<std::string,Animation*> animationMap;

        Animation *currentAnimation;
        float currentTime;

        CSELL::Render::Texture *spriteSheet;
        CSELL::Render::Mesh *cutOuts;
        CSELL::Render::ShaderProgram *shaderProgram;

    protected:
        virtual bool onLoad(CSELL::Render::Renderer *renderer, CSEA::Render::CacheManager *cacheManager) = 0;
        virtual bool onUnload(CSELL::Render::Renderer *renderer, CSEA::Render::CacheManager *cacheManager) = 0;

        void onUpdate(double deltaTime);
        void onRender(CSEA::Render::Camera *camera);

        // set-up / clean-up methods called by child classes

        bool setup(CSELL::Render::Texture *spriteSheet, CSELL::Render::Mesh *cutOuts, CSELL::Render::ShaderProgram *shaderProgram);

        bool addAnimation(const std::string &name, unsigned int nFrames, unsigned int *frames,
                          int *originXs, int *originYs, float *delays);

        bool deleteAnimation(const std::string &name);

    public:
        SpriteRenderable();
        ~SpriteRenderable();

        // for manipulating animation frames
        bool setCurrentAnimation(const std::string &name);
        bool setCurrentAnimationTime(float time);
        float getCurrentAnimationTime();


        //unsigned int registerSpriteTrigger();
        //bool unregisterSpriteTrigger();
    };
}}
#endif // CSEF_RENDER_SPRITERENDERABLE_HPP

