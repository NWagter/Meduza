#pragma once

#include "Meduza/Transform.h"

namespace meduza
{
	class Mesh;
	class Material;

	class Renderable
	{
	public:
		Renderable();
		virtual ~Renderable();

		inline Transform& GetTransform() { return m_transform; }
		inline Mesh& GetMesh() { return *m_mesh; }
		inline Material& GetMaterial() { return *m_material; }

		virtual void SetMesh(Mesh&);
		void SetMaterial(Material&);

		virtual void Reload();
	protected:
		Transform m_transform;
		Mesh* m_mesh = nullptr;
		Material* m_material = nullptr;
	};
}