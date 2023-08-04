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
            None = 0,
            Orthographic,
            Perspective,
            Physical
        };
        
        enum FOVAxis
        {
            Vertical,
            Horizontal
        };

        struct CameraSettings
        {
            // Base Settings
            std::string Name = "Main Camera";
            CameraType Type = CameraType::Orthographic;
            glm::vec4 Viewport = {-1,1,-1,1}; // Left, Right, Bottom, Top
            // Field of View.
            float FieldOfView = 60.0f;
            FOVAxis FieldOfViewAxis = FOVAxis::Horizontal;
            // Aspect Ratio
            float AspectRatio = 1.777f;
            // Clip plane
            float NearClip = -10.0f;
            float FarClip = 10.0f;
            // Positional
            glm::vec3 Position = {0,0,0};
            glm::vec3 Rotation = {0,0,0};
            // Zoom
            float ZoomLevel = 1;
            // Speeds
            float MoveSpeed = 0.01f;
            float RotateSpeed = 10.0f;
        };
    } // namespace Camera
    
} // namespace VersaMachina
