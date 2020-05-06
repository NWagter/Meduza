#include "mePch.h"

#include "Core.h"
#include "Util/MeduzaHelper.h"

#include "Platform/General/Resources/Texture.h"
#ifdef WINDOWS
#include "Platform/Windows/Resources/OpenGL/TextureGL.h"
#endif // WINDOWS

meduza::Texture2D* meduza::Texture2D::Create(std::string a_path, unsigned int a_id)
{
	switch (MeduzaHelper::ms_activeAPI)
	{
	case meduza::API::OpenGL:
#ifdef WINDOWS
		return new Texture2DGL(a_path, a_id);
#else // WINDOWS
		break;
#endif
	default:
		break;
	}

	return nullptr;
}
