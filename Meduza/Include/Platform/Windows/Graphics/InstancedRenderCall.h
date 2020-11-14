#pragma once

#include "Platform/Windows/Helper/BufferStructures.h"
#include "Platform/Windows/Graphics/CommandList.h"

#include "Platform/General/MeshLibrary.h"

namespace Me
{
    namespace Renderer
    {
        namespace Dx12
        {

            constexpr unsigned int MAX_INSTANCES = 128;

            class BaseInstanced
            {
            public:
                ~BaseInstanced() = default;

                virtual void Draw(CommandList*) = 0;
                virtual void ClearBuffer() = 0;

                virtual Shader GetShader() = 0;
                virtual Mesh GetMesh() = 0;
            };
            
            template<typename InstancedData>
            class InstancedRenderCall : public BaseInstanced
            {
            public:
                InstancedRenderCall(Mesh& a_mesh, Shader& a_shader, Device* a_device)
                {
                    m_meshIndex = a_mesh;
                    m_shaderIndex = a_shader;

                    m_alignmentItem = 0;
                    m_instancedBuffer = new Helper::Dx12::UploadBuffer<InstancedData>(*a_device, false);
                    m_instancedBuffer->SetElementCount(*a_device, MAX_INSTANCES, false);
                }
                ~InstancedRenderCall()
                {
                    delete m_instancedBuffer;
                    m_instancedData.clear();
                }

                void Draw(CommandList*) override;
                bool AddData(InstancedData);
                void ClearBuffer() override
                {
                    m_instancedData.clear();
                    m_alignmentItem = 0;
                }

                
                Shader GetShader() override { return m_shaderIndex;}
                Mesh GetMesh() override { return m_meshIndex;}
            protected:
                Mesh m_meshIndex;
                Shader m_shaderIndex;

                std::vector<InstancedData> m_instancedData;

                unsigned int m_alignmentItem = 0;
                Helper::Dx12::UploadBuffer<InstancedData>* m_instancedBuffer;
            };

            template<typename InstancedData>
            void InstancedRenderCall<InstancedData>::Draw(CommandList* a_cmd)
            {
                auto m = static_cast<Resources::Dx12::Mesh*>(Resources::MeshLibrary::GetMesh(m_meshIndex));
                a_cmd->Draw(m, m_instancedBuffer->GetResource().Get() ,m_alignmentItem);
            }

            template<typename InstancedData>
            bool InstancedRenderCall<InstancedData>::AddData(InstancedData a_data)
            {
                if(m_alignmentItem >= MAX_INSTANCES)
                {
                    return false;
                }

                int item = m_alignmentItem;
                m_instancedData.push_back(a_data);

                int alignmentSize = (m_instancedBuffer->GetBufferAlignment() * item++);
			    m_instancedBuffer->CopyData(alignmentSize, m_instancedData.at(m_alignmentItem));

                m_alignmentItem = item;

                return true;
            }
        }
    }
}