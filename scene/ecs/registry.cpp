#include "registry.h"

using radium::registry;
using radium::entity_t;


entity_t registry::create()
{
    m_entityIdList.push_back(entity_t(++m_numEntities));
    return m_entityIdList.back();
}

