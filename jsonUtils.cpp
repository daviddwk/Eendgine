#include "jsonUtils.hpp"

#include <fstream>

#include "fatalError.hpp"

namespace Eendgine {

Json::Value jsonLoadFile(std::filesystem::path filePath) {
    Json::Value rootJson;
    std::ifstream file = std::ifstream(filePath);
    if (!file.is_open()) {
        fatalError("could not open: " + filePath.string());
    }
    try {
        file >> rootJson;
    } catch (...) {
        fatalError("improper json: " + filePath.string());
    }
    return rootJson;
}

glm::vec3
jsonVec3(const Json::Value& json, const std::string key, const std::filesystem::path path) {
    if (!json[key].isArray()) {
        fatalError("Missing \"" + key + "\" array: " + path.string());
    }
    for (int i = 0; i < 2; ++i) {
        if (!json[key][i].isNumeric()) {
            fatalError("\"" + key + "\" array incorrect: " + path.string());
        }
    }
    return glm::vec3(json[key][0].asFloat(), json[key][1].asFloat(), json[key][2].asFloat());
}

glm::vec2
jsonVec2(const Json::Value json, const std::string key, const std::filesystem::path path) {
    if (!json[key].isArray()) {
        fatalError("Missing \"" + key + "\" array: " + path.string());
    }
    for (int i = 0; i < 2; ++i) {
        if (!json[key][i].isNumeric()) {
            fatalError("\"" + key + "\" array incorrect: " + path.string());
        }
    }
    return glm::vec2(json[key][0].asFloat(), json[key][1].asFloat());
}

float jsonFloat(const Json::Value json, const std::string key, const std::filesystem::path path) {
    if (!json[key].isNumeric()) {
        fatalError("\"" + key + "\" not a string: " + path.string());
    }
    return json[key].asFloat();
}

std::string
jsonString(const Json::Value json, const std::string key, const std::filesystem::path path) {
    if (!json[key].isString()) {
        fatalError("\"" + key + "\" not a string: " + path.string());
    }
    return json[key].asString();
}

} // namespace Eendgine
