#pragma once
#include "Platform/General/Graphics/RenderLayer.h"

namespace Me 
{
    class WindowsWindow;

    namespace Resources
    {
        class MeshBase;

        namespace Dx12
        {
            class Shader;
            class Texture;
        }
    }

    namespace Helper
    {
        namespace Dx12
        {
            class TextureLoader;
        }
    }

    namespace Renderer
    {
        class BaseInstanced;

        namespace Dx12
        {
            enum class CommandListType
            {
                Default = 0,
                Editor = 1
            };

            class RenderLayerDx12 : public RenderLayer
            {
                public:
                RenderLayerDx12(Me::Window* a_window);
                virtual ~RenderLayerDx12();

                void Clear(Colour const a_clearColour) override;
                void Populate() override;
                void Present() override;
                void Submit(RenderComponent const& a_renderComponent, TransformComponent& a_transformComponent) override;
                void DebugSubmit(DebugRenderComponent const& a_debugRenderComponent, TransformComponent& a_transformComponent) override;
                void RenderLine(LineRender const& a_lineRender) override;
                void RenderCircle(CircleRender const& a_circleRender)  override;
                void SetCamera(CameraComponent const& a_cameraComponent, TransformComponent& a_transformComponent) override;
                
                Resources::MeshBase* CreateMesh(std::vector<Vertex> const& a_vertices, std::vector<uint16_t> const& a_indices);
                Resources::Dx12::Texture* LoadTexture(std::string const& a_file);
                Resources::Dx12::Texture* LoadTexture(std::vector<unsigned char> const& a_texture, int const a_width, int const a_height);
                Helper::Dx12::TextureLoader* GetTextureLoader() { return m_textureLoader; }

                Window* GetWindow() override;

                private:

                WindowsWindow* m_window = nullptr;

                Helper::Dx12::TextureLoader* m_textureLoader = nullptr;
            };
        }
    }
}