#include "Versa.h"
#include <UI/ImGUILayer.h>
#include <iostream>
#include "imgui/imgui.h"

class ExampleLayer : public VersaMachina::Layer
{
    public:
        ExampleLayer()
        : Layer("Example"), m_Camera() {
        m_VertexArray.reset(VersaMachina::Render::VertexArray::Create());

        float vertices[3*7] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.6f,
            0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        };
        // Create vertex buffer
        m_VertexBuffer.reset(VersaMachina::Render::VertexBuffer::Create(sizeof(vertices), vertices));    
        VersaMachina::Render::BufferLayout layout = {
            {VersaMachina::Render::ShaderDataType::Float3, "a_Position"},
            {VersaMachina::Render::ShaderDataType::Float4, "a_Color"}
        };

        m_VertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        VM_CORE_ASSERT(m_VertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout elements.");

        unsigned int indices[3] = {0, 1, 2};
        m_IndexBuffer.reset(VersaMachina::Render::IndexBuffer::Create(3, indices));
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        // Square
        m_SquareVertexArray.reset(VersaMachina::Render::VertexArray::Create());

        float vertices2[3*4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
        };
        // Create vertex buffer
        m_SquareVertexBuffer.reset(VersaMachina::Render::VertexBuffer::Create(sizeof(vertices2), vertices2));    
        VersaMachina::Render::BufferLayout layout2 = {
            {VersaMachina::Render::ShaderDataType::Float3, "a_Position"}
        };

        m_SquareVertexBuffer->SetLayout(layout2);
        m_SquareVertexArray->AddVertexBuffer(m_SquareVertexBuffer);

        VM_CORE_ASSERT(m_SquareVertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout elements.");

        unsigned int indices2[6] = {0, 1, 2, 2, 3, 0};
        m_SquareIndexBuffer.reset(VersaMachina::Render::IndexBuffer::Create(6, indices2));
        m_SquareVertexArray->SetIndexBuffer(m_SquareIndexBuffer);

        // Shaders
        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;

            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position;
                gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
                v_Color = a_Color;
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;
            
            in vec3 v_Position;
            in vec4 v_Color;

            void main()
            {
                color = vec4(v_Position*0.5+0.5, 1.0);
                color = v_Color;
            }
        )";

        std::string vertexSrc2 = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;

            out vec3 v_Position;

            void main()
            {
                v_Position = a_Position;
                gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrc2 = R"(
            #version 330 core

            layout(location = 0) out vec4 color;
            
            void main()
            {
                color = vec4(0.5, 0.5, 0.8, 1.0);
            }
        )";
        m_SquareShader.reset(new VersaMachina::Render::Shader(vertexSrc2, fragmentSrc2));
        m_Shader.reset(new VersaMachina::Render::Shader(vertexSrc, fragmentSrc));
        }


