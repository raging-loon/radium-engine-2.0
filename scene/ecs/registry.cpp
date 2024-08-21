#include "registry.h"

using radium::registry;
using radium::entity_t;


registry::registry()
    : m_entityGraveyard{}, m_entityIdList{}, m_poolFactory{}, m_numEntities(0)
{
}

registry::~registry()
{
}

entity_t registry::create()
{
    m_entityIdList.push_back(entity_t(++m_numEntities));
    return m_entityIdList.back();
}

void release(entity_t eid)
{

}


