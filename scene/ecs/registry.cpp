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
    if (m_entityGraveyard.size() > 0)
    {
        entity_t id = m_entityGraveyard.back();
        m_entityGraveyard.pop_back();
        return id;
    }
    m_entityIdList.push_back(entity_t(++m_numEntities));
    return m_entityIdList.back();
}

void registry::release(entity_t eid)
{
    m_entityGraveyard.push_back(eid);
    m_poolFactory.removeAll(eid);
}

bool registry::isOrphaned(entity_t eid)
{
    return m_entityGraveyard.contains(eid);
}

bool registry::isValid(entity_t eid)
{
    return m_entityIdList.contains(eid) && !m_entityGraveyard.contains(eid);
}
