#include "mePch.h"
#include "Scene/Scene.h"

#include "Renderable/Renderable.h"

void meduza::Scene::Destroy()
{
	for (auto r : m_renderables)
	{
		delete r;
	}
}
