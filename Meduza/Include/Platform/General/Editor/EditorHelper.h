#pragma once

namespace Me
{
    namespace Editor
    {
        namespace Helper
        {
            struct EntityPayload
            {
                std::string m_entityName;
                EntityID m_entityID;

                EntityPayload(std::string const& a_name, EntityID const a_id)
                {
                    m_entityName = a_name;
                    m_entityID = a_id;
                }
            };

            class EditorHelper
            {
            public:

                static bool DrawVector2Prop(std::string const& a_label, Me::Math::Vector2& a_value, float const a_resetValue = 0, float const a_columnWidth = 100.0f);
                static bool DrawVector3Prop(std::string const& a_label, Me::Math::Vector3& a_value, float const a_resetValue = 0, float const a_columnWidth = 100.0f);
                static bool DrawVector4Prop(std::string const& a_label, Me::Math::Vector4& a_value, float const a_resetValue = 0, float const a_columnWidth = 100.0f);
            };
        }
    }
}