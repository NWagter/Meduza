#include "MePCH.h"
#include "Platform/General/Resources/Scene.h"

Me::Resources::Scene::Scene() : ResourceBase(ResourceType::Scene)
{

}

Me::Resources::Scene::~Scene()
{

}

Me::Resources::Scene* Me::Resources::Scene::OnCreate(std::string const& a_path)
{
	return new Scene();
}