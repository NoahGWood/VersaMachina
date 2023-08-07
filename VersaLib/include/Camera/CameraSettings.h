#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

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
        };
    } // namespace Camera
    
} // namespace VersaMachina
