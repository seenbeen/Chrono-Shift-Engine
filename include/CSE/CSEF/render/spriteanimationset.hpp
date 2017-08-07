#ifndef CSEF_RENDER_SPRITEANIMATIONSET_HPP
#define CSEF_RENDER_SPRITEANIMATIONSET_HPP
#include <map>
#include <string>

namespace CSEF { namespace Render {
    class SpriteAnimationSet {
        // Note: SpriteAnimation copies over data passed in.
        //       It's still the caller's responsibility to free their arguments.
        class SpriteAnimation {
            unsigned int nFrames;
            unsigned int *frames;
            int *originXs;
            int *originYs;
            float *delays;

            float animationLength; // for quick fast-track lookups

        public:
            SpriteAnimation(unsigned int nFrames, unsigned int *frames, int *originXs, int *originYs, float *delays);
            ~SpriteAnimation();
            void getDataAtTime(float time, unsigned int &resultFrame, int &originX, int &originY);
            float getAnimationLength();
        };

        std::map<std::string,SpriteAnimation*> animationMap;
    public:
        SpriteAnimationSet();
        ~SpriteAnimationSet();

        bool addAnimation(const std::string &name, unsigned int nFrames, unsigned int *frames,
                          int *originXs, int *originYs, float *delays);
        bool deleteAnimation(const std::string &name);
        bool getAnimationDataAtTime(const std::string &name, float time,
                                    unsigned int &resultFrame, int &originX, int &originY);
        bool getAnimationLength(const std::string &name, float &length);
    };
}}
#endif // CSEF_RENDER_SPRITEANIMATIONSET_HPP
