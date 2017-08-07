#ifndef CSEA_ASSETS_ASSETMANAGER_HPP
#define CSEA_ASSETS_ASSETMANAGER_HPP
#include <map>
#include <string>

#include <CSE/CSELL/asset/assetmanager.hpp>
#include <CSE/CSELL/asset/text.hpp>
#include <CSE/CSELL/asset/image.hpp>

#include <CSE/CSEA/asset/spriteanimationset.hpp>

namespace CSEA { namespace Core {
    class Engine; // forward decls
}}

namespace CSEA { namespace Assets {
    /*
        AssetManager - A class that manages resource initiating via instances n stuff
    */

    class AssetManager {
    friend class CSEA::Core::Engine;
        static bool isInitialized;

        static std::map<std::string, unsigned int> assetReferenceMap;
        static std::map<std::string, CSELL::Assets::ImageAsset*> imageAssetMap;
        static std::map<std::string, CSELL::Assets::TextAsset*> textAssetMap;
        static std::map<std::string, CSEA::Assets::SpriteAnimationSet*> spriteSetMap;

        // gimme singleton.
        AssetManager();
        ~AssetManager();

        static bool initialize();
        static void shutdown();

    public:
        // actual loading and releasing of memory
        // will result in NULL if something went wrong, or asset has already been loaded
        static CSELL::Assets::ImageAsset *loadImage(const std::string &path);
        static CSELL::Assets::TextAsset *loadFile(const std::string &path);
        static CSEA::Assets::SpriteAnimationSet *loadSpriteAnimationSet(const std::string &path);
        // for now just allocates an anim set. In future will also parse

        // returns loaded assets
        // will result in NULL if asset isn't already loaded
        static CSELL::Assets::ImageAsset *getImage(const std::string &path);
        static CSELL::Assets::TextAsset *getFile(const std::string &path);
        static CSEA::Assets::SpriteAnimationSet *getSpriteAnimationSet(const std::string &path);

        // internally tracks references per
        static void releaseAsset(const std::string &path);
        // actual unloading
        static void unloadAsset(const std::string &path);

    };
}}
#endif
