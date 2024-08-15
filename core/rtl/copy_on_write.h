#ifndef CORE_RTL_COPY_ONE_WRITE_H_
#define CORE_RTL_COPY_ONE_WRITE_H_

#include "core/radium.h"
#include "core/memory/Memory.h"
#include "core/rtl/utility.h"
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <type_traits>


template <class U>
class array;
template <class U>
class basic_string;
template <class K, class V, class H>
class unordered_map;

namespace rtl
{

///    
/// @brief 
///    A template class that allows clients to    
///    use copy-on-write. Use @ref copy() to create 
///    your own copy
///
///     ** inspired by Godot Engine's CowData **
///     
///    Provide a Copy on Write buffer for clients
///     
///    When the copy constructor or copy assignment
///    operator is used, the pointer to the other COWs
///    buffer is used and it's refcounter incremented
///     
///    Reference counters are stored inside the allocated buffer
///     @code
///    0           32                 64    
///    ┌────────────┬───────────┬──────┐
///    │  Ref Count │ Data Size │ Data │    
///    └────────────┴───────────┴──────┘
///    @endcode
/// 
///    When a copy occurs:
///        1. Create a new buffer and copy the existing buffer's data into it.
///        2. Decrement the old buffer's ref count
///        3. Set the new buffer's ref count to 1
///        4. Set the current buffer to the new buffer        
///     
///    The function @ref __copy_on_write will ensure that we do own our own copy
/// 
template <class T>
class copy_on_write
{
    template <class U>  friend class array;
    template <class U> friend class basic_string;
    template <class K, class V, class H> friend class hash_map;
public:


    copy_on_write() : m_ptr(nullptr)
    {
        resize(1);
    }

    ~copy_on_write()
    {
        unref();
    }

    copy_on_write(const copy_on_write& other)
        : m_ptr(other.m_ptr)
    {
        ref();
    }

    copy_on_write(const copy_on_write&& other) 
        : m_ptr(rtl::move(other.m_ptr))
    {
        ref();

    }

    copy_on_write& operator=(const copy_on_write& other)
    {
        m_ptr = other.m_ptr;
        ref();
        return *this;
    }

    copy_on_write& operator=(const copy_on_write&& other)
    {
        m_ptr = rtl::move(other.m_ptr);
        ref();
        return *this;
    }


    /// data[where] without copy
    const T& at(size_t where) const;

    /// data[where] with copy
    T& at_c(size_t where);

    T* at_pc(size_t where);
    const T* at_p(size_t where) const;
    /// Get your own copy
    T* copy();

    /// Obtain a const reference to the data
    const T* reference() const;

    /// size of data section
    uint32_t get_size() const;

    /// @brief
    ///    How many individual T's can fit in the data section
    ///    This is generally what you will want to use
    uint32_t get_num_data() const;
    uint32_t get_allocation_size() const;

    ///
    /// @brief
    ///    Resize the buffer to (n * T) + DATA_OFFSET bytes
    ///    Will create a new copy
    ///    
    void resize(size_t n);

    /// Copy to the <i>data section offset</i>
    void memcpy(const T* source, size_t n);
    
    /// @brief
    ///    Copy to the data section + offset
    ///    Note that this will copy relative to the offset
    ///    
    void memcpy(const T* source, size_t n, size_t offset);

    constexpr uint32_t get_reference_count() const
    {
        return *(uint32_t*)(((uint8_t*)m_ptr) + REFCOUNT_OFFSET);

    }

    constexpr uint32_t get_data_size() const
    {
        return *(uint32_t*)(((uint8_t*)m_ptr) + SIZE_OFFSET);
    }


private:

    static constexpr size_t REFCOUNT_OFFSET = 0;
    static constexpr size_t SIZE_OFFSET = REFCOUNT_OFFSET + 4;
    static constexpr size_t DATA_OFFSET = SIZE_OFFSET + 4;
    constexpr T* get_data()
    {
        return (T*)(((uint8_t*)m_ptr) + DATA_OFFSET);

    }
    constexpr const T* get_data() const
    {
        return (T*)(((uint8_t*)m_ptr) + DATA_OFFSET);
    }

    constexpr uint32_t* get_refc_ptr()
    {
        return (uint32_t*)(((uint8_t*)m_ptr) + REFCOUNT_OFFSET);
    }

    constexpr uint32_t* get_data_size_ptr()
    {
        return (uint32_t*)(((uint8_t*)m_ptr) + SIZE_OFFSET);
    }

    constexpr size_t get_alloc_size(size_t n)
    {
        //          objects             meta data
        return (n * sizeof(T)) + (sizeof(uint32_t) * 2);
    }


