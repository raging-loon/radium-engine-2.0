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

Status ResourceManager::init()
{

#ifdef RADIUM_API_OPENGL
    stbi_set_flip_vertically_on_load(true);
#endif // RADIUM_API_OPENGL 
    return OK;
}

void ResourceManager::terminate()
{
  
    for (auto& i : m_ridPtrMap)
    {
        if (i.displacement != -1)
        {
            while (i.second.reference_count() > 1)
                i.second.release();
        }
    }

}

ResourceManager::~ResourceManager()
{
}

bool ResourceManager::isValidResource(RID rid)
{
    return m_ridPtrMap.find(rid) != m_ridPtrMap.end();
}

size_t ResourceManager::getRIDRefCount(RID rid)
{
    auto iter = m_ridPtrMap.find(rid);
    if (iter == m_ridPtrMap.end())
        return 0;
    
    return iter->second.reference_count();
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
    return rtl::hash<rtl::string>().run(name);
}

