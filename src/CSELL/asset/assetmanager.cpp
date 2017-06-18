#include <unordered_map>
#include <cstddef>
#include <string>

#include <CSE/CSELL/asset/assetmanager.hpp>
#include <CSE/CSELL/asset/asset.hpp>
#include <CSE/CSELL/asset/image.hpp>
#include <CSE/CSELL/asset/text.hpp>
#include <CSE/CSU/logger.hpp>

namespace CSELL { namespace Assets {
    unsigned int AssetManager::assetCount = 0;
    bool AssetManager::isInitialized = false;
    std::unordered_map<unsigned int, Asset*> AssetManager::assets;

    bool AssetManager::ensureInit() {
        if (!AssetManager::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL, "Assets - AssetManager", "AssetManager not Initialized!");
            return false;
        }
        return true;
    }

    AssetManager::AssetManager() {}
    AssetManager::~AssetManager() {}

    bool AssetManager::initialize() {
        if (AssetManager::isInitialized) {
            return false;
        }
        // doesn't do much for now
        AssetManager::isInitialized = true;
        return true;
    }

    void AssetManager::shutdown() {
        if (!AssetManager::ensureInit())
            return;
        // prevent leakage
        std::unordered_map<unsigned int, Asset*>::iterator it;
        for (it = AssetManager::assets.begin(); it != AssetManager::assets.end(); it++) {
            delete it->second;
        }
        AssetManager::isInitialized = false;
    }

    void AssetManager::freeAsset(Asset *asset) {
        if (!AssetManager::ensureInit())
            return;

        std::unordered_map<unsigned int, Asset*>::iterator it;
        it = AssetManager::assets.find(asset->assetID);

        if (it == AssetManager::assets.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Assets - AssetManager", "Attempting to free a non-existent asset!");
            return;
        }

        delete it->second;

        AssetManager::assets.erase(it);
    }

    ImageAsset *AssetManager::loadImage(const std::string &path, bool isPNG) {
        if (!AssetManager::ensureInit())
            return NULL;
        ImageAsset *asset = new ImageAsset(path, isPNG);
        asset->assetID = AssetManager::assetCount++;
        AssetManager::assets[asset->assetID] = asset;
        return asset;
    }

    TextAsset *AssetManager::loadFile(const std::string &path) {
        if (!AssetManager::ensureInit())
            return NULL;
        TextAsset *asset = new TextAsset(path);
        asset->assetID = AssetManager::assetCount++;
        AssetManager::assets[asset->assetID] = asset;
        return asset;
    }

}}
