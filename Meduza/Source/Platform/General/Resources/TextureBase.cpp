#include "MePCH.h"
#include "Platform/General/Resources/TextureBase.h"

Me::Resources::TextureBase::TextureBase(const Math::Vec2 a_size, std::string a_path)
{
    m_size = a_size;
    m_filePath = a_path;
}

Me::Resources::TextureBase::~TextureBase()
{

}