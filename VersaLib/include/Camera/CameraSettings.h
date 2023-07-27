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
            glm::vec3 Transform = {0,0,0};
            glm::vec3 Rotation = {0,0,0};
            glm::vec4 Viewport = {-1.6,1.6,-0.9f,0.9f}; // Left, Right, Bottom, Top
            // Field of View.
            float FieldOfView = 60.0f;
            FOVAxis FieldOfViewAxis = FOVAxis::Horizontal;
            // Aspect Ratio
            float AspectRatio = 1.777f;
            // Clip plane
//            float NearClip = 0.01f;
//            float FarClip = 1000.0f;
            float NearClip = -1.0f;
            float FarClip = 1.0f;
        };
    } // namespace Camera
    
} // namespace VersaMachina
