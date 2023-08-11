#pragma once

// For use by Versa Applications
#include "Core/Base.h"
#include "Core/Layer.h"
#include "Core/LayerStack.h"
#include "Core/Application.h"
#include "Core/Log.h"

// Math
#include "Math/Math.h"

// Time
#include "Core/Timestep.h"

// Keycodes
#include "Core/Input.h"
#include "Core/KeyCodes.h"
#include "Core/MouseCodes.h"

// Events
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/WindowEvent.h"
#include "Events/MouseEvent.h"

// ImGUI Layer
#include <imgui/imgui.h>
#include <ImGuizmo/ImGuizmo.h>
#include "UI/ImGUILayer.h"

// Entity Component System
#include "ECS/Scene.h"
#include "ECS/Entity.h"
#include "ECS/ScriptableEntity.h"
#include "ECS/Components.h"

// Rendering
#include "Render/BufferLayout.h"
#include "Render/IndexBuffer.h"
#include "Render/RenderCommand.h"
#include "Render/RenderContext.h"
#include "Render/Renderer.h"
#include "Render/Renderer2D.h"
#include "Render/RendererAPI.h"
#include "Render/Framebuffer.h"

// Shaders
#include "Render/Shader.h"

// Textures
#include "Render/Texture.h"

// Vertex
#include "Render/VertexArray.h"
#include "Render/VertexBuffer.h"

// Camera
#include "Camera/EditorCamera.h"
#include "Camera/Camera.h"
//#include "Camera/CameraController.h"
#include "Camera/CameraSettings.h"

// Profiler
#include "Profiler/Profiler.h"
#include <glm/gtc/type_ptr.hpp>
// Entry point
// #include "Core/Entry.h"