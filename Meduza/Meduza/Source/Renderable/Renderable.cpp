#include "mePch.h"
#include "Renderable/Renderable.h"

#include "Meduza/Transform.h"

meduza::Renderable::Renderable()
{
	m_transform = Transform();
}

meduza::Renderable::~Renderable()
{
}

void meduza::Renderable::SetMesh(Mesh& a_mesh)
{
	m_mesh = &a_mesh;
}

void meduza::Renderable::SetMaterial(Material& a_material)
{
	m_material = &a_material;
}
