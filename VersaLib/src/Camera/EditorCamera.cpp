#include "Camera/EditorCamera.h"
#include "Core/Input.h"

#include <glm/gtx/quaternion.hpp>

namespace VersaMachina
{
    namespace Camera
    {
		void EditorCamera::UpdateProjection()
		{
			m_Settings->AspectRatio = m_ViewportWidth/m_ViewportHeight;
			m_ProjectionMatrix = glm::perspective(
                        glm::radians(m_Settings->FieldOfView),
                        m_Settings->AspectRatio,
                        m_Settings->NearClip,
                        m_Settings->FarClip
                        );

		}

		void EditorCamera::UpdateView()
		{
//			m_Yaw = 0.0f; // m_Pitch = 0.0f; // Lock the camera's rotation
			// Set camera position
			// Translation x rotation x scale
			m_Settings->Transform = glm::translate(glm::mat4(1.0f), CalculatePosition()) * glm::toMat4(GetOrientation());
			RecalculateViewMatrix();
		}

		std::pair<float, float> EditorCamera::PanSpeed() const
		{
			float x = std::min(m_ViewportWidth / 1000.0f, 2.4f); // max = 2.4f
			float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

			float y = std::min(m_ViewportHeight / 1000.0f, 2.4f); // max = 2.4f
			float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

			return { xFactor, yFactor };
		}

		float EditorCamera::RotationSpeed() const
		{
			return 0.8f;
		}

		float EditorCamera::ZoomSpeed() const
		{
			float distance = m_Distance * 0.2f;
			distance = std::max(distance, 0.0f);
			float speed = distance * distance;
			speed = std::min(speed, 100.0f); // max speed = 100
			return speed;
		}

		void EditorCamera::OnUpdate(Timestep ts)
		{
			auto m = Input::GetMousePos();
			const glm::vec2& mouse { m.first, m.second};
			glm::vec2 delta = (mouse - m_InitialMousePos) * 0.003f;
			m_InitialMousePos = mouse;
			
			if (Input::IsButtonPressed(Mouse::ButtonMiddle))
				MousePan(delta);
			else if (Input::IsButtonPressed(Mouse::ButtonRight))
				MouseRotate(delta);
			UpdateView();
		}

		void EditorCamera::OnEvent(Event& e)
		{
			EventDispatcher dispatcher(e);
			dispatcher.Dispatch<MouseScrolledEvent>(VM_BIND_EVENT_FN(EditorCamera::OnMouseScroll));
		}

		bool EditorCamera::OnMouseScroll(MouseScrolledEvent& e)
		{
			float delta = e.GetYOffset() * 0.1f;
			MouseZoom(delta);
			UpdateView();
			return false;
		}

		void EditorCamera::MousePan(const glm::vec2& delta)
		{
			auto [xSpeed, ySpeed] = PanSpeed();
			m_FocalPoint += -GetRightDirection() * delta.x * xSpeed * m_Distance;
			m_FocalPoint += GetUpDirection() * delta.y * ySpeed * m_Distance;
		}

		void EditorCamera::MouseRotate(const glm::vec2& delta)
		{
			float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
			m_Yaw += yawSign * delta.x * RotationSpeed();
			m_Pitch += delta.y * RotationSpeed();
		}

		void EditorCamera::MouseZoom(float delta)
		{
			m_Distance -= delta * ZoomSpeed();
			if (m_Distance < 1.0f)
			{
				m_FocalPoint += GetForwardDirection();
				m_Distance = 1.0f;
			}
		}

		glm::vec3 EditorCamera::GetUpDirection() const
		{
			return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
		}

		glm::vec3 EditorCamera::GetRightDirection() const
		{
			return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
		}

		glm::vec3 EditorCamera::GetForwardDirection() const
		{
			return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
		}

		glm::vec3 EditorCamera::CalculatePosition() const
		{
			return m_FocalPoint - GetForwardDirection() * m_Distance;
		}

		glm::quat EditorCamera::GetOrientation() const
		{
			return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
		}
	
	} // namespace Camera
	
} // namespace VersaMachina
