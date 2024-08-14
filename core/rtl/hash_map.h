#ifndef CORE_RTL_HASH_MAP_H_
#define CORE_RTL_HASH_MAP_H_

#include "core/rtl/utility.h"
#include "core/rtl/hash.h"
#include <stdio.h>
#include "core/rtl/copy_on_write.h"
#include <new>

namespace rtl 
{

template <class U, class T, class H>
class hash_map;

///
/// @brief
///     A specialized KV pair for maps/tables using PSLs
/// 
#pragma pack(push, 1)
template <class K, class V, typename DisplacementType = int32_t>
struct displaced_pair
{
    K first;
    V second;
    DisplacementType displacement;
    displaced_pair(const K& _k, const V& _v)
        : first(_k), second(_v)
    {
    }

    displaced_pair(const K&& _k, const V&& _v)
        : first(rtl::move(_k)), second(rtl::move(_v))
    {}

    displaced_pair& operator=(const displaced_pair& o)
    {
        first = o.first;
        second = o.second;


        return *this;
    }

    explicit displaced_pair() : displacement(-1) {}
private:
    template <class U, class T, class H>
    friend class hash_map;

};
#pragma pack(pop)

///
/// @brief
///     A hash_map implementation using 'Robin Hood' collision resolution
///     
///     
/// 
template <class K, class V, class Hash = rtl::hash<K> >
class hash_map
{
public:
    using hashing_function = Hash;
    using kv_map_t = rtl::displaced_pair<K, V>;

    hash_map() 
    {
        m_data.resize(10);
        for (size_t i = 0; i < 10; i++)
        {
            m_data.at_c(i).displacement = -1;
        }
        element_count = 0;
        size = 10;
    }
    /// Insert new value
    void insert(const kv_map_t& nkv);
    
    /// Get value at key
    V* at(const K& key);



    copy_on_write<kv_map_t> m_data;
private:

    unsigned int size;
    unsigned int element_count;
    void swap(uint32_t old_index, uint32_t new_index, uint32_t problen);

};


template<class K, class V, class Hash>
void hash_map<K, V, Hash>::insert(const kv_map_t& nkv)
{
    uint32_t index = hashing_function::run(nkv.first) % size;
    unsigned int probe_len = 0;
    unsigned int n_probe_len = 0;

    signed int swapIndex = -1;

    while (probe_len < size)
    {
        // if the keys match, update the value
        if (m_data.at(index).first == nkv.first)
        {
            m_data.at_c(index).second = nkv.second;
            return;
        }

        // if the object does not exist, emplcae it here
        else if (m_data.at_p(index)->displacement == -1)
        {
            auto* _new = m_data.at_pc(index);
            _new->first = nkv.first;
            _new->second = nkv.second;
            _new->displacement = probe_len;
            
            element_count++;
            
            if (swapIndex != -1)
            {
                swap(index, swapIndex, n_probe_len);
            }

            return;
        }
        
        // linear probing
        else
        {
            if (m_data.at(index).displacement  < probe_len)
            {
                swapIndex = index;
                n_probe_len = probe_len;
            }
            index = (index + 1) % size;
        }

        ++probe_len;

    }
}

template<class K, class V, class Hash>
V* hash_map<K, V, Hash>::at(const K& key)
{
    uint32_t hash = hashing_function::run(key);
    unsigned int index = hash % size;
    unsigned int displacement = 0;

    for (int i = 0; i < size; i++)
    {
        if (m_data.at(index).displacement != -1 && m_data.at(index).first == key)
            return &m_data.at_pc(index)->second;
        
        index = (index + 1) % size;

    }
    return nullptr;
}

template<class K, class V, class Hash>
void hash_map<K, V, Hash>::swap(uint32_t old_index, uint32_t new_index, uint32_t problen)
{
    kv_map_t temp = m_data.at(old_index);

    kv_map_t* old = m_data.at_pc(old_index);
    kv_map_t* _new = m_data.at_pc(new_index);

    old->first = _new->first;
    old->second = _new->second;
    old->displacement = _new->displacement;

    _new->first = temp.first;
    _new->second = temp.second;
    _new->displacement = problen;
   }

} // rtl


#endif // CORE_RTL_HASH_MAP_H_