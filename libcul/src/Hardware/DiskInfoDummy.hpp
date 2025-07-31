#pragma once

#include <CUL/Hardware/DiskInfo.hpp>

namespace CUL
{
class CDiskInfoDummy final: public CDiskInfo
{
public:
    CDiskInfoDummy();
    ~CDiskInfoDummy();

protected:
private:
    std::vector<std::pair<std::string, float>> getDisksUsage() const override;
    float getDiskUsage( const std::string& inDiskName ) const override;
    void findDiskMappings() override;
    void mainLoop() override;
    void debugLoop() override;
};
}  // namespace CUL