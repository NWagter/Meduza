#include "mePch.h"
#include "Scene/Scene.h"

#include "Renderable/Renderable.h"

void meduza::Scene::Reload()
{
	for (auto r : m_renderables)
	{
		r->Reload();
	}
}

void meduza::Scene::Destroy()
{
	for (auto r : m_renderables)
	{
		delete r;
	}
}
