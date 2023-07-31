#include "pch.h"
#include "Render/Renderer2D.h"

#include "Render/VertexArray.h"
#include "Render/IndexBuffer.h"
#include "Render/VertexBuffer.h"
#include "Render/Shader.h"

#include "OpenGL/include/OpenGLShader.h"

namespace VersaMachina
{
    namespace Render
    {
        struct Renderer2DStorage
        {
            Ref<VertexArray> QuadVertexArray;
            Ref<Shader> TextureShader;
            Ref<Texture2D> WhiteTexture;
        };

        static Renderer2DStorage* s_Data;

        void Renderer2D::Init()
        {
            VM_PROFILE_FUNCTION();

            s_Data = new Renderer2DStorage();

            s_Data->QuadVertexArray = VertexArray::Create();

            float squareVertices[5*4] = {
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
                -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
            };
            // Create vertex buffer
            Ref<VertexBuffer> vb;
            vb.reset(VertexBuffer::Create(sizeof(squareVertices), squareVertices));
            BufferLayout layout = {
                {ShaderDataType::Float3, "a_Position"},
                {ShaderDataType::Float2, "a_TexCoord"},
            };
            vb->SetLayout(layout);
            s_Data->QuadVertexArray->AddVertexBuffer(vb);

            uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
            Ref<IndexBuffer> ib;
            ib.reset(IndexBuffer::Create(sizeof(indices)/sizeof(uint32_t),indices));
            s_Data->QuadVertexArray->SetIndexBuffer(ib);

            s_Data->WhiteTexture = Texture2D::Create(1, 1);
            uint32_t whiteTextureData = 0xffffffff;
            s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
            
            // Create shader
            s_Data->TextureShader = Shader::Create("VersaEditor/assets/shaders/Texture.glsl");
            s_Data->TextureShader->Bind();
            s_Data->TextureShader->SetInt("u_Texture", 0);

        }
        void Renderer2D::Shutdown()
        {
            VM_PROFILE_FUNCTION();

            delete s_Data;
        }
        void Renderer2D::BeginScene(const Camera::Camera& camera)
        {
            VM_PROFILE_FUNCTION();
            
            s_Data->TextureShader->Bind();
            s_Data->TextureShader->SetMat4("u_ViewProjection", camera.getViewProjectionMatrix());
        }
        void Renderer2D::EndScene()
        {
            VM_PROFILE_FUNCTION();
        }

        // Primitives
        void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
        {
            DrawQuad({position.x, position.y, 1.0f}, size, color);
        }
        void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
        {
            VM_PROFILE_FUNCTION();

            {
                VM_PROFILE_SCOPE("Setup Textures");        
                s_Data->TextureShader->SetFloat4("u_Color", color);
                // Bind white texture
                s_Data->WhiteTexture->Bind();
            }

            {
                VM_PROFILE_SCOPE("Setup Transform Shade");
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f});
                s_Data->TextureShader->SetMat4("u_Transform", transform);
            }
            
            {
                VM_PROFILE_SCOPE("Bind and draw indexed");
                s_Data->QuadVertexArray->Bind();
                RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
            }
        }

        void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
        {
            DrawQuad({position.x, position.y, 1.0f }, size, texture);
        }

        void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
        {
            DrawQuad(position, size, texture, glm::vec4(1.0f));
        }


        void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color)
        {
            VM_PROFILE_FUNCTION();
            
            s_Data->TextureShader->SetFloat4("u_Color", color);
            texture->Bind();

            glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 0.0f});
            s_Data->TextureShader->SetMat4("u_Transform", transform);

            s_Data->QuadVertexArray->Bind();
            RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
        }


    } // namespace Render
    
} // namespace VersaMachina
