#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi
#include <glm/gtx/string_cast.hpp> // glm::to_string

namespace VersaMachina
{
    namespace Camera
    {
        enum CameraType
        {
            Orthographic=0,
            Perspective=1,
            Physical=2

        };

        enum FOVAxis
        {
            Vertical=0,
            Horizontal=1
        };

        struct CameraSettings
        {
            // Base Settings
            std::string Name = "Main Camera";
            CameraType Type = CameraType::Orthographic;
            glm::vec4 Viewport = glm::vec4{-1,1,-1,1}; // Left, Right, Bottom, Top
            // Field of View.
            float FieldOfView = 60.0f;
            FOVAxis FieldOfViewAxis = FOVAxis::Horizontal;
            // Aspect Ratio
            float AspectRatio = 1.777f;
            bool FixedAspectRatio = false;
            // Clip plane
            float NearClip = -1.0f;
            float FarClip = 1.0f;
            // Transform
            glm::mat4 Transform = glm::mat4{1};
            // Zoom
            float ZoomLevel = 1;
            // Speeds
            float MoveSpeed = 0.01f;
            float RotateSpeed = 10.0f;

        //     std::unordered_map<std::string, std::string> to_map()
        //     {
        //         std::unordered_map<std::string, std::string> out  = {
        //             {"Name", Name },
        //             {"CameraType", std::to_string(Type)},
        //             {"Viewport", glm::to_string(Viewport)},
        //             {"FieldOfView", std::to_string(FieldOfView) },
        //             {"FieldOfViewAxis", std::to_string(FieldOfViewAxis)},
        //             {"AspectRatio", std::to_string(AspectRatio)},
        //             {"FixedAspectRatio", std::to_string(FixedAspectRatio)},
        //             {"NearClip", std::to_string(NearClip)},
        //             {"FarClip", std::to_string(FarClip)},
        //             {"ZoomLevel", std::to_string(ZoomLevel)},
        //             {"MoveSpeed", std::to_string(MoveSpeed)},
        //             {"RotateSpeed", std::to_string(RotateSpeed) },
        //         };
        //         return out;
        // };
        };
    } // namespace Camera
    
} // namespace VersaMachina
