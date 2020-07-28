#pragma once

#include "Platform/General/Gfx/Renderer.h"
#include "Math/MeduzaMath.h"

#include "UploadBufferDx12.h"

namespace meduza
{
	class ShaderDx12;

	namespace renderer
	{
		struct ConstBuffer
		{
			ConstBuffer() = default;

			DirectX::XMFLOAT4X4 m_viewProjection = DirectX::XMFLOAT4X4(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);

			DirectX::XMFLOAT3 m_position = { 0,0,0 };
			DirectX::XMFLOAT3 m_scale = { 1,1,1 };
		};

		class Context;
		class ContextDx12;
		class CommandListDx12;
		class DescriptorDx12;
		class DepthStencilDx12;

		class RendererDx12 : public Renderer
		{
		public:
			RendererDx12(Context&);
			~RendererDx12() override;

			void Clear(Colour) override;
			void Render(const Camera&) override;
			void Resize(math::Vec2);

			void Submit(Renderable&) override;
			void Submit(Scene&) override;

			ContextDx12& GetContext() const;
			CommandListDx12& GetCmd(int = 0) const;

			DrawStatistics GetDrawStatistics() const override;

			static RendererDx12* GetRenderer();

		private:
			static RendererDx12* ms_renderer;
			void PreRender();
			void PopulateBuffers(const Camera&);

			ContextDx12* m_context;

			std::vector<CommandListDx12*> m_cmdList;
			DepthStencilDx12* m_dsBuffer;
			DescriptorDx12* m_rtv;
			DescriptorDx12* m_srv;
			DrawStatistics m_stats;

			std::vector<Renderable*> m_renderables;
			ShaderDx12* m_lastShader = nullptr;
		};
	}
}