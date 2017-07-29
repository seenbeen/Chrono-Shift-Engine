#ifndef CSEA_ASSETS_ASSETMANAGER_HPP
#define CSEA_ASSETS_ASSETMANAGER_HPP
#include <map>
#include <string>

#include <CSE/CSELL/asset/assetmanager.hpp>

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

        // gimme singleton.
        AssetManager();
        ~AssetManager();

        static bool initialize();
        static void shutdown();

    public:
        // actual loading and releasing of memory
        // will result in false if something went wrong, or asset has already been loaded
        static bool loadImage(const std::string &path);
        static bool loadFile(const std::string &path);

        // returns loaded assets
        // will result in NULL if asset isn't already loaded
        static CSELL::Assets::ImageAsset *getImage(const std::string &path);
        static CSELL::Assets::TextAsset *getFile(const std::string &path);

        // internally tracks references per
        static void releaseAsset(const std::string &path);
        // actual unloading
        static void unloadAsset(const std::string &path);

    };
}}
#endif
