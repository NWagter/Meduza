#include "MePCH.h"

#include "Platform/General/Editor/EditorScriptConfig.h"

#include "Core/Scripting/ScriptComponentHelper.h"
#include "Core/Scripting/ScriptConfig.h"

#include "Platform/General/ResourceLibrary.h"
#include "Platform/General/Resources/Script.h"

Me::Editor::EditorScriptConfig::EditorScriptConfig()
{
}

Me::Editor::EditorScriptConfig::~EditorScriptConfig()
{
}

void Me::Editor::EditorScriptConfig::Update(float a_dt)
{

}

void Me::Editor::EditorScriptConfig::Draw()
{
	Resources::ResourceLibrary* rLibrary = Resources::ResourceLibrary::GetInstance();
	const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_AllowItemOverlap;

	if (ImGui::Begin("Script Configurator"))
	{
		for (auto s : Scripting::ScriptConfig::GetScriptConfig()->GetConfigData())
		{
			auto script = rLibrary->GetResource<Resources::Script>(s.second->m_resourceId);

			if (script == nullptr)
			{
				continue;
			}

			if (ImGui::TreeNodeEx(script->GetFileName().c_str(), treeNodeFlags))
			{
				if (ImGui::Button("+"))
				{
					Scripting::ScriptConfig::GetScriptConfig()->AddValue(s.first);
				}
				ImGui::SameLine();
				if (ImGui::Button("Change Config"))
				{
					Scripting::ScriptConfig::GetScriptConfig()->OnChange(s.second->m_resourceId);
				}

				int input = 0;
				std::vector<int> toDelete;
				for (auto v : s.second->m_inputValues)
				{

					ImGui::Text("ArgumentName : %s", v->m_argumentName.c_str());
					ImGui::SameLine();
					std::string removeButton = "X ##" + v->m_argumentName;
					if (ImGui::Button(removeButton.c_str()))
					{
						toDelete.push_back(input);
					}
					// Change Type
					const char* valueTypes[] = { "Unkown", "Number", "String", "Bool", "Vector3"};
					const char* currentType = valueTypes[int(v->m_type)];

					std::string idInputName = "InputName ##" + v->m_argumentName;
					char buffer[256];
					strncpy(buffer, v->m_argumentName.c_str(), sizeof(buffer) - 1);
					ImGui::InputText(idInputName.c_str(), buffer, 256);
					if (buffer != "")
					{
						v->m_argumentName = buffer;
					}

					std::string idType = "Type ##" + v->m_argumentName;
					if (ImGui::BeginCombo(idType.c_str(), currentType))
					{
						for (size_t t = 1; t < (size_t)Scripting::ValueType::Last; t++)
						{
							bool isSelected = currentType == valueTypes[t];

							if (ImGui::Selectable(valueTypes[t], isSelected))
							{
								currentType = valueTypes[t];
								auto newValue = Scripting::ScriptConfig::GetScriptConfig()->ChangeType(s.second, input, (Scripting::ValueType)t);
								s.second->m_inputValues.at(input) = newValue;
							}

							if (isSelected)
							{
								ImGui::SetItemDefaultFocus();
							}
						}

						ImGui::EndCombo();
					}
					input++;
				}
				
				for (auto d : toDelete)
				{
					delete s.second->m_inputValues.at(d);
					s.second->m_inputValues.erase(s.second->m_inputValues.begin() + d);
				}
				ImGui::TreePop();
			}
		}
	}

	ImGui::End();
}
