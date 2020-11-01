#include "MePCH.h"
#include "Utils/MeduzaUtils.h"

uint16_t Me::Utils::Utilities::GetHashedID(std::string a_strToHash)
{   
    uint16_t hashedId = 0;
    hashedId = static_cast<uint16_t>(std::hash<std::string>{}(a_strToHash));
    return hashedId;
}