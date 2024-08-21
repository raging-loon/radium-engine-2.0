#ifndef CORE_RTL_HASH_MAP_H_
#define CORE_RTL_HASH_MAP_H_

#include "core/rtl/utility.h"
#include "core/rtl/hash.h"
#include "core/rtl/copy_on_write.h"
#include "core/rtl/iterator.h"

#include <stdio.h>
#include <new>

namespace rtl 
{
template <class U, class T, class H>
class unordered_map;

///
/// @brief
///     A specialized KV pair for maps/tables using PSLs
/// 
///     TODO: replace this pragma macro with something cross-compiler supported
/// 
#pragma pack(push, 1)
template <class K, class V, typename DisplacementType = int32_t>
struct displaced_pair
{
    K first;
    V second;
    DisplacementType displacement;
    displaced_pair(const K& _k, const V& _v)
        : first(_k), second(_v), displacement(-1)
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



};
#pragma pack(pop)

///
/// @brief
///     An unordered hash map implementation using 'Robin Hood' collision resolution
///     
///     The API is basically the same as std::unordered_map
/// 
template <class K, class V, class Hash = rtl::hash<K> >
class unordered_map
{
public:
    using hashing_function  = Hash;
    using kv_map_t          = rtl::displaced_pair<K, V>;

    using const_iterator    = rtl::generic_const_iterator<kv_map_t>;
    using iterator          = rtl::generic_iterator<kv_map_t>;

    unordered_map() : m_data{}, m_element_count(0), m_size(1) { reserve(1); }
    ~unordered_map();
    /// Insert new value
    void insert(const kv_map_t& nkv);
    
    /// Get value at key
    V& at(const K& key);
    
    /// Get element at key. Will create a new on if not exists
    V& operator[](const K& key);
    V& operator[](K&& key);
    
    size_t count(const K& k) const;
    
    bool contains(const K& k) const { return index_of(k) != -1; }


    /// returns an iterator containing key's value
    /// end() if not exists
    iterator find(const K& key)
    {
        int idx = index_of(key);
        if (idx == -1) return end();

        return iterator(m_data.at_pc(idx));
    }

    /// returns an iterator containing key's value
    /// cend() if not exists
    const_iterator find(const K& key) const
    {
        int idx = index_of(key);
        if (idx == -1) return cend();

        return const_iterator(m_data.at_p(idx));
    }

    /// get total number of elements allowed before
    /// a resize will occur
    size_t max_size() const { return m_size;  }

    /// get current number of elements
    size_t size() const { return m_element_count; }
    
    /// is this map empty?
    bool empty() const { return m_element_count == 0; }

    /// Resize the array and rehash the data
    void resize(size_t n);

    /// Reserve 'n' entries, MUST be done before inserting data
    void reserve(size_t n);


    inline iterator begin() { return iterator(m_data.at_pc(0)); }

    inline iterator end() { return iterator(m_data.at_pc(m_element_count)); }

    inline const_iterator cbegin() const { return const_iterator(m_data.at_p(0)); }

    inline const_iterator cend() const { return const_iterator(m_data.at_p(m_element_count)); }

    /// get the index of 'key'. 
    /// @returns -1 on failure
    int index_of(const K& key) const;
public:
    copy_on_write<kv_map_t> m_data;
private:

