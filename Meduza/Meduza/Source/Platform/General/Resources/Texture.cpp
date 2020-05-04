#include "mePch.h"

#include "Core.h"
#include "Util/MeduzaHelper.h"

#include "Platform/General/Resources/Texture.h"
#ifdef WINDOWS
#include "Platform/Windows/Resources/OpenGL/TextureGL.h"
#endif // WINDOWS

meduza::Texture2D* meduza::Texture2D::Create(std::string a_path)
{
	switch (MeduzaHelper::ms_activeAPI)
	{
	case meduza::API::OpenGL:
#ifdef WINDOWS
		return new TextureGL2D(a_path);
#else // WINDOWS
		break;
#endif
	default:
		break;
	}

	return nullptr;
}
