#pragma once

#include "Renderable.h"

namespace meduza
{
	class Renderable2D : public Renderable 
	{
	public:
		Renderable2D();
		Renderable2D(float);
		~Renderable2D();

		void SetMesh(Mesh&) override;
		void SetUnitsPerPixel(float);

	private:
		void CreateQuad();

		float m_pixelsPerUnit = 32;
	};

}