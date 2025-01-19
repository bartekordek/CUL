#include "CUL/CUL.hpp"
#include "CUL/IMPORT_GLM.hpp"

NAMESPACE_BEGIN(CUL)

NAMESPACE_BEGIN(MATH)

struct CULLib_API SphericalCoords final
{

};

class Utils final
{
public:
    CULLib_API static const glm::vec3 sphericalToVector( float xAngle, float zAngle, float r );

protected:
private:
};

NAMESPACE_END(MATH)

NAMESPACE_END(CUL)