#pragma once

namespace meduza
{
	class Renderable;

	class Scene
	{
	public:

		inline void Submit(Renderable& a_renderable)
		{
			m_renderables.push_back(&a_renderable);
		}

		inline std::vector<Renderable*> GetRenderables() const { return m_renderables; }

		void Reload();
		void Destroy();

	private:
		std::vector<Renderable*> m_renderables;
	};
}