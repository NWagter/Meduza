#include "MePCH.h"
#include "Utils/MeduzaUtils.h"

uint16_t Me::Utils::Utilities::GetHashedID(std::string const& a_strToHash)
{   
    uint16_t hashedId = 0;
    hashedId = static_cast<uint16_t>(std::hash<std::string>{}(a_strToHash));
    return hashedId;
}

Me::Math::Vec4 Me::Utils::TextureSlice(Math::Vec2 const& a_textureSize, Math::Vec2 const& a_sliceBegin, Math::Vec2 const& a_sliceSize)
{
    Math::Vec4 slice = Math::Vec4(0,0,1,1);

    if(a_sliceBegin.m_x != 0)
    {
        slice.m_x = (1 / a_textureSize.m_x) * (a_sliceBegin.m_x + 0.5f);
    }

    if(a_sliceBegin.m_y != 0)
    {
        slice.m_y = (1 / a_textureSize.m_y) * (a_sliceBegin.m_y + 0.5f);
    }

    if(a_sliceSize.m_x != a_textureSize.m_x)
    {
        slice.m_z = (1 / a_textureSize.m_x) * (a_sliceSize.m_x - 0.5f);
    }
    
    if(a_sliceSize.m_y != a_textureSize.m_y)
    {
        slice.m_w = (1 / a_textureSize.m_y) * (a_sliceSize.m_y - 0.5f);
    }

    return slice;
}