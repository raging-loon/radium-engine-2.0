#ifndef RES_MGR_RESOURCE_MANAGER_H_
#define RES_MGR_RESOURCE_MANAGER_H_

#include <core/error.h>

namespace radium
{

class ResourceManager
{
public:
    static ResourceManager& get()
    {
        static ResourceManager s_instance;
        return s_instance;
    }

    
    Status init();
    void terminate();


public:
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

private:
    ResourceManager(){}
};

} // radium


#endif // RES_MGR_RESOURCE_MANAGER_H_