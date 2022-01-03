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
            std::string m_value;
        };


        struct Script
        {
            std::string m_script;
            lua_State* m_luaState;
            std::vector<Value> m_inputFields;

            Script(std::string const& a_script)
            {
                m_script = a_script;
                m_luaState = nullptr;
                m_inputFields.clear();
            }
        };

    }
}