#include "MePCH.h"
#include "Platform/General/TextureLibrary.h"

Me::Resources::TextureLibrary* Me::Resources::TextureLibrary::ms_instance = nullptr;

Me::Resources::TextureLibrary* Me::Resources::TextureLibrary::CreateTextureLibrary()
{
    return nullptr;
}

void Me::Resources::TextureLibrary::Destroy()
{

}

Me::Texture Me::Resources::TextureLibrary::CreateTexture(std::string)
{
    return 0;
}

Me::Resources::TextureBase* Me::Resources::TextureLibrary::GetTexture(std::string)
{
    return nullptr;
}
Me::Resources::TextureBase* Me::Resources::TextureLibrary::GetTexture(unsigned int)
{
    return nullptr;
}

bool Me::Resources::TextureLibrary::UnloadTexture(std::string)
{
    return false;
}

bool Me::Resources::TextureLibrary::UnloadTexture(unsigned int, bool)
{
    return false;
}
Me::Resources::TextureLibrary::TextureLibrary()
{

}

Me::Resources::TextureLibrary::~TextureLibrary()
{

}