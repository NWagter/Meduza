#include "MePCH.h"
#include "Platform/General/Resources/Script.h"

Me::Resources::Script::Script() : ResourceBase(ResourceType::Script)
{

}

Me::Resources::Script::~Script()
{

}

Me::Resources::Script* Me::Resources::Script::OnCreate(std::string const& a_path)
{
	return new Script();
}