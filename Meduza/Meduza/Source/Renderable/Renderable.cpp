#include "mePch.h"
#include "Renderable/Renderable.h"

#include "Meduza/Transform.h"
#include "Platform/General/Resources/Mesh.h"

meduza::Renderable::Renderable()
{
	m_transform = Transform();
}

meduza::Renderable::~Renderable()
{
	if (m_mesh != nullptr)
	{
		delete m_mesh;
	}
}

void meduza::Renderable::SetMesh(Mesh& a_mesh)
{
	m_mesh = &a_mesh;
}

void meduza::Renderable::SetMaterial(Material& a_material)
{
	m_material = &a_material;
}

void meduza::Renderable::Reload()
{

}
