#pragma once

#include "Camera/Camera.h"
#include "Core/Timestep.h"
#include "Events/Event.h"
#include "Events/MouseEvent.h"

#include <glm/glm.hpp>

namespace VersaMachina
{
    namespace Camera
    {
        class EditorCamera : public Camera::Camera
        {
        private:
            /* data */
            glm::vec3 m_Position = {0.0f,0.0f,0.0f};
            glm::vec3 m_FocalPoint = {0.0f,0.0f,0.0f};
            glm::vec2 m_InitialMousePos = {0.0f,0.0f};
            float m_Distance = 10.0f;
            float m_Pitch = 0.0f, m_Yaw = 0.0f;
            float m_ViewportWidth = 1280, m_ViewportHeight = 720;

        public:
            EditorCamera() {
                m_Settings->Type = CameraType::Perspective;
            }
            virtual ~EditorCamera() {}
        
            void OnUpdate(Timestep ts);
            void OnEvent(Event& e);
            void OnResize(int width, int height) { m_ViewportWidth = width; m_ViewportHeight = height; UpdateProjection(); }

            inline float GetDistance() const { return m_Distance; }
            inline void SetDistance(float distance) { m_Distance = distance; }
            
    		glm::vec3 GetUpDirection() const;
    		glm::vec3 GetRightDirection() const;
    		glm::vec3 GetForwardDirection() const;
    		const glm::vec3& GetPosition() const { return m_Position; }
    		glm::quat GetOrientation() const;

    		float GetPitch() const { return m_Pitch; }
    		float GetYaw() const { return m_Yaw; }
    	private:
    		void UpdateProjection();
    		void UpdateView();
    
    		bool OnMouseScroll(MouseScrolledEvent& e);
    
    		void MousePan(const glm::vec2& delta);
    		void MouseRotate(const glm::vec2& delta);
    		void MouseZoom(float delta);
    
    		glm::vec3 CalculatePosition() const;
    
    		std::pair<float, float> PanSpeed() const;
    		float RotationSpeed() const;
    		float ZoomSpeed() const;
        };
        
    } // namespace Camera
    
} // namespace VersaMachina
