#include "ResourceManager.h"
#include "Resource.h"
#include <stb_image.h>
#include <core/io/file.h>
#include <core/rtl/hash.h>
#include <core/rtl/string.h>
#include <core/debug/globlog.h>
using radium::ResourceManager;
using radium::Status;
using radium::File;
using radium::RID;

bool ResourceManager::m_isActive = false;

Status ResourceManager::init()
{

#ifdef RADIUM_API_OPENGL
    stbi_set_flip_vertically_on_load(true);
#endif // RADIUM_API_OPENGL 
    m_isActive = true;
    return OK;
}

void ResourceManager::terminate()
{
    for (auto& i : m_ridDataMap)
    {
        if (i.displacement != -1 && i.second)
            releaseResource(i.first);
    }
    for (auto& i : m_ridPtrMap)
    {
        if (i.displacement != -1)
        {
            if (i.second.reference_count() <= 1)
                i.second.~shared_ptr();
        }
    }

    m_isActive = false;
}

bool ResourceManager::isValidResource(RID rid)
{
    return m_ridDataMap.find(rid) != m_ridDataMap.end();
}

void ResourceManager::releaseResource(RID rid)
{
    if (!m_isActive) return;

    if (!ResourceManager::get().m_ridDataMap.contains(rid))
        return;
    byte* data = ResourceManager::get().m_ridDataMap[rid];
    //ENGINE_INFO("Released RID 0x%0X with data @ %p", *(uint64_t*)(&rid), data);
    if (data)
        delete[] data;

    ResourceManager::get().m_ridDataMap.erase(rid);
}

size_t ResourceManager::getRIDRefCount(RID rid)
{
    auto iter = m_ridPtrMap.find(rid);
    if (iter == m_ridPtrMap.end())
        return 0;
    
    return iter->second.reference_count();
}

ResourceManager::~ResourceManager()
{
  /*  m_ridDataMap.~unordered_map();
    m_ridPtrMap.~unordered_map();*/
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