    size_t m_size;
    size_t m_element_count;
    void swap(uint32_t old_index, uint32_t new_index, uint32_t probelen);

};


template<class K, class V, class Hash>
unordered_map<K, V, Hash>::~unordered_map()
{
    if (m_data.get_reference_count() != 1)
        return;

    for (int i = 0; i < m_element_count; i++)
    {
        auto* p = m_data.at_pc(i);
        if constexpr (!std::is_trivially_destructible_v<V>)
            p->second.~V();
        if constexpr (!std::is_trivially_destructible_v<K>)
            p->first.~K();
    }
}

template<class K, class V, class Hash>
void unordered_map<K, V, Hash>::insert(const kv_map_t& nkv)
{
    // resize if needed
    if (m_element_count + 1 > m_size)
        resize(m_size + 1);

    uint32_t index = hashing_function::run(nkv.first) % m_size;
    unsigned int probe_len = 0;
    unsigned int n_probe_len = 0;

    signed int swapIndex = -1;
    while (probe_len < m_size)
    {
        
        // if the object does not exist, emplcae it here
        if (m_data.at_p(index)->displacement == -1)
        {
            auto* _new = m_data.at_pc(index);
            _new->first = nkv.first;
            _new->second = nkv.second;
            _new->displacement = probe_len;
            
            m_element_count++;
            
            if (swapIndex != -1)
            {
                swap(index, swapIndex, n_probe_len);
            }

            return;
        }
        // if the keys match, update the value
        else if (m_data.at(index).first == nkv.first)
        {
            m_data.at_c(index).second = nkv.second;
            return;
        }

        // linear probing
        else
        {
            if (swapIndex == -1 &&  m_data.at(index).displacement  < (int)probe_len)
            {
                swapIndex = index;
                n_probe_len = probe_len;
            }
            index = (index + 1) % m_size;
        }

        ++probe_len;

    }
}

template<class K, class V, class Hash>
V& unordered_map<K, V, Hash>::at(const K& key)
{
    uint32_t hash = hashing_function::run(key);
    unsigned int index = hash % m_size;
    unsigned int displacement = 0;

    for (unsigned int i = 0; i < m_size; i++)
    {
        assert(m_data.at(index).displacement != -1);
        if (m_data.at(index).displacement != -1 && m_data.at(index).first == key)
            return m_data.at_c(index).second;
        
        index = (index + 1) % m_size;

    }
    abort();
}

template<class K, class V, class Hash>
V& unordered_map<K, V, Hash>::operator[](const K& key)
{

    bool exists = index_of(key) != -1;

    if (exists)
        return m_data.at_c(index_of(key)).second;


    insert({ key, V() });
    return m_data.at_c(index_of(key)).second;

}

template<class K, class V, class Hash>
V& unordered_map<K, V, Hash>::operator[](K&& key)
{
    K value = rtl::move(key);
    return this->operator[](value);
}

template<class K, class V, class Hash>
void unordered_map<K, V, Hash>::resize(size_t n)
{
    // get a copy of the data, this will increase the ref count
    copy_on_write<kv_map_t> copy = m_data;

    // resize, our old data is in m_data
    m_data.resize(n);
    
    m_size = n;
    // this will be reset to what it was in the 
    // resinsertion loop below
    m_element_count = 0;

    // mark all slots as overwrite-able
    for (size_t i = 0; i < n; i++)
        m_data.at_c(i).displacement = -1;

    // re-insert
    size_t old_size = copy.get_num_data();
    for (size_t i = 0; i < old_size; i++)
        insert(copy.at(i));

   
    // when copy goes out of scope, it will either delete itself
    // or decrease the ref count  
}

template<class K, class V, class Hash>
void unordered_map<K, V, Hash>::reserve(size_t n)
{
    assert(m_element_count == 0);
    m_data.resize(n);
    //memset(m_data.get_data(), 0, m_data.get_size());
    m_size = n;
    // mark all slots as overwriteable
    for (size_t i = 0; i < n; i++)
        m_data.at_c(i).displacement = -1;

}

template<class K, class V, class Hash>
int unordered_map<K, V, Hash>::index_of(const K& key) const
{
    uint32_t index = hashing_function::run(key) % m_size;
    for (int i = 0; i < m_element_count; i++)
    {
        if (m_data.at(index).displacement != -1 && m_data.at(index).first == key)
            return index;
        index = (index + 1) % m_size;

    }

    return -1;
}

template<class K, class V, class Hash>
void unordered_map<K, V, Hash>::swap(uint32_t old_index, uint32_t new_index, uint32_t probelen)
{
    assert(probelen != -1 && probelen != 0xffffffff);
    kv_map_t temp = m_data.at(old_index);

    kv_map_t* old = m_data.at_pc(old_index);
    kv_map_t* _new = m_data.at_pc(new_index);

    old->first = _new->first;
    old->second = _new->second;
    old->displacement = _new->displacement == -1 ? 0 : _new->displacement;

    _new->first = temp.first;
    _new->second = temp.second;
    _new->displacement = probelen;
}


} // rtl


#endif // CORE_RTL_HASH_MAP_H_