#pragma once

#include <filesystem>

#include <glm/glm.hpp>
#include <json/json.h>

namespace Eendgine {

Json::Value jsonLoadFile(std::filesystem::path filePath);
glm::vec3
jsonVec3(const Json::Value& json, const std::string key, const std::filesystem::path path);
glm::vec2 jsonVec2(const Json::Value json, const std::string key, const std::filesystem::path path);
float jsonFloat(const Json::Value json, const std::string key, const std::filesystem::path path);
int jsonInt(const Json::Value json, const std::string key, const std::filesystem::path path);
std::string
jsonString(const Json::Value json, const std::string key, const std::filesystem::path path);

} // namespace Eendgine
