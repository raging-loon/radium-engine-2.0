#ifndef RES_MGR_RESOURCE_MANAGER_H_
#define RES_MGR_RESOURCE_MANAGER_H_

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




public:
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

private:
    ResourceManager(){}
};

} // radium


#endif // RES_MGR_RESOURCE_MANAGER_H_