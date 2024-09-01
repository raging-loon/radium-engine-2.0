#include "ResourceManager.h"
#include "Resource.h"
#include <stb_image.h>
#include <core/io/file.h>
#include <core/rtl/hash.h>
#include <core/rtl/string.h>

using radium::ResourceManager;
using radium::Status;
using radium::File;
using radium::RID;

Status ResourceManager::init()
{

#ifdef RADIUM_API_OPENGL
    stbi_set_flip_vertically_on_load(true);
#endif // RADIUM_API_OPENGL 

    return OK;
}

void ResourceManager::terminate()
{
}

bool ResourceManager::isValidResource(RID rid)
{
    return m_ridDataMap.find(rid) != m_ridDataMap.end();
}

void ResourceManager::releaseResource(RID rid)
{
    byte* data = m_ridDataMap[rid];
    if (data)
        delete[] data;

    m_ridDataMap.erase(rid);

}

Status ResourceManager::loadResourceFromDisk(const rtl::string& location, byte** out, U32* outSize)
{
    File res;
    Status openStat = res.open(location, File::READ);
    if (openStat != OK)
        return openStat;

    *outSize = (U32)res.getSize();
    
    *out = new byte[*outSize];

    res.read(*out, *outSize);

    return OK;
}

RID ResourceManager::createResourceID(const rtl::string& name)
{
    RID id = { .name = rtl::hash<rtl::string>().run(name) };
    return id;
}

