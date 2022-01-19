#include "MePCH.h"
#include "Platform/General/Resources/Script.h"

#include "Core/Scripting/ScriptComponentHelper.h"
#include "Core/Scripting/ScriptConfig.h"

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

void Me::Resources::Script::AddInputField(Scripting::Value* a_input)
{
	m_inputFields.push_back(a_input);
}

void Me::Resources::Script::OnInit()
{
	Scripting::ScriptConfig::GetScriptConfig()->AddScript(*this);
}