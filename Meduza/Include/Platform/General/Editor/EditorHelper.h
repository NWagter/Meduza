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

                static void DrawVec2Prop(const std::string&, Me::Math::Vec2&, float = 0, float = 100.0f);
                static void DrawVec3Prop(const std::string&, Me::Math::Vec3&, float = 0, float = 100.0f);
                static bool DrawVec4Prop(const std::string&, Me::Math::Vec4&, float = 0, float = 100.0f);
            };
        }
    }
}