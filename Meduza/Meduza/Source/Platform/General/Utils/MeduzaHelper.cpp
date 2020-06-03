#include "mePch.h"
#include "Platform/General/Utils/MeduzaHelper.h"

meduza::API meduza::MeduzaHelper::ms_activeAPI = meduza::API::OpenGL;
bool meduza::MeduzaHelper::ms_imGui = false;
bool meduza::MeduzaHelper::ms_minimized = false;