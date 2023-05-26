#include "ibaseobject.h"

namespace core {

long long IBaseObject::s_counter = 0;

IBaseObject::IBaseObject()
{
    m_id = ++IBaseObject::s_counter;
}

} // namespace core
