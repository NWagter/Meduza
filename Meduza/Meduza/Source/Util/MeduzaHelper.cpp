#include "mePch.h"
#include "Util/MeduzaHelper.h"

meduza::API meduza::MeduzaHelper::ms_activeAPI = meduza::API::OpenGL;
bool meduza::MeduzaHelper::ms_imGui = false;
bool meduza::MeduzaHelper::ms_minimized = false;