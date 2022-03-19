#pragma once

#include "Core/ValueContainer.h"
#include "Core/Scripting/ScriptConfig.h"

#include "Platform/General/Resources/Script.h"
#include "Platform/General/ResourceLibrary.h"

namespace Me
{
    namespace Scripting
    {
        struct ScriptConfigData
        {
            Resource m_resourceId;
            std::string m_scriptPath;
            std::vector<Value*> m_inputValues;
        };

        struct Script
        {
            std::string m_script;
            Resource m_scriptID;
            lua_State* m_luaState;
            std::vector<Value*> m_inputFields;

            Script(std::string const& a_script)
            {
                m_script = a_script;
                m_scriptID = Resources::ResourceLibrary::GetInstance()->LoadResource<Resources::Script>(a_script)->GetID();
                m_luaState = nullptr;

                SetInputField(*ScriptConfig::GetScriptConfig()->GetConfigData().at(m_scriptID));
            }

            ~Script()
            {
                for (auto value : m_inputFields)
                {
                    delete value;
                }
                m_inputFields.clear();
            }
        
            void SetInputField(ScriptConfigData const& a_data)
            {
                std::vector<Value*> toDelete;
                std::vector<Value*> toAdd;

                for (auto value : a_data.m_inputValues)
                {
                    toAdd.push_back(value);
                }

                for (auto value : m_inputFields)
                {
                    delete value;
                }
                m_inputFields.clear();

                for (auto a : toAdd)
                {
                    auto v = CreateValue(a);
                    if (v != nullptr)
                    {
                        m_inputFields.push_back(v);
                    }
                }
            }

            void RemoveInputField(size_t a_id)
            {
                auto inputField = m_inputFields.at(a_id);
                delete inputField;
                m_inputFields.erase(m_inputFields.begin() + a_id);
            }

        private:
            Value* CreateValue(Value* a_value)
            {
                switch (a_value->m_type)
                {
                case ValueType::Boolean:
                {
                    auto oldValue = static_cast<ValueBool*>(a_value);
                    auto v = new ValueBool(a_value->m_argumentName, oldValue->m_value);
                    return v;
                }
                    break;
                case ValueType::Number:
                {
                    auto oldValue = static_cast<ValueNumber*>(a_value);
                    auto v = new ValueNumber(a_value->m_argumentName, oldValue->m_value);
                    return v;
                }
                    break;
                case ValueType::String:
                {
                    auto oldValue = static_cast<ValueString*>(a_value);
                    auto v = new ValueString(a_value->m_argumentName, oldValue->m_value);
                    return v;
                }
                    break;
                case ValueType::Vector3:
                {
                    auto oldValue = static_cast<ValueVector3*>(a_value);
                    auto v = new ValueVector3(a_value->m_argumentName, oldValue->m_value);
                    return v;
                }
                    break;
                case ValueType::Entity:
                {
                    auto oldValue = static_cast<ValueEntity*>(a_value);
                    auto v = new ValueEntity(a_value->m_argumentName, oldValue->m_value);
                    return v;
                }
                break;
                }

                return nullptr;
            }
        };

    }
}