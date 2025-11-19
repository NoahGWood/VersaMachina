/**
 * @file Base.h
 * @author Noah G. Wood (@Noah G. Wood)
 * @brief Core pch for shared types, utils, and GLM config
 * @version 0.1
 * @date 2025-07-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once
#include <set>
#include <chrono>
#include <memory>
#include <string>
#include <vector>
#include <variant>
#include <filesystem>
#include <functional>
#include <optional>
#include <stddef.h>
#include <stdint.h>
#include <unordered_map>
#include <cassert>
#include <fstream>
#include <csignal>
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <atomic>
#include <regex>
// ImGui
#include <imgui.h>
#include <imgui_stdlib.h>
// EnTT
#include <entt/entt.hpp>

// YAML
#include <yaml-cpp/yaml.h>

// GLM
// #ifndef GLM_FORCE_RADIANS
    // #define GLM_FORCE_RADIANS
// #endif
// #ifndef GLM_ENABLE_EXPERIMENTAL
    // #define GLM_ENABLE_EXPERIMENTAL
// #endif
#include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtx/transform.hpp>
// using json = nlohmann::json;

// TFD
#include <tinyfiledialogs.h>
// PlatformDirs
#include <platform_dirs.hpp>

namespace fs = std::filesystem;


#include <common/Logger.h>
