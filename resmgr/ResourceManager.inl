// TODO: optimize: ~25ms for loading an image is too much
template <class T >
rtl::shared_ptr<T> radium::ResourceManager::loadResource(const rtl::string & str)
{
    //PROFILED_FUNCTION("load resource");
    static_assert(std::is_base_of_v<Resource, T>, "T must inherit from radium::Resource");

    RID id = createResourceID(str);
    
    auto iter = m_ridPtrMap.find(id);
    
    if (iter != m_ridPtrMap.end())
        return iter->second.static_pointer_cast<T>();


    byte* resData = nullptr;
    U32 resSize = 0;
    Status loadStatus = loadResourceFromDisk(str, &resData, &resSize);

    if (loadStatus != OK)
        return rtl::shared_ptr<T>();

    rtl::shared_ptr<T> resPtr = rtl::make_shared<T>();
    if (resPtr->load(resData, resSize) != RsStatus::RES_OK)
    {
        resPtr.release();
        return rtl::shared_ptr<T>();
    }

    resPtr->m_data = resData;
    resPtr->m_rid = id;
    m_ridPtrMap.insert({ id, resPtr });
    return resPtr;
}