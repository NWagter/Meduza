#pragma once

namespace Me
{

    enum class ValueType
    {
        Unkown = 0,
        Number,
        String,
        Boolean,
        Vector3,
        Entity,
        Asset,

        Last
    };

    struct Value
    {
        ValueType m_type;
        std::string m_argumentName;

        Value(Value const& a_value)
        {
            m_type = a_value.m_type;
            m_argumentName = a_value.m_argumentName;
        }

        Value(std::string const& a_argumentName, ValueType const a_type)
        {
            m_type = a_type;
            m_argumentName = a_argumentName;
        }

        virtual void Reset() = 0;
    };

    struct ValueNumber : public Value
    {
        float m_value;
        float m_defaultValue = 0.0f;

        ValueNumber(ValueNumber const& a_value) : Value(a_value)
        {
            m_value = a_value.m_value;
        }

        ValueNumber(std::string const& a_argumentName) : Value(a_argumentName, ValueType::Number)
        {
            Reset();
        }

        ValueNumber(std::string const& a_argumentName, float const a_value) : Value(a_argumentName, ValueType::Number)
        {
            m_value = a_value;
        }

        void Reset() override
        {
            m_value = m_defaultValue;
        }
    };

    struct ValueBool : public Value
    {
        bool m_value;
        bool m_defaultValue = false;

        ValueBool(ValueBool const& a_value) : Value(a_value)
        {
            m_value = a_value.m_value;
        }

        ValueBool(std::string const& a_argumentName) : Value(a_argumentName, ValueType::Boolean)
        {
            Reset();
        }

        ValueBool(std::string const& a_argumentName, bool const a_value) : Value(a_argumentName, ValueType::Boolean)
        {
            m_value = a_value;
        }

        void Reset() override
        {
            m_value = m_defaultValue;
        }
    };

    struct ValueString : public Value
    {
        std::string m_value;
        std::string m_defaultValue = "";

        ValueString(ValueString const& a_value) : Value(a_value)
        {
            m_value = a_value.m_value;
        }

        ValueString(std::string const& a_argumentName) : Value(a_argumentName, ValueType::String)
        {
            Reset();
        }

        ValueString(std::string const& a_argumentName, std::string const& a_value) : Value(a_argumentName, ValueType::String)
        {
            m_value = a_value;
        }

        void Reset() override
        {
            m_value = m_defaultValue;
        }
    };

    struct ValueVector3 : public Value
    {
        Math::Vector3 m_value;
        Math::Vector3 m_defaultValue = Math::Vector3(0);

        ValueVector3(ValueVector3 const& a_value) : Value(a_value)
        {
            m_value = a_value.m_value;
        }

        ValueVector3(std::string const& a_argumentName) : Value(a_argumentName, ValueType::Vector3)
        {
            Reset();
        }

        ValueVector3(std::string const& a_argumentName, Math::Vector3 const a_value) : Value(a_argumentName, ValueType::Vector3)
        {
            m_value = a_value;
        }

        void Reset() override
        {
            m_value = m_defaultValue;
        }
    };

    struct ValueEntity : public Value
    {
        EntityID m_value;
        EntityID m_defaultValue = ENTITY_NULL;

        ValueEntity(ValueEntity const& a_value) : Value(a_value)
        {
            m_value = a_value.m_value;
        }

        ValueEntity(std::string const& a_argumentName) : Value(a_argumentName, ValueType::Entity)
        {
            Reset();
        }

        ValueEntity(std::string const& a_argumentName, EntityID const a_value) : Value(a_argumentName, ValueType::Entity)
        {
            m_value = a_value;
        }

        void Reset() override
        {
            m_value = m_defaultValue;
        }
    };

    struct ValueAsset : public Value
    {
        std::string m_value;
        std::string m_defaultValue = "";

        ValueAsset(ValueAsset const& a_value) : Value(a_value)
        {
            m_value = a_value.m_value;
        }

        ValueAsset(std::string const& a_argumentName) : Value(a_argumentName, ValueType::Asset)
        {
            Reset();
        }

        ValueAsset(std::string const& a_argumentName, std::string const& a_value) : Value(a_argumentName, ValueType::Asset)
        {
            m_value = a_value;
        }

        void Reset() override
        {
            m_value = m_defaultValue;
        }
    };
}