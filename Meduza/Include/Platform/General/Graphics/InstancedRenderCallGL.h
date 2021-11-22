#pragma once
#include "Platform/General/Graphics/BaseInstanced.h"

#include "Platform/General/MeshLibrary.h"
#include "Platform/General/Resources/Mesh.h"
#include "Platform/General/TextureLibrary.h"
#include "Platform/General/Resources/Texture.h"
#include "Platform/General/ShaderLibrary.h"
#include "Platform/General/Resources/Shader.h"

namespace Me
{
    namespace Renderer
    {
        namespace GL
        {
            constexpr unsigned int MAX_TEXTURES = 3;

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

                    auto mesh = static_cast<Resources::GL::Mesh*>(Resources::MeshLibrary::GetMesh(m_meshIndex));
                    glBindVertexArray(mesh->GetVAO());
                    glBindBuffer(GL_ARRAY_BUFFER, m_ibo);
                    //ModelMat
                    glVertexAttribPointer(3, 4, GL_FLOAT, false, sizeof(InstancedData), (void*)(sizeof(float) * 0));
                    glVertexAttribPointer(4, 4, GL_FLOAT, false, sizeof(InstancedData), (void*)(sizeof(float) * 4));
                    glVertexAttribPointer(5, 4, GL_FLOAT, false, sizeof(InstancedData), (void*)(sizeof(float) * 8));
                    glVertexAttribPointer(6, 4, GL_FLOAT, false, sizeof(InstancedData), (void*)(sizeof(float) * 12));
                    //Colour
                    glVertexAttribPointer(7, 4, GL_FLOAT, false, sizeof(InstancedData), (void*)(sizeof(float) * 16));
                    //UV
                    glVertexAttribPointer(8, 4, GL_FLOAT, false, sizeof(InstancedData), (void*)(sizeof(float) * 20));
                    //textureID
                    glVertexAttribPointer(9, 1, GL_INT, false, sizeof(InstancedData), (void*)(sizeof(float) * 24));

                    glBindBuffer(GL_ARRAY_BUFFER, 0);

                    glEnableVertexAttribArray(3);
                    glEnableVertexAttribArray(4);
                    glEnableVertexAttribArray(5);
                    glEnableVertexAttribArray(6);
                    glEnableVertexAttribArray(7);
                    glEnableVertexAttribArray(8);
                    glEnableVertexAttribArray(9);

                    // sent these attributes only once per instance to the program:
                    glVertexAttribDivisor(3, 1);
                    glVertexAttribDivisor(4, 1);
                    glVertexAttribDivisor(5, 1);
                    glVertexAttribDivisor(6, 1);
                    glVertexAttribDivisor(7, 1);
                    glVertexAttribDivisor(8, 1);
                    glVertexAttribDivisor(9, 1);

                    glBindVertexArray(0);

                    glBindBuffer(GL_UNIFORM_BUFFER, m_ibo);
                    glBufferData(GL_UNIFORM_BUFFER, sizeof(InstancedData) * MAX_INSTANCES, NULL, GL_DYNAMIC_DRAW);
                    glBindBuffer(GL_UNIFORM_BUFFER, 0);

                }
                ~InstancedRenderCall()
                {
                    glDeleteBuffers(1, &m_ibo);
                    m_instancedData.clear();
                }

                int Draw(bool = false);
                bool AddData(InstancedData);
                int AddTexture(Texture);
                void ClearBuffer() override
                {
                    m_instancedData.clear();
                    m_textures.clear();
                    m_alignmentItem = 0;
                    m_textureAmount = 0;
                }

                Mesh GetMesh() override { return m_meshIndex; }
                Shader GetShader() override { return m_shaderIndex; }

                int Amount() { return m_alignmentItem; }
                bool ReachedMaxSize() override { return (m_alignmentItem >= MAX_INSTANCES); }

            protected:
                unsigned int m_ibo;
                Mesh m_meshIndex;
                Shader m_shaderIndex;
                std::map<Texture, unsigned int> m_textures;

                unsigned int m_alignmentItem = 0;
                unsigned int m_textureAmount = 0;


                std::vector<InstancedData> m_instancedData;
            };

            template<typename InstancedData>
            int InstancedRenderCall<InstancedData>::Draw(bool a_debug)
            {
                auto mesh = static_cast<Resources::GL::Mesh*>(Resources::MeshLibrary::GetMesh(m_meshIndex));

                for (auto t : m_textures)
                {
                    static_cast<Resources::GL::Texture*>(Resources::TextureLibrary::GetTexture(t.first))->Bind(t.second);
                    if (!a_debug && m_meshIndex == (Mesh)Primitives::Quad)
                    {
                        glDisable(GL_CULL_FACE);
                    }
                }

                // upload instance buffer data:
                glBindBuffer(GL_UNIFORM_BUFFER, m_ibo);
                glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(InstancedData)* m_alignmentItem, m_instancedData.data());
                glBindBuffer(GL_UNIFORM_BUFFER, 0);

                glBindVertexArray(mesh->GetVAO());

                // render objects in scene
                glDrawElementsInstanced(GL_TRIANGLES, mesh->GetIndices().size(), GL_UNSIGNED_SHORT, 0, m_alignmentItem);

                for (auto t : m_textures)
                {
                    static_cast<Resources::GL::Texture*>(Resources::TextureLibrary::GetTexture(t.first))->UnBind(t.second);
                }

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

                m_instancedData.push_back(a_data);
                m_alignmentItem++;


                return true;
            }

            template<typename InstancedData>
            int InstancedRenderCall<InstancedData>::AddTexture(Texture a_texture)
            {
                if (a_texture == 0)
                    return -9999; // Un textured..

                if (m_textures.find(a_texture) != m_textures.end()) 
                {
                    return m_textures.at(a_texture);
                }

                if (m_textureAmount >= MAX_TEXTURES)
                {
                    return -1;
                }

                m_textures[a_texture] = m_textureAmount;
                m_textureAmount++;

                return m_textures[a_texture];
            }
        }
    }
}