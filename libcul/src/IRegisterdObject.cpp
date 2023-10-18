#include "CUL/IRegisteredObject.hpp"
#include "CUL/ObjectRegistry.hpp"

using namespace CUL;

IRegisterdObject::IRegisterdObject()
{
    m_id = CUL::ObjectRegistry::getInstance().getFirstFreeIndex();
}

std::uint64_t IRegisterdObject::getId() const
{
    return m_id;
}

IRegisterdObject::~IRegisterdObject()
{
    CUL::ObjectRegistry::getInstance().removeIndex( m_id );
}