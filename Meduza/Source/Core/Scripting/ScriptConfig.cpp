#include "MePCH.h"

#include "Core/Scripting/ScriptConfig.h"
#include "Core/Scripting/ScriptComponentHelper.h"

#include "Platform/General/ResourceLibrary.h"
#include "Platform/General/Resources/Script.h"
#include "Platform/General/FileSystem/FileSystem.h"

#include "ECS/EntityManager.h"
#include "Core/Scripting/ScriptComponent.h"

#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/FileSystem/FileSystem.h"
#endif // PLATFORM_WINDOWS


std::string const gc_projectName = "#ProjectName";
std::string const gc_scriptConfigured = "#ScriptsConfigured";

Me::Scripting::ScriptConfig* Me::Scripting::ScriptConfig::ms_instance = nullptr;

Me::Scripting::ScriptConfig::ScriptConfig()
{
	ms_instance = this;
}

Me::Scripting::ScriptConfig::~ScriptConfig()
{
	ms_instance = nullptr;
}

Me::Scripting::ScriptConfig* Me::Scripting::ScriptConfig::CreateScriptConfig()
{
	if (ms_instance != nullptr)
	{
		ME_CORE_ASSERT_M(true, "Can't have multiple instanced of the ScriptConfigurators!")
	}

	return new ScriptConfig();
}


bool Me::Scripting::ScriptConfig::InitializeScriptConfig(std::string const& a_path, std::string const& a_projectName)
{
	if (a_path.empty() || a_projectName.empty())
	{
		return false;
	}
	Clear();
	m_scriptPath = a_path;
	m_projectName = a_projectName;

	std::ofstream scriptFile(a_path.c_str());
	cereal::XMLOutputArchive archiveScript(scriptFile);

	archiveScript.setNextName("Script");
	archiveScript.startNode();

	archiveScript(cereal::make_nvp(gc_scriptConfigured, 0));

	archiveScript.finishNode();

	return true;
}

bool Me::Scripting::ScriptConfig::LoadScriptConfig(std::string const& a_path, std::string const& a_projectName, std::string const& a_assetPath)
{
	if (a_path.empty() || a_projectName.empty())
	{
		return false;
	}

	Clear();
	m_scriptPath = a_path;

	m_projectName = a_projectName;

	std::ifstream is(a_path.c_str());
	is.open(a_path);

	if (!is.is_open())
	{
		ME_LOG("Can't Open File! \n");
	}

	cereal::XMLInputArchive archive(is);

	archive.setNextName("Script");
	archive.startNode();

	int amount;
	archive(cereal::make_nvp(gc_scriptConfigured, amount));

	for (int i = 0; i < amount; i++)
	{
		archive.startNode();

		ScriptConfigData* scriptData = new ScriptConfigData();

		std::string script = "Script" + std::to_string(i);
		archive(cereal::make_nvp(script.c_str(), scriptData->m_resourceId));
		archive(cereal::make_nvp("ScriptPath", scriptData->m_scriptPath));

		int values;
		archive(cereal::make_nvp("#AmountOfValues", values));
		for (int j = 0; j < values; j++)
		{
			archive.startNode();
			std::string argument;
			int type;
			archive(cereal::make_nvp("Argument", argument));
			archive(cereal::make_nvp("Type", type));

			switch (static_cast<ValueType>(type))
			{
			case ValueType::Boolean:
			{
				ValueBool* value = new ValueBool(argument);
				archive(cereal::make_nvp("DefaultValue", value->m_defaultValue));
				scriptData->m_inputValues.push_back(value);
			}
				break;
			case ValueType::Number:
			{
				ValueNumber* value = new ValueNumber(argument);
				archive(cereal::make_nvp("DefaultValue", value->m_defaultValue));
				scriptData->m_inputValues.push_back(value);
			}
				break;
			case ValueType::String:
			{
				ValueString* value = new ValueString(argument);
				archive(cereal::make_nvp("DefaultValue", value->m_defaultValue));
				scriptData->m_inputValues.push_back(value);
			}
				break;
			}
			archive.finishNode();
		}

		m_config[scriptData->m_resourceId] = scriptData;

		archive.finishNode();
	}

	archive.finishNode();


	auto rLibrary = Resources::ResourceLibrary::GetInstance();
	bool noPath = false;
	for (auto c : m_config)
	{
		if (c.second->m_scriptPath.empty())
		{
			noPath = true;
			continue;
		}
		rLibrary->LoadResource<Resources::Script>(c.second->m_scriptPath);
	}

#ifdef PLATFORM_WINDOWS
	Files::BrowseData scripts = Files::BrowseData();
	Files::Windows::FileSystem::GetFilesOfType(scripts, Files::FileType::Script, true, a_assetPath);

	if (noPath || scripts.m_files.size() != m_config.size())
	{
		for (auto f : scripts.m_files)
		{
			rLibrary->LoadResource<Resources::Script>(f->m_path);
		}
	}
#endif

	return true;
}

