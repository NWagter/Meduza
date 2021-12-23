#pragma once

namespace Me
{
    namespace Editor
    {
        namespace Helper
        {
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