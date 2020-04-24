#pragma once

#include <string>

#include "Math/MeduzaMath.h"
#include "MeduzaUtil.h"

namespace meduza
{
	namespace renderer
	{
		class Context;
	}

	class Window
	{
	public:
		Window() = default;
		virtual ~Window() = default;

		virtual void Peek() = 0;
		virtual void SwapBuffers() = 0;

		virtual void SetTitle(std::string) = 0;
		virtual void CreateContext(API) = 0;

		inline renderer::Context* GetContext() { return m_context; }

		inline math::Vec2 GetSize() { return m_size; }
		inline std::string GetTitle() { return m_title; }
		inline bool GetActive() { return m_windowActive; }

	protected:
		renderer::Context* m_context = nullptr;
		math::Vec2 m_size;
		std::string m_title;
		bool m_windowActive;
	};
}
