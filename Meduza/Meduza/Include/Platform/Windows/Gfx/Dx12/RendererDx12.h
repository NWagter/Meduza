#pragma once

#include "Platform/General/Gfx/Renderer.h"
#include "Math/MeduzaMath.h"

namespace meduza
{
	namespace renderer
	{
		class Context;
		class ContextDx12;
		class CommandListDx12;
		class DescriptorDx12;

		class RendererDx12 : public Renderer
		{
		public:
			RendererDx12(Context&);
			~RendererDx12() override;

			void Clear(Colour) override;
			void Render(const Camera&) override;

			void Submit(Renderable&) override;
			void Submit(Scene&) override;

			ContextDx12& GetContext() const;
			CommandListDx12& GetCmd(int = 0) const;

			DrawStatistics GetDrawStatistics() const override;

			static RendererDx12* GetRenderer();

		private:
			static RendererDx12* ms_renderer;
			void PreRender();
			void PopulateBuffers();

			ContextDx12* m_context;

			std::vector<CommandListDx12*> m_cmdList;
			DescriptorDx12* m_rtv;
			DescriptorDx12* m_srv;
			DrawStatistics m_stats;
		};
	}
}