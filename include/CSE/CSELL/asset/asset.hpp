#ifndef CSELL_ASSETS_ASSET_HPP
#define CSELL_ASSETS_ASSET_HPP

class AssetManager;

namespace CSELL { namespace Assets {
    class Asset {
    friend class AssetManager;
        unsigned int assetID;
    protected:
        // only assetmanager should be making these calls
        Asset();
        virtual ~Asset();
    };
}}
#endif
