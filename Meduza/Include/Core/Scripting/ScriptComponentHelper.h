#pragma once

namespace Me
{
    namespace Scripting
    {
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
            float m_value = 0;

            ValueNumber(std::string const& a_argumentName) : Value(a_argumentName, ValueType::Number)
            {
                m_value = 0;
            }
        };        
        
        struct ValueBool : public Value
        {
            bool m_value = true;

            ValueBool(std::string const& a_argumentName) : Value(a_argumentName, ValueType::Boolean)
            {
                m_value = true;
            }
        };        
        
        struct ValueString : public Value
        {
            std::string m_value;

            ValueString(std::string const& a_argumentName) : Value(a_argumentName, ValueType::String)
            {
                m_value = "";
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
                m_luaState = nullptr;
            }

            ~Script()
            {
                for (auto value : m_inputFields)
                {
                    delete value;
                }
                m_inputFields.clear();
            }
        
            void AddInputField()
            {
                std::string name = "InputName" + std::to_string(m_inputFields.size());
                m_inputFields.push_back(new ValueString(name));
            }

            Value* ChangeType(size_t a_id, ValueType a_type)
            {
                auto inputField = m_inputFields.at(a_id);
                std::string name = inputField->m_argumentName;
                if (inputField->m_type == a_type)
                {
                    return m_inputFields.at(a_id);
                }

                delete inputField;
                
                switch (a_type)
                {
                case ValueType::Boolean:
                    m_inputFields.at(a_id) = new ValueBool(name);
                    break;
                case ValueType::Number:
                    m_inputFields.at(a_id) = new ValueNumber(name);
                    break;
                case ValueType::String:
                    m_inputFields.at(a_id) = new ValueString(name);
                    break;
                }

                return m_inputFields.at(a_id);
            }

            void RemoveInputField(size_t a_id)
            {
                auto inputField = m_inputFields.at(a_id);
                delete inputField;
                m_inputFields.erase(m_inputFields.begin() + a_id);
            }
        };

    }
}