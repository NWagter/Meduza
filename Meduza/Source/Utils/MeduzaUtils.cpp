#include "MePCH.h"
#include "Utils/MeduzaUtils.h"

unsigned int Me::Utils::Utilities::GetHashedID(std::string a_strToHash)
{   
    unsigned int hashedId = 0;
    hashedId = static_cast<unsigned int>(std::hash<std::string>{}(a_strToHash));
    return hashedId;
}