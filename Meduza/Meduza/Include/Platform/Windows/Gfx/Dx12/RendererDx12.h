#pragma once

#include "Platform/General/Renderer.h"
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
			void SwapBuffers() override;

			void Draw(drawable::Drawable*) override;
			void Submit(std::vector<drawable::Drawable*>) override;

			void EnableOptick() override;
		private:
			void PreRender();
			void PopulateBuffers();

			ContextDx12* m_context;

			CommandListDx12* m_cmdList;
			DescriptorDx12* m_rtv;
			DescriptorDx12* m_srv;
		};
	}
}