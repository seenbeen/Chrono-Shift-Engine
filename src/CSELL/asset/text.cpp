#include <fstream>
#include <sstream>
#include <cstring>
#include <string>

#include <CSE/CSU/logger.hpp>
#include <CSE/CSELL/asset/text.hpp>

namespace CSELL { namespace Assets {
    TextAsset::TextAsset(const std::string &path) {
        std::ostringstream oss;
        std::ifstream file;

        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            file.open(path.c_str());
            oss << file.rdbuf();
            file.close();
        } catch (const std::ifstream::failure &e) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL, "AssetManager - TextAsset", e.what());
        }
        this->contents = new std::string(oss.str());

    }

    TextAsset::~TextAsset() {
        delete this->contents;
    }

    std::string *TextAsset::getContents() { return this->contents; }
}}

