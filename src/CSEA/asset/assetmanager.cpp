#include <string>
#include <map>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/asset/assetmanager.hpp>

#include <CSE/CSEA/asset/assetmanager.hpp>

namespace CSEA { namespace Assets {
    AssetManager::AssetManager() {}
    AssetManager::~AssetManager() {}

    bool AssetManager::isInitialized = false;
    std::map<std::string, unsigned int> AssetManager::assetReferenceMap;
    std::map<std::string, CSELL::Assets::ImageAsset*> AssetManager::imageAssetMap;
    std::map<std::string, CSELL::Assets::TextAsset*> AssetManager::textAssetMap;

    bool AssetManager::initialize() {
        if (AssetManager::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Assets - AssetManager", "AssetManager is already Initialized!");
            return false;
        }

        AssetManager::isInitialized = CSELL::Assets::AssetManager::initialize();

        return AssetManager::isInitialized;
    }

    void AssetManager::shutdown() {
        if (!AssetManager::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Assets - AssetManager", "Trying to shutdown uninitialized AssetManager!");
            return;
        }

        if (AssetManager::assetReferenceMap.size()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA,
                             "Assets - AssetManager", "Not all loaded assets have been freed.");
        }

        AssetManager::isInitialized = false;

        CSELL::Assets::AssetManager::shutdown();
    }

    bool AssetManager::loadImage(const std::string &path) {
        if (!AssetManager::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Assets - AssetManager", "AssetManager is not Initialized!");
            return false;
        }

        std::map<std::string, unsigned int>::iterator it;
        it = AssetManager::assetReferenceMap.find(path);

        if (it != AssetManager::assetReferenceMap.end()) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Assets - AssetManager", "Asset Path " + path + " is already loaded!");
            return false;
        }

        CSELL::Assets::ImageAsset *asset = CSELL::Assets::AssetManager::loadImage(path);
        if (asset == NULL) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Assets - AssetManager", "ImageAsset Path " + path + " failed to load!");
            return false;
        }

        AssetManager::assetReferenceMap[path] = 1;
        AssetManager::imageAssetMap[path] = asset;

        CSU::Logger::log(CSU::Logger::INFO, CSU::Logger::CSEA, "Assets - AssetManager", "Loading an image with path \""+path+"\"");

        return true;
    }

    bool AssetManager::loadFile(const std::string &path) {
        if (!AssetManager::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Assets - AssetManager", "AssetManager is not Initialized!");
            return false;
        }

        std::map<std::string, unsigned int>::iterator it;
        it = AssetManager::assetReferenceMap.find(path);

        if (it != AssetManager::assetReferenceMap.end()) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Assets - AssetManager", "Asset Path " + path + " is already loaded!");
            return false;
        }

        CSELL::Assets::TextAsset *asset = CSELL::Assets::AssetManager::loadFile(path);

        if (asset == NULL) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Assets - AssetManager", "TextAsset Path " + path + " failed to load!");
            return false;
        }

        AssetManager::assetReferenceMap[path] = 1;
        AssetManager::textAssetMap[path] = asset;

        CSU::Logger::log(CSU::Logger::INFO, CSU::Logger::CSEA, "Assets - AssetManager", "Loading a file with path \""+path+"\"");

        return true;
    }


    CSELL::Assets::ImageAsset *AssetManager::getImage(const std::string &path) {
        if (!AssetManager::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Assets - AssetManager", "AssetManager is not Initialized!");
            return NULL;
        }

        std::map<std::string, CSELL::Assets::ImageAsset*>::iterator it;
        it = AssetManager::imageAssetMap.find(path);
        if (it == AssetManager::imageAssetMap.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA,
                             "Assets - AssetManager", "ImageAsset \""+path+"\" not loaded!");
            return NULL;
        }

        AssetManager::assetReferenceMap[path]++;

        return it->second;
    }

    CSELL::Assets::TextAsset *AssetManager::getFile(const std::string &path) {
        if (!AssetManager::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Assets - AssetManager", "AssetManager is not Initialized!");
            return NULL;
        }

        std::map<std::string, CSELL::Assets::TextAsset*>::iterator it;
        it = AssetManager::textAssetMap.find(path);
        if (it == AssetManager::textAssetMap.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA,
                             "Assets - AssetManager", "TextAsset \""+path+"\" not loaded!");
            return NULL;
        }

        AssetManager::assetReferenceMap[path]++;

        return it->second;
    }

    void AssetManager::releaseAsset(const std::string &path) {
        if (!AssetManager::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Assets - AssetManager", "AssetManager is not Initialized!");
            return;
        }

        std::map<std::string, unsigned int>::iterator it;
        it = AssetManager::assetReferenceMap.find(path);
        if (it == AssetManager::assetReferenceMap.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA,
                             "Assets - AssetManager", "Asset with path \""+path+"\" is not loaded!");
            return;
        } else if (it->second == 0) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA,
                             "Assets - AssetManager", "Asset with path \""+path+"\" has no references to release!");
            return;
        }
        AssetManager::assetReferenceMap[path]--;
    }

    void AssetManager::unloadAsset(const std::string &path) {
        if (!AssetManager::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Assets - AssetManager", "AssetManager is not Initialized!");
            return;
        }

        std::map<std::string, unsigned int>::iterator it;
        it = AssetManager::assetReferenceMap.find(path);

        if (it == AssetManager::assetReferenceMap.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA,
                             "Assets - AssetManager", "Asset with path \""+path+"\" is not loaded!");
            return;
        } else if (it->second) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA,
                             "Assets - AssetManager", "Asset with path \""+path+"\" still has references!");
            return;
        }

        AssetManager::assetReferenceMap.erase(it); // bai

        std::map<std::string, CSELL::Assets::ImageAsset*>::iterator imageIt;
        imageIt = AssetManager::imageAssetMap.find(path);
        if (imageIt != AssetManager::imageAssetMap.end()) {
            CSELL::Assets::AssetManager::freeAsset(imageIt->second);
            AssetManager::imageAssetMap.erase(imageIt);
            return;
        } else {
            std::map<std::string, CSELL::Assets::TextAsset*>::iterator textIt;
            textIt = AssetManager::textAssetMap.find(path);
            if (textIt !=  AssetManager::textAssetMap.end()) {
                CSELL::Assets::AssetManager::freeAsset(textIt->second);
                AssetManager::textAssetMap.erase(textIt);
                return;
            } else {
                CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Assets - AssetManager", "Asset with path \""+path+"\" was referenced, but not loaded!");
            }
        }
    }
}}
