#include <CSE/CSEA/asset/spriteanimationset.hpp>

#include <math.h>

#include <CSE/CSU/logger.hpp>

namespace CSEA { namespace Assets {
    SpriteAnimationSet::SpriteAnimation::SpriteAnimation(unsigned int nFrames, unsigned int *frames,
                                                         int *originXs, int *originYs, float *delays) {
        this->nFrames = nFrames;
        this->frames = new unsigned int[this->nFrames];
        this->originXs = new int[this->nFrames];
        this->originYs = new int[this->nFrames];
        this->delays = new float[this->nFrames];

        this->animationLength = 0.0f;
        for (unsigned int i = 0; i < nFrames; ++i) {
            this->frames[i] = frames[i];
            this->originXs[i] = originXs[i];
            this->originYs[i] = originYs[i];
            this->delays[i] = delays[i];
            this->animationLength += this->delays[i];
        }
    }

    SpriteAnimationSet::SpriteAnimation::~SpriteAnimation() {
        delete[] this->frames;
        delete[] this->originXs;
        delete[] this->originYs;
        delete[] this->delays;
    }

    void SpriteAnimationSet::SpriteAnimation::getDataAtTime(float time, unsigned int &resultFrame,
                                                            int &originX, int &originY) {
        time = fmod(time, this->animationLength);

        for (unsigned int i = 0; i < this->nFrames; ++i) {
            time -= this->delays[i];
            if (time <= 0) {
                resultFrame = this->frames[i];
                originX = this->originXs[i];
                originY = this->originYs[i];
                return;
            }
        }
        resultFrame = this->frames[this->nFrames - 1];
        originX = this->originXs[this->nFrames - 1];
        originY = this->originYs[this->nFrames - 1];
    }

    float SpriteAnimationSet::SpriteAnimation::getAnimationLength() {
        return this->animationLength;
    }

    SpriteAnimationSet::SpriteAnimationSet() {}

    SpriteAnimationSet::~SpriteAnimationSet() {
        std::map<std::string,SpriteAnimation*>::iterator it;
        for (it = this->animationMap.begin(); it != this->animationMap.end(); ++it) {
            delete it->second;
        }
    }

    bool SpriteAnimationSet::addAnimation(const std::string &name, unsigned int nFrames, unsigned int *frames,
                                          int *originXs, int *originYs, float *delays) {
        std::map<std::string,SpriteAnimation*>::iterator it = this->animationMap.find(name);
        if (it != this->animationMap.end()) {
            CSU::Logger::log(CSU::Logger::WARN,  CSU::Logger::CSEA, "Assets - SpriteAnimationSet",
                             "Trying to add existing animation.");
            return false;
        }
        this->animationMap[name] = new SpriteAnimation(nFrames, frames, originXs, originYs, delays);
        return true;
    }

    bool SpriteAnimationSet::deleteAnimation(const std::string &name) {
        std::map<std::string,SpriteAnimation*>::iterator it = this->animationMap.find(name);
        if (it == this->animationMap.end()) {
            CSU::Logger::log(CSU::Logger::WARN,  CSU::Logger::CSEA, "Assets - SpriteAnimationSet",
                             "Trying to delete non-existent animation.");
            return false;
        }

        delete it->second;
        this->animationMap.erase(it);

        return true;
    }

    bool SpriteAnimationSet::getAnimationDataAtTime(const std::string &name, float time,
                                                    unsigned int &resultFrame, int &originX, int &originY) {
        std::map<std::string,SpriteAnimation*>::iterator it = this->animationMap.find(name);
        if (it == this->animationMap.end()) {
            CSU::Logger::log(CSU::Logger::WARN,  CSU::Logger::CSEA, "Assets - SpriteAnimationSet",
                             "Trying to fetch data of non-existent animation.");
            return false;
        }
        it->second->getDataAtTime(time, resultFrame, originX, originY);
        return true;
    }

    bool SpriteAnimationSet::getAnimationLength(const std::string &name, float &length) {
        std::map<std::string,SpriteAnimation*>::iterator it = this->animationMap.find(name);
        if (it == this->animationMap.end()) {
            CSU::Logger::log(CSU::Logger::WARN,  CSU::Logger::CSEA, "Assets - SpriteAnimationSet",
                             "Trying to fetch length of non-existent animation.");
            return false;
        }
        length = it->second->getAnimationLength();
        return true;
    }
}}
