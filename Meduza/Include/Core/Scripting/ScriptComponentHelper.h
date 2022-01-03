#pragma once

namespace Me
{
    namespace Scripting
    {
        enum ValueType : uint8_t
        {
            Unkown = 0,
            Number,
            String,
            Bool,

            Last
        };

        struct Value
        {
            ValueType m_type;
            std::string m_argumentName;
        };

        struct ValueInt : public Value
        {
            int m_value;
        };        
        
        struct ValueBool : public Value
        {
            bool m_value;
        };        
        
        struct ValueString : public Value
        {
            std::string m_value;
        };


        struct Script
        {
            std::string m_script;
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
        };

    }
}