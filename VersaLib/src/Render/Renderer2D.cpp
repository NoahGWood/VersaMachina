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
        struct QuadVertex
        {
            glm::vec3 Position;
            glm::vec4 Color;
            glm::vec2 TexCoord;
            float TexIndex;
            float TilingFactor;

            // Editor only
            int EntityID;
        };

        struct Renderer2DData
        {
            static const uint32_t MaxQuads = 10000;            // Max for a draw call
            static const uint32_t MaxVertices = MaxQuads * 4;  // Max for a draw call
            static const uint32_t MaxIndices = MaxQuads * 6;   // Max for a draw call
            static const uint32_t MaxTextureSlots = 32;   // TODO: RenderCaps, Max for a draw call

            Ref<VertexArray> QuadVertexArray;
            Ref<VertexBuffer> QuadVertexBuffer;
            Ref<Shader> TextureShader;
            Ref<Texture2D> WhiteTexture;

            uint32_t QuadIndexCount = 0;
            QuadVertex* QuadVertexBufferBase = nullptr;
            QuadVertex* QuadVertexBufferPtr = nullptr;

            std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
            uint32_t TextureSlotIndex = 1; // 0 = White Texture

            glm::vec4 QuadVertexPositions[4];

            Statistics Stats;
        };

        static Renderer2DData s_Data;

        void Renderer2D::Init()
        {
            VM_PROFILE_FUNCTION();

            s_Data.QuadVertexArray = VertexArray::Create();

            // Create vertex buffer
            s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));

            s_Data.QuadVertexBuffer->SetLayout({
                {ShaderDataType::Float3, "a_Position"},
                {ShaderDataType::Float4, "a_Color"},
                {ShaderDataType::Float2, "a_TexCoord"},
                {ShaderDataType::Float, "a_TexIndex"},
                {ShaderDataType::Float, "a_TilingFactor"},
                {ShaderDataType::Int, "a_EntityID"}
            });
            s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

            s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

            uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

            uint32_t offset=0;
            for(uint32_t i=0; i < s_Data.MaxIndices; i+=6)
            {
                quadIndices[i + 0] = offset + 0;
                quadIndices[i + 1] = offset + 1;
                quadIndices[i + 2] = offset + 2;
                
                quadIndices[i + 3] = offset + 2;
                quadIndices[i + 4] = offset + 3;
                quadIndices[i + 5] = offset + 0;

                offset += 4;
            }

            Ref<IndexBuffer> quadIB = IndexBuffer::Create(s_Data.MaxIndices, quadIndices);
            s_Data.QuadVertexArray->SetIndexBuffer(quadIB);

            delete[] quadIndices;

            s_Data.WhiteTexture = Texture2D::Create(1, 1);
            uint32_t whiteTextureData = 0xffffffff;
            s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
            
            // Create samples
            int32_t samplers[s_Data.MaxTextureSlots];
            for(uint32_t i=0; i<s_Data.MaxTextureSlots; i++)
            {
                samplers[i] = i;
            }

            // Create shader
            s_Data.TextureShader = Shader::Create("VersaEditor/assets/shaders/Texture.glsl");
            s_Data.TextureShader->Bind();
            s_Data.TextureShader->SetIntArray("u_Textures", samplers, s_Data.MaxTextureSlots);

            s_Data.TextureSlots[0] = s_Data.WhiteTexture;

            s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
            s_Data.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
            s_Data.QuadVertexPositions[2] = { 0.5f, 0.5f, 0.0f, 1.0f };
            s_Data.QuadVertexPositions[3] = { -0.5f, 0.5f, 0.0f, 1.0f };
        }
        void Renderer2D::Shutdown()
        {
            VM_PROFILE_FUNCTION();
        }
        void Renderer2D::BeginScene(const Camera::Camera& camera)
        {
            VM_PROFILE_FUNCTION();
            
            s_Data.TextureShader->Bind();
            s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

            s_Data.QuadIndexCount = 0;
            s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

            s_Data.TextureSlotIndex = 1;
        }
        void Renderer2D::BeginScene(const Camera::EditorCamera& camera)
        {
            VM_PROFILE_FUNCTION();
            
            s_Data.TextureShader->Bind();
            s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

            s_Data.QuadIndexCount = 0;
            s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

            s_Data.TextureSlotIndex = 1;
        }
        void Renderer2D::BeginScene(const Camera::Camera* camera)
        {
            VM_PROFILE_FUNCTION();
            
            s_Data.TextureShader->Bind();
            s_Data.TextureShader->SetMat4("u_ViewProjection", camera->GetViewProjectionMatrix());

            s_Data.QuadIndexCount = 0;
            s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

            s_Data.TextureSlotIndex = 1;
        }
        void Renderer2D::EndScene()
        {
            VM_PROFILE_FUNCTION();

            uint32_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
            s_Data.QuadVertexBuffer->SetData(dataSize, s_Data.QuadVertexBufferBase);

            Flush();
        }

        void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec3& position,
            const glm::vec4& color, const glm::vec2& size, const glm::vec3& rotation,
            const Ref<Texture2D>& texture, float tilingFactor, const int entityID)
        {
            // Check if all textures register
            if(s_Data.QuadIndexCount >= s_Data.MaxIndices)
            {
                FlushAndReset();   
            }
            else if(s_Data.TextureSlotIndex > s_Data.MaxTextureSlots-1)
            {
                FlushAndReset();
            }

            float textureIndex = -1.0f;

            if(texture == nullptr)
            {
                textureIndex = 0.0f;
            } else {
                for(uint32_t i=0; i<s_Data.TextureSlotIndex; i++)
                {
                    if(*s_Data.TextureSlots[i].get() == *texture.get())
                    {
                        textureIndex = (float)i;
                        break;
                    }
                }
                if(textureIndex == -1.0f)
                {
                    textureIndex = (float)s_Data.TextureSlotIndex;
                    s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
                    s_Data.TextureSlotIndex++;
                }
            }
            glm::mat4 tmatrix;
            if(transform == glm::mat4{0})
            {
                tmatrix = glm::translate(glm::mat4(1.0f), position)
                    * glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), {0.0f, 0.0f, 1.0f})
                    * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
            } else {
                tmatrix = transform;
            }

    		s_Data.QuadVertexBufferPtr->Position = tmatrix * s_Data.QuadVertexPositions[0];
    		s_Data.QuadVertexBufferPtr->Color = color;
    		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
    		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
    		s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
    		s_Data.QuadVertexBufferPtr->EntityID = entityID;
    		s_Data.QuadVertexBufferPtr++;

	    	s_Data.QuadVertexBufferPtr->Position = tmatrix * s_Data.QuadVertexPositions[1];
	    	s_Data.QuadVertexBufferPtr->Color = color;
	    	s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
    		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
    		s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
    		s_Data.QuadVertexBufferPtr->EntityID = entityID;
	    	s_Data.QuadVertexBufferPtr++;

		    s_Data.QuadVertexBufferPtr->Position = tmatrix * s_Data.QuadVertexPositions[2];
		    s_Data.QuadVertexBufferPtr->Color = color;
		    s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
    		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
    		s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
    		s_Data.QuadVertexBufferPtr->EntityID = entityID;
		    s_Data.QuadVertexBufferPtr++;

    		s_Data.QuadVertexBufferPtr->Position = tmatrix * s_Data.QuadVertexPositions[3];
    		s_Data.QuadVertexBufferPtr->Color = color;
    		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
    		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
    		s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
    		s_Data.QuadVertexBufferPtr->EntityID = entityID;
    		s_Data.QuadVertexBufferPtr++;

	    	s_Data.QuadIndexCount += 6;

            s_Data.Stats.QuadCount++;
        }
        void Renderer2D::DrawSprite(const glm::mat4& transform, ECS::SpriteRendererComponent& src, int entityID)
        {
            Render::Renderer2D::DrawQuad(transform, {0,0,0}, src.Color,
                {1,1}, {0,0,0}, src.Texture, 1.0f, entityID);
      
        }

        void Renderer2D::Flush()
        {
            // Bind all textures
            for(uint32_t i=0; i<s_Data.TextureSlotIndex; i++)
            {
                s_Data.TextureSlots[i]->Bind(i);
            }
            RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
            s_Data.Stats.DrawCalls++;
        }

        void Renderer2D::ResetStats()
        {
            memset(&s_Data.Stats, 0, sizeof(Statistics));
        }
        Statistics Renderer2D::GetStats()
        {
            return s_Data.Stats;
        }
        void Renderer2D::FlushAndReset()
        {
            EndScene();
            s_Data.QuadIndexCount = 0;
            s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

            s_Data.TextureSlotIndex = 1;
        }

    } // namespace Render
    
} // namespace VersaMachina
