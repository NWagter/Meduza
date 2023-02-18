#pragma once
#include "Platform/General/Graphics/BaseInstanced.h"

#include "Platform/General/Resources/Texture.h"
#include "Platform/General/Resources/Shader.h"
#include "Platform/General/Resources/Mesh.h"
#include "Platform/General/ResourceLibrary.h"

namespace Me
{
    namespace Renderer
    {
        namespace GL
        {
            constexpr unsigned int MAX_TEXTURES = 8;

            template<typename InstancedData>
            class InstancedRenderCall : public BaseInstanced
            {
            public:
                InstancedRenderCall(Mesh const& a_mesh, Shader const& a_shader)
                {
                    m_meshIndex = a_mesh;
                    m_shaderIndex = a_shader;

                    m_alignmentItem = 0;
                    m_textureAmount = 0;
                }
                ~InstancedRenderCall()
                {
                    m_instancedData.clear();
                    m_textures.clear();
                }

                int Draw(Math::Matrix4 const& a_cameraMatrix, bool const a_debugMode = false);
                bool AddData(InstancedData const& a_instanceData);
                int AddTexture(Texture const& a_texture);
                void ClearBuffer() override
                {
                    m_instancedData.clear(); 
                    m_instancedData.reserve(MAX_INSTANCES);
                    m_alignmentItem = 0;
                }

                Mesh GetMesh() override { return m_meshIndex; }
                Shader GetShader() override { return m_shaderIndex; }

                int Amount() override { return m_alignmentItem; }
                bool ReachedMaxSize() override { return (m_alignmentItem >= MAX_INSTANCES); }
                bool Empty() override { return m_alignmentItem == 0; }
            private:
                void CreateInstancedBuffer();
            protected:
                Mesh m_meshIndex;
                Shader m_shaderIndex;
                std::vector<Texture> m_textures;

                unsigned int m_alignmentItem = 0;
                unsigned int m_textureAmount = 0;
                unsigned int m_instancedVBO = 0;


                std::vector<InstancedData> m_instancedData = std::vector<InstancedData>(MAX_INSTANCES);
            };

            template<typename InstancedData>
            int InstancedRenderCall<InstancedData>::Draw(Math::Matrix4 const& a_cameraMatrix, bool const a_debugMode)
            {
                ME_PROFILE_FUNC("Instanced Draw");
                if (m_alignmentItem <= 0)
                {
                    return 0;
                }

                if (m_instancedVBO == 0)
                {
                    CreateInstancedBuffer();
                }

                auto mesh = static_cast<Resources::GL::Mesh*>(Resources::ResourceLibrary::GetInstance()->GetResource<Resources::MeshBase>(m_meshIndex));
                auto shader = static_cast<Resources::GL::Shader*>(Resources::ResourceLibrary::GetInstance()->GetResource<Resources::ShaderBase>(m_shaderIndex));

                shader->Bind();
                shader->SetMat4("u_projectionView", a_cameraMatrix, false);

                for (size_t i = 0; i < m_textures.size(); i++)
                {
                    static_cast<Resources::GL::Texture*>(Resources::ResourceLibrary::GetInstance()->GetResource<Resources::TextureBase>(m_textures[i]))->Bind(static_cast<int>(i));
                    if (!a_debugMode && m_meshIndex == (Mesh)Primitives::Quad)
                    {
                        glDisable(GL_CULL_FACE);
                    }
                }

                // Upload instanced data
                glBindBuffer(GL_UNIFORM_BUFFER, m_instancedVBO);
                glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(InstancedData) * m_alignmentItem, m_instancedData.data());
                glBindBuffer(GL_UNIFORM_BUFFER, 0);

                glBindVertexArray(mesh->GetVAO());

                // render objects in scene
                glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, mesh->GetVerticesSize(), m_alignmentItem);

                glBindVertexArray(0);

                for (size_t i = 0; i < m_textures.size(); i++)
                {
                    static_cast<Resources::GL::Texture*>(Resources::ResourceLibrary::GetInstance()->GetResource<Resources::TextureBase>(m_textures[i]))->UnBind(static_cast<int>(i));
                }

