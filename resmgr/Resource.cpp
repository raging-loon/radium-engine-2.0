#include "Resource.h"
#include "ResourceManager.h"

radium::Resource::~Resource()
{
    if (m_data)
    {
        delete[] m_data;
        m_data = nullptr;
    }
}