void Me::Scripting::ScriptConfig::AddScript(Me::Resources::Script& a_script)
{
	if (m_config[a_script.GetID()] != nullptr)
	{
		if (m_config[a_script.GetID()]->m_scriptPath.empty())
		{
			m_config[a_script.GetID()]->m_scriptPath = a_script.GetPath();
			SerializeScriptData();

		}

		return;
	}


	ScriptConfigData* data = new ScriptConfigData();
	data->m_resourceId = a_script.GetID();
	data->m_scriptPath = a_script.GetPath();

	m_config[a_script.GetID()] = data;

	SerializeScriptData();
}

void Me::Scripting::ScriptConfig::AddValue(Resource const a_resource)
{
	if (m_config[a_resource] == nullptr)
	{
		return;
	}

	m_config[a_resource]->m_inputValues.push_back(new ValueNumber("NewValue"));
}

void Me::Scripting::ScriptConfig::OnChange(Resource const a_resource)
{
	SerializeScriptData();

	auto comps = EntityManager::GetEntityManager()->GetComponents<ScriptComponent>();

	for (auto s : comps)
	{
		for (auto script : s.second->m_scripts)
		{
			if (script->m_scriptID == a_resource)
			{
				script->SetInputField(*m_config[a_resource]);
			}
		}
	}
}

Me::Scripting::Value* Me::Scripting::ScriptConfig::ChangeType(ScriptConfigData* a_dataSet, int a_index, ValueType a_newType)
{
	auto inputField = a_dataSet->m_inputValues.at(a_index);
	std::string name = inputField->m_argumentName;
	if (inputField->m_type == a_newType)
	{
		return inputField;
	}

	delete inputField;

	switch (a_newType)
	{
	case ValueType::Boolean:
		return new ValueBool(name);
		break;
	case ValueType::Number:
		return new ValueNumber(name);
		break;
	case ValueType::String:
		return new ValueString(name);
		break;
	}

	return nullptr;
}

void Me::Scripting::ScriptConfig::SerializeScriptData()
{
	std::ofstream scriptFile(m_scriptPath.c_str());
	cereal::XMLOutputArchive archiveScript(scriptFile);

	archiveScript.setNextName("Script");
	archiveScript.startNode();

	archiveScript(cereal::make_nvp(gc_projectName, m_projectName));
	archiveScript(cereal::make_nvp(gc_scriptConfigured, m_config.size()));

	int i = 0;
	for (auto c : m_config)
	{
		archiveScript.startNode();

		std::string script = "Script" + std::to_string(i);
		archiveScript(cereal::make_nvp(script.c_str(), c.second->m_resourceId));
		archiveScript(cereal::make_nvp("ScriptPath", c.second->m_scriptPath));
		archiveScript(cereal::make_nvp("#AmountOfValues", c.second->m_inputValues.size()));

		for (auto value : c.second->m_inputValues)
		{
			archiveScript.startNode();
			archiveScript(cereal::make_nvp("Argument", value->m_argumentName));
			archiveScript(cereal::make_nvp("Type", static_cast<int>(value->m_type)));

			switch (value->m_type)
			{
			case ValueType::Boolean:
				archiveScript(cereal::make_nvp("DefaultValue", static_cast<ValueBool*>(value)->m_defaultValue));
					break;
			case ValueType::Number:
				archiveScript(cereal::make_nvp("DefaultValue", static_cast<ValueNumber*>(value)->m_defaultValue));
				break;
			case ValueType::String:
				archiveScript(cereal::make_nvp("DefaultValue", static_cast<ValueString*>(value)->m_defaultValue));
				break;
			}

			archiveScript.finishNode();
		}

		archiveScript.finishNode();
		i++;
	}

	archiveScript.finishNode();
}

void Me::Scripting::ScriptConfig::Clear()
{
	for (auto c : m_config)
	{
		delete c.second;
	}

	m_config.clear();
}