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

                static void DrawVec2Prop(std::string const& a_label, Me::Math::Vec2& a_value, float const a_resetValue = 0, float const a_columnWidth = 100.0f);
                static void DrawVec3Prop(std::string const& a_label, Me::Math::Vec3& a_value, float const a_resetValue = 0, float const a_columnWidth = 100.0f);
                static bool DrawVec4Prop(std::string const& a_label, Me::Math::Vec4& a_value, float const a_resetValue = 0, float const a_columnWidth = 100.0f);
            };
        }
    }
}