#pragma once
#include "Platform/General/Graphics/BaseInstanced.h"

#include "Platform/General/TextureLibrary.h"
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
                InstancedRenderCall(Mesh& a_mesh, Shader& a_shader)
                {
                    m_meshIndex = a_mesh;
                    m_shaderIndex = a_shader;

                    m_alignmentItem = 0;
                    m_textureAmount = 0;
                }
                ~InstancedRenderCall()
                {
                    ClearBuffer();
                }

                int Draw(Math::Mat4, bool = false);
                bool AddData(InstancedData);
                int AddTexture(Texture);
                void ClearBuffer() override
                {
                    m_instancedData.clear(); 
                    m_instancedData = std::vector<InstancedData>(MAX_INSTANCES);
                    m_textures.clear();
                    m_alignmentItem = 0;
                    m_textureAmount = 0;
                }

                Mesh GetMesh() override { return m_meshIndex; }
                Shader GetShader() override { return m_shaderIndex; }

                int Amount() { return m_alignmentItem; }
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


                std::vector<InstancedData> m_instancedData = std::vector<InstancedData>(MAX_INSTANCES);
            };

            template<typename InstancedData>
            int InstancedRenderCall<InstancedData>::Draw(Math::Mat4 a_camMat, bool a_debug)
            {
                CreateInstancedBuffer();

                auto mesh = static_cast<Resources::GL::Mesh*>(Resources::ResourceLibrary::GetInstance()->GetResource<Resources::MeshBase>(m_meshIndex));
                auto shader = static_cast<Resources::GL::Shader*>(Resources::ResourceLibrary::GetInstance()->GetResource<Resources::ShaderBase>(m_shaderIndex));

                shader->Bind();

                for (size_t i = 0; i < m_textures.size(); i++)
                {
                    static_cast<Resources::GL::Texture*>(Resources::TextureLibrary::GetTexture(m_textures[i]))->Bind(static_cast<int>(i));
                    if (!a_debug && m_meshIndex == (Mesh)Primitives::Quad)
                    {
                        glDisable(GL_CULL_FACE);
                    }
                }

                glBindVertexArray(mesh->GetVAO());

                // render objects in scene
                int indices = mesh->GetIndices().size();

                shader->SetMat4("u_projectionView", a_camMat, false);
                glDrawElementsInstanced(GL_TRIANGLES, mesh->GetIndices().size(), GL_UNSIGNED_SHORT, 0, m_alignmentItem);
                // render objects in scene

                glBindVertexArray(0);

                for (size_t i = 0; i < m_textures.size(); i++)
                {
                    static_cast<Resources::GL::Texture*>(Resources::TextureLibrary::GetTexture(m_textures[i]))->UnBind(static_cast<int>(i));
                }

                shader->UnBind();
                return mesh->GetVerticesSize();
            }

            template<typename InstancedData>
            bool InstancedRenderCall<InstancedData>::AddData(InstancedData a_data)
            {
                if (m_alignmentItem >= MAX_INSTANCES)
                {
                    return false;
                }

                InstancedData data = a_data;

                m_instancedData[m_alignmentItem] = a_data;
                m_alignmentItem++;


                return true;
            }

            template<typename InstancedData>
            int InstancedRenderCall<InstancedData>::AddTexture(Texture a_texture)
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
                auto mesh = static_cast<Resources::GL::Mesh*>(Resources::ResourceLibrary::GetInstance()->GetResource<Resources::MeshBase>(m_meshIndex));

                glBindVertexArray(mesh->GetVAO());

                unsigned int ibo;
                glGenBuffers(1, &ibo);
                glBindBuffer(GL_ARRAY_BUFFER, ibo);
                glBufferData(GL_ARRAY_BUFFER, m_alignmentItem * sizeof(InstancedData), &m_instancedData[0], GL_STATIC_DRAW);

                //ModelMat
                glEnableVertexAttribArray(3);
                glVertexAttribPointer(3, 4, GL_FLOAT, false, sizeof(InstancedData), (void*)(sizeof(float) * 0));
                glEnableVertexAttribArray(4);
                glVertexAttribPointer(4, 4, GL_FLOAT, false, sizeof(InstancedData), (void*)(1 * sizeof(Math::Vec4)));
                glEnableVertexAttribArray(5);
                glVertexAttribPointer(5, 4, GL_FLOAT, false, sizeof(InstancedData), (void*)(2 * sizeof(Math::Vec4)));
                glEnableVertexAttribArray(6);
                glVertexAttribPointer(6, 4, GL_FLOAT, false, sizeof(InstancedData), (void*)(3 * sizeof(Math::Vec4)));
                //Colour
                glEnableVertexAttribArray(7);
                glVertexAttribPointer(7, 4, GL_FLOAT, false, sizeof(InstancedData), (void*)(4 * sizeof(Math::Vec4)));
                //UV
                glEnableVertexAttribArray(8);
                glVertexAttribPointer(8, 4, GL_FLOAT, false, sizeof(InstancedData), (void*)(5 * sizeof(Math::Vec4)));
                //textureID

                glEnableVertexAttribArray(9);
                glVertexAttribPointer(9, 1, GL_FLOAT, false, sizeof(InstancedData), (void*)(6 * sizeof(Math::Vec4)));


                // sent these attributes only once per instance to the program:
                glVertexAttribDivisor(3, 1);
                glVertexAttribDivisor(4, 1);
                glVertexAttribDivisor(5, 1);
                glVertexAttribDivisor(6, 1);
                glVertexAttribDivisor(7, 1);
                glVertexAttribDivisor(8, 1);
                glVertexAttribDivisor(9, 1);

                glBindVertexArray(0);
                glDeleteBuffers(1, &ibo);
            }
        }
    }
}