                shader->UnBind();
                glBindVertexArray(0);
                return mesh->GetVerticesSize();
            }

            template<typename InstancedData>
            bool InstancedRenderCall<InstancedData>::AddData(InstancedData const& a_instanceData)
            {
                if (m_alignmentItem >= MAX_INSTANCES)
                {
                    return false;
                }

                m_instancedData.push_back(a_instanceData);
                m_alignmentItem++;

                return true;
            }

            template<typename InstancedData>
            int InstancedRenderCall<InstancedData>::AddTexture(Texture const& a_texture)
            {
                if (a_texture == 0)
                    return -9999; // Un textured..

                for (size_t i = 0; i < m_textures.size(); i++)
                {
                    if (a_texture == m_textures[i])
                    {
                        return static_cast<int>(i);
                    }
                }

                if (m_textureAmount >= MAX_TEXTURES)
                {
                    return -1;
                }

                m_textures.push_back(a_texture);
                m_textureAmount++;

                return m_textureAmount - 1;
            }

            template<typename InstancedData>
            void InstancedRenderCall<InstancedData>::CreateInstancedBuffer()
            {
                ME_PROFILE_FUNC("Create Instanced Buffer");
                glGenBuffers(1, &m_instancedVBO);
                glBindBuffer(GL_ARRAY_BUFFER, m_instancedVBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(InstancedData), &m_instancedData[0], GL_STREAM_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, 0);

                auto mesh = static_cast<Resources::GL::Mesh*>(Resources::ResourceLibrary::GetInstance()->GetResource<Resources::MeshBase>(m_meshIndex));
                glBindVertexArray(mesh->GetVAO());

                glBindBuffer(GL_ARRAY_BUFFER, m_instancedVBO);

                //ModelMat
                glVertexAttribPointer(3, 4, GL_FLOAT, false, sizeof(InstancedData), (void*)(sizeof(float) * 0));
                glVertexAttribPointer(4, 4, GL_FLOAT, false, sizeof(InstancedData), (void*)(1 * sizeof(Math::Vector4)));
                glVertexAttribPointer(5, 4, GL_FLOAT, false, sizeof(InstancedData), (void*)(2 * sizeof(Math::Vector4)));
                glVertexAttribPointer(6, 4, GL_FLOAT, false, sizeof(InstancedData), (void*)(3 * sizeof(Math::Vector4)));
                //Colour
                glVertexAttribPointer(7, 4, GL_FLOAT, false, sizeof(InstancedData), (void*)(4 * sizeof(Math::Vector4)));
                //UV
                glVertexAttribPointer(8, 4, GL_FLOAT, false, sizeof(InstancedData), (void*)(5 * sizeof(Math::Vector4)));
                //textureID
                glVertexAttribPointer(9, 1, GL_FLOAT, false, sizeof(InstancedData), (void*)(6 * sizeof(Math::Vector4)));

                //ModelMat
                glEnableVertexAttribArray(3);
                glEnableVertexAttribArray(4);
                glEnableVertexAttribArray(5);
                glEnableVertexAttribArray(6);
                //Colour
                glEnableVertexAttribArray(7);
                //UV
                glEnableVertexAttribArray(8);
                //textureID
                glEnableVertexAttribArray(9);

                // sent these attributes only once per instance to the program:
                glVertexAttribDivisor(3, 1);
                glVertexAttribDivisor(4, 1);
                glVertexAttribDivisor(5, 1);
                glVertexAttribDivisor(6, 1);
                glVertexAttribDivisor(7, 1);
                glVertexAttribDivisor(8, 1);
                glVertexAttribDivisor(9, 1);

                glBindBuffer(GL_ARRAY_BUFFER, 0);

                glBindBuffer(GL_UNIFORM_BUFFER, m_instancedVBO);
                glBufferData(GL_UNIFORM_BUFFER, sizeof(InstancedData) * MAX_INSTANCES, NULL, GL_DYNAMIC_DRAW);
                glBindBuffer(GL_UNIFORM_BUFFER, 0);
            }
        }
    }
}