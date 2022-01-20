#pragma once

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

        enum class ValueType
        {
            Unkown = 0,
            Number,
            String,
            Boolean,

            Last
        };

        struct Value
        {
            ValueType m_type;
            std::string m_argumentName;

            Value(std::string const& a_argumentName, ValueType const a_type)
            {
                m_type = a_type;
                m_argumentName = a_argumentName;
            }
        };

        struct ValueNumber : public Value
        {
            float m_value = 0.0f;
            float m_defaultValue;

            ValueNumber(std::string const& a_argumentName) : Value(a_argumentName, ValueType::Number)
            {
                m_value = 0.0f;
            }

            ValueNumber(std::string const& a_argumentName, float const a_value) : Value(a_argumentName, ValueType::Number)
            {
                m_value = a_value;
            }
        };        
        
        struct ValueBool : public Value
        {
            bool m_value = true;
            bool m_defaultValue;

            ValueBool(std::string const& a_argumentName) : Value(a_argumentName, ValueType::Boolean)
            {
                m_value = true;
            }

            ValueBool(std::string const& a_argumentName, bool const a_value) : Value(a_argumentName, ValueType::Boolean)
            {
                m_value = a_value;
            }
        };        
        
        struct ValueString : public Value
        {
            std::string m_value;
            std::string m_defaultValue;

            ValueString(std::string const& a_argumentName) : Value(a_argumentName, ValueType::String)
            {
                m_value = "";
            }

            ValueString(std::string const& a_argumentName, std::string const& a_value) : Value(a_argumentName, ValueType::String)
            {
                m_value = a_value;
            }
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
                }

                return nullptr;
            }
        };

    }
}