#include "MePCH.h"
#include "Core/GUID.h"

static std::random_device gs_randomDevice;
static std::mt19937_64 gs_engine(gs_randomDevice());
static std::uniform_int_distribution<uint32_t> gs_uniformDistribution;


Me::UUID::UUID() : m_guid(gs_uniformDistribution(gs_engine))
{
}

Me::UUID::UUID(uint32_t const a_guid) : m_guid(a_guid)
{

}