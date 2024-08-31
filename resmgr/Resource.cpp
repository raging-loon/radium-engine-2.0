#include "Resource.h"
#include "ResourceManager.h"

radium::Resource::~Resource()
{
    radium::ResMgr::get().releaseResource(m_rid);
}
