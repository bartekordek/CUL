#include "Hardware/DiskInfoDummy.hpp"

using namespace CUL;

CDiskInfoDummy::CDiskInfoDummy()
{
}

std::vector<std::pair<std::string, float>> CDiskInfoDummy::getDisksUsage() const
{
    return std::vector<std::pair<std::string, float>>();
}

float CDiskInfoDummy::getDiskUsage( const std::string& inDiskName ) const
{
    return 0.0f;
}

void CDiskInfoDummy::findDiskMappings()
{
}

void CDiskInfoDummy::mainLoop()
{
}

void CDiskInfoDummy::debugLoop()
{
}

CDiskInfoDummy::~CDiskInfoDummy()
{
}
