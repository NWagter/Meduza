#include "MePCH.h"
#include "Platform/General/Resources/TextureBase.h"

Me::Resources::TextureBase::TextureBase(Math::Vec2 const& a_size, std::string const& a_path)
{
    m_size = a_size;
    m_filePath = a_path;
}

Me::Resources::TextureBase::~TextureBase()
{

}