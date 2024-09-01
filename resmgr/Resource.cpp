#include "Resource.h"
#include "ResourceManager.h"

radium::Resource::~Resource()
{
    radium::ResMgr::get().releaseResource(m_rid);
}

bool radium::operator==(RID l, RID r)
{
    return (*(U64*)&l) == (*(U64*)&r);
}