    uint32_t __copy_on_write();

    void ref();
    void unref();

    T* m_ptr;
};

/// 
/// @brief
///    Create a copy of the buffer for our own use
/// 
///    If this is the owning instance or it has no size, 
///    nothing will happen
/// 
template<class T>
uint32_t copy_on_write<T>::__copy_on_write()
{
    if (!m_ptr || get_size() == 0)
        return 0;

    if (get_reference_count() == 1)
        return 1;

    uint32_t old_size = get_size();

    uint32_t* old_ref_count_ptr = get_refc_ptr();
    uint32_t rc = *old_ref_count_ptr;
    (*old_ref_count_ptr)--;

    T* old_data_ptr = get_data();

    T* new_buffer = static_cast<T*>(radium::GenericAllocator::alloc_static(old_size + 8));

    m_ptr = new_buffer;

    *(get_data_size_ptr()) = old_size;
    *(get_refc_ptr()) = 1;

    ::memcpy(get_data(), old_data_ptr, old_size);

    return rc;
    
}

template<class T>
void copy_on_write<T>::ref()
{
    if (m_ptr)
    {
        *(get_refc_ptr()) += 1;
    }
}

template<class T>
void copy_on_write<T>::unref()
{
    if (m_ptr)
    {

        if (get_reference_count() == 1)
        {
            if constexpr (!std::is_trivially_destructible_v<T>)
            {
                for (size_t i = 0; i < get_num_data(); i++)
                    at_c(i).~T();
            }
            radium::GenericAllocator::free_static(m_ptr);
            m_ptr = nullptr;
        }
        else
            *(get_refc_ptr()) -= 1;
    }
}

///
/// Resizes the buffer
/// 
///    This will perform a copy-on-write
/// 
template<class T>
void copy_on_write<T>::resize(size_t n)
{
    uint32_t rc = __copy_on_write();

    T* new_buffer = static_cast<T*>(radium::GenericAllocator::alloc_static(get_alloc_size(n)));

    T* old_buffer = m_ptr;
    T* old_data = get_data();
    //size_t old_size = get_size();
    size_t old_num_data = get_num_data();
    m_ptr = new_buffer;

    *(get_refc_ptr()) = 1;
    *(get_data_size_ptr()) = (uint32_t)n;



    if (old_num_data > 0)
    {

        // if this is a larger buffer, copy all of the old data
        if (n > old_num_data)
            memcpy(old_data, old_num_data);
        // otherwise, only copy the remaining data
        else if (n <= old_num_data)
            memcpy(old_data, n);
    }
    if (rc == 1)
        radium::GenericAllocator::free_static(old_buffer);



}

template<class T>
void copy_on_write<T>::memcpy(const T* source, size_t n)
{
    __copy_on_write();
    ::memcpy(get_data(), source, (n * sizeof(T)));
}

template<class T>
void copy_on_write<T>::memcpy(const T* source, size_t n, size_t offset)
{
    __copy_on_write();
    ::memcpy(get_data() + (offset * sizeof(T)), source, (n * sizeof(T)));
}

template<class T>
const T& copy_on_write<T>::at(size_t where) const
{
    const T* _ptr = get_data();
    return _ptr[where];
}

template <class T>
T& copy_on_write<T>::at_c(size_t where)
{
    __copy_on_write();
    T* _ptr = get_data();
    return _ptr[where];
}

template<class T>
inline T* copy_on_write<T>::at_pc(size_t where)
{
    __copy_on_write();
    T* _ptr = get_data();
    return &_ptr[where];
}

template<class T>
inline const T* copy_on_write<T>::at_p(size_t where) const
{
    const T* _ptr = get_data();
    return &_ptr[where];
}

template <class T>
T* copy_on_write<T>::copy()
{
    __copy_on_write();
    return (T*)(((uint8_t*)m_ptr) + DATA_OFFSET);
}

template <class T>
const T* copy_on_write<T>::reference() const
{
    return m_ptr + DATA_OFFSET;
}


template <class T>
uint32_t copy_on_write<T>::get_size() const
{
    if (!m_ptr)
        return 0;
    return get_data_size() * sizeof(T);
}

template <class T>
uint32_t copy_on_write<T>::get_num_data() const
{
    if (!m_ptr)
        return 0;
    return (get_data_size());
}

template<class T>
uint32_t copy_on_write<T>::get_allocation_size() const
{
    if (!m_ptr)
        return 0;
    else
        return (get_data_size() * sizeof(T)) + DATA_OFFSET;
}

} // rtl


#endif // CORE_RTL_COPY_ONE_WRITE_H_