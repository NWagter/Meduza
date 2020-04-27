#include "mePch.h"
#include "Core/MeduzaUtil.h"

bool meduza::MeduzaHelper::ms_optick = false;

void meduza::MeduzaHelper::EnableOptick(bool a_enable)
{
	ms_optick = a_enable;
}