        void OnAttach() override {}
        void OnDetach() override {}
        void OnUpdate(VersaMachina::Timestep ts) override
        {
//            VM_TRACE("Delta Time {0}s {1}", ts.GetSeconds(), ts.GetMilliseconds());
            if(VersaMachina::Input::Input::IsKeyPressed(VersaMachina::Key::LeftControl))
            {
                if (VersaMachina::Input::Input::IsKeyPressed(VersaMachina::Key::Up) ||
                    VersaMachina::Input::Input::IsKeyPressed(VersaMachina::Key::W))
                {
                    m_Camera.RotateZ(m_CameraRotationSpeed * ts.GetSeconds());
                }
                else if (VersaMachina::Input::Input::IsKeyPressed(VersaMachina::Key::Down) ||
                    VersaMachina::Input::Input::IsKeyPressed(VersaMachina::Key::S))
                {
                    m_Camera.RotateZ(-m_CameraRotationSpeed * ts.GetSeconds());
                }
                if (VersaMachina::Input::Input::IsKeyPressed(VersaMachina::Key::Left) ||
                    VersaMachina::Input::Input::IsKeyPressed(VersaMachina::Key::A))
                {
                    m_Camera.RotateZ(-m_CameraRotationSpeed * ts.GetSeconds());
                }
                else if (VersaMachina::Input::Input::IsKeyPressed(VersaMachina::Key::Right) ||
                    VersaMachina::Input::Input::IsKeyPressed(VersaMachina::Key::D))
                {
                        m_Camera.RotateZ(m_CameraRotationSpeed * ts.GetSeconds());
                }

            } else {
                if (VersaMachina::Input::Input::IsKeyPressed(VersaMachina::Key::Up) ||
                    VersaMachina::Input::Input::IsKeyPressed(VersaMachina::Key::W))
                {
                    m_Camera.TranslateY(-m_CameraSpeed * ts.GetSeconds());
                }
                else if (VersaMachina::Input::Input::IsKeyPressed(VersaMachina::Key::Down) ||
                    VersaMachina::Input::Input::IsKeyPressed(VersaMachina::Key::S))
                {
                    m_Camera.TranslateY(m_CameraSpeed * ts.GetSeconds());
                }
                if (VersaMachina::Input::Input::IsKeyPressed(VersaMachina::Key::Left) ||
                    VersaMachina::Input::Input::IsKeyPressed(VersaMachina::Key::A))
                {
                    m_Camera.TranslateX(m_CameraSpeed * ts.GetSeconds());
                }
                else if (VersaMachina::Input::Input::IsKeyPressed(VersaMachina::Key::Right) ||
                    VersaMachina::Input::Input::IsKeyPressed(VersaMachina::Key::D))
                {
                        m_Camera.TranslateX(-m_CameraSpeed * ts.GetSeconds());
                }
            }

            VersaMachina::Render::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
            VersaMachina::Render::RenderCommand::Clear();

//            m_Camera.SetRotation({0.0f, 0.0f, 45.0f});

            VersaMachina::Render::Renderer::BeginScene(m_Camera); //camera, lights, environment);
            
            VersaMachina::Render::Renderer::Submit(m_SquareShader, m_SquareVertexArray);
            VersaMachina::Render::Renderer::Submit(m_Shader, m_VertexArray);

            VersaMachina::Render::Renderer::EndScene();
        }


        virtual void OnImGuiRender() override
        {
            ImGui::Begin("Versa Editor");
            ImGui::Text("Hello World!");
            ImGui::SliderFloat("Camera Move Speed", &m_CameraSpeed, 1, 10, "%.3f");
            ImGui::SliderFloat("Camera Rotate Speed", &m_CameraRotationSpeed, 1.0f, 360.0f, "%.5f");
            ImGui::End();
        }

        void OnEvent(VersaMachina::Event& event) override
        {
        }

    private:
        std::shared_ptr<VersaMachina::Render::Shader> m_Shader;
        std::shared_ptr<VersaMachina::Render::VertexArray> m_VertexArray;
        std::shared_ptr<VersaMachina::Render::VertexBuffer> m_VertexBuffer;
        std::shared_ptr<VersaMachina::Render::IndexBuffer> m_IndexBuffer;

        std::shared_ptr<VersaMachina::Render::Shader> m_SquareShader;
        std::shared_ptr<VersaMachina::Render::VertexArray> m_SquareVertexArray;
        std::shared_ptr<VersaMachina::Render::VertexBuffer> m_SquareVertexBuffer;
        std::shared_ptr<VersaMachina::Render::IndexBuffer> m_SquareIndexBuffer;
    
        VersaMachina::Camera::Camera m_Camera;
        float m_CameraSpeed = 1;
        float m_CameraRotationSpeed = 15;


};


class VersaEditor : public VersaMachina::Application
{
    public:
        VersaEditor()
        {
            PushLayer(new ExampleLayer());
//            PushOverlay(new ImGUILayer());
            VM_INFO("Hello, VersaMachina World");
            VM_TRACE("Trace");
            VM_INFO("Info");
            VM_WARN("Warn");
            VM_ERROR("Error");
            VM_CRITICAL("Critical");
        }
        ~VersaEditor()
        {

        }
};

VersaMachina::Application* VersaMachina::CreateApplication()
{
    return new VersaEditor();
}