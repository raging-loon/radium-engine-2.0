#ifndef CORE_RTL_COPY_ON_WRITE_H_
#define CORE_RTL_COPY_ON_WRITE_H_

#include "core/radium.h"
#include "core/memory/Memory.h"

#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

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
///    m_dataPtr holds a pointer to a heap allocated 
///    buffer of memory
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
///     Sharing works via pointers-to-pointers
///    m_ptr holds the data
///    m_dataPtr will either hold the value of OUR m_ptr if we own it,
///    or another clients m_ptr if we don't.
///    
///    The function @ref __copy_on_write will ensure that we do own our own copy
///        
template <class T>
class copy_on_write
{
public:
    copy_on_write()
        : m_ptr(nullptr)
    {
        m_dataPtr = &m_ptr;
        resize(1);
    }

    ~copy_on_write()
    {
        // only free the buffer if we are the owner
        if (m_ptr && *get_refc_ptr() == 1)
            radium::Allocator::free_aligned(m_ptr);
        else
            *get_refc_ptr() -= 1;
    }

    copy_on_write(copy_on_write& other)
        : m_dataPtr(other.m_dataPtr)
    {
        *(other.get_refc_ptr()) += 1;
        m_ptr = nullptr;
    }

    copy_on_write& operator=(copy_on_write& other)
    {
        m_dataPtr = other.m_dataPtr;
        *(other.get_refc_ptr()) += 1;
        m_ptr = nullptr;
        return *this;
    }

    /// data[where] without copy
    const T* at(size_t where)
    {
        return (get_data() + where);
    }

    /// data[where] with copy
    T* at_c(size_t where)
    {
        __copy_on_write();
        return (get_data() + where);
    }

    /// How many bytes are allocated?
    uint32_t get_alloc_size() const
    {
        if (!*m_dataPtr)
            return 0;
        else
            return (get_data_size() + DATA_SECTION_OFFSET )* sizeof(T);
    }
    /// size of data section
    uint32_t get_size() const
    {
        if (!*m_dataPtr)
            return 0;

        return get_data_size() * sizeof(T);
    }

    /// @brief
    ///    How many individual T's can fit in the data section
    ///    This is generally what you will want to use
    uint32_t get_num_data() const
    {
        if (!m_ptr)
            return 0;
        return (uint32_t)(get_data_size());
    }

    /// Get your own copy
    T* copy()
    {
        __copy_on_write();
        return *m_dataPtr + DATA_SECTION_OFFSET;
    }

    /// Obtain a const reference to the data
    const T* reference() const
    {
        return *m_dataPtr + DATA_SECTION_OFFSET;
    }
    

    ///
    /// @brief
    ///     Resize the buffer to (n * T) + DATA_SECTION_OFFSET bytes
    ///    Will create a new copy
    ///    
    void resize(size_t n);

    /// Copy to the <i>data section offset</i>
    void memcpy(const T* source, size_t n);

    ///
    /// @brief
    ///    Copy to the data section + offset
    ///    Note that this will copy relative to the offset
    ///    
    void memcpy(const T* source, size_t n, size_t offset);


    FORCEINLINE uint32_t get_reference_count() const
    {
        return *get_refc_ptr();
    }

    FORCEINLINE uint32_t get_data_size() const
    {
        return *(uint32_t*)(void*)(*m_dataPtr + DATA_SIZE_SECTION_OFFSET);
    }



private:
    static constexpr size_t REF_SECTION_OFFSET = 0;

    static constexpr size_t DATA_SIZE_SECTION_OFFSET = REF_SECTION_OFFSET + alignof(T) < sizeof(uint32_t) ? sizeof(uint32_t) : 1;
    
    static constexpr size_t DATA_SECTION_OFFSET = DATA_SIZE_SECTION_OFFSET + DATA_SIZE_SECTION_OFFSET;
     
    FORCEINLINE T* get_data()
    {
        return *m_dataPtr + DATA_SECTION_OFFSET;
    }

    FORCEINLINE uint32_t* get_refc_ptr()
    {
        return (uint32_t*)(void*)(*m_dataPtr + REF_SECTION_OFFSET);
    }

    FORCEINLINE uint32_t* get_data_size_ptr()
    {
        return (uint32_t*)(void*)(*m_dataPtr + DATA_SIZE_SECTION_OFFSET);
    }
    

    uint32_t __copy_on_write();


    T* m_ptr;    
    T** m_dataPtr;

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
    // if we own the data, don't do anything
    if (m_ptr)
        return *get_refc_ptr();

    
    if(!*m_dataPtr || get_size() == 0)
        return 0;

    uint32_t size = get_size();

    uint32_t* old_size_ptr = get_data_size_ptr();
    uint32_t* old_ref_count_ptr = get_refc_ptr();
    
    
    (*old_ref_count_ptr) -= 1;
    
    T* old_data_ptr = get_data();

    T* newBuffer = radium::Allocator::alloc_aligned<T>((sizeof(T)*size) + DATA_SECTION_OFFSET);

    m_ptr = newBuffer;
    m_dataPtr = &m_ptr;

    *get_data_size_ptr() = *old_size_ptr;
    *get_refc_ptr() = 1;

    ::memcpy(get_data(), old_data_ptr, *old_size_ptr);
    return 1;

}


///
/// Resizes the buffer
/// 
///    This will perform a copy-on-write
/// 
template<class T>
void copy_on_write<T>::resize(size_t n)
{
    bool wasOwner = m_ptr != nullptr;

    uint32_t rc = __copy_on_write();
    // Allocate T * n + room for the headers
    
    size_t curSize = get_alloc_size();

    T* newBuffer = radium::Allocator::alloc_aligned<T>((n * sizeof(T)) + DATA_SECTION_OFFSET);
    
    T* oldBuffer = m_ptr; 
    T* old_data = get_data();
    size_t data_sz = get_num_data();

    m_ptr = newBuffer;

    uint32_t* refc = get_refc_ptr();
    uint32_t* data_size = get_data_size_ptr();
    
    if (wasOwner)
        rc = 1;
    
    *refc = rc;

    uint32_t size = static_cast<uint32_t>(n);
    *data_size = size;
    
    if(old_data)
        memcpy(old_data, data_sz);


    if (wasOwner && rc == 1)
        radium::Allocator::free_aligned(oldBuffer);
    m_dataPtr = &m_ptr;

}

template<class T>
void copy_on_write<T>::memcpy(const T* source, size_t n)
{
    __copy_on_write();
    ::memcpy(get_data(), source, (n * sizeof(T)));
}

template<class T>
inline void copy_on_write<T>::memcpy(const T* source, size_t n, size_t offset)
{
    __copy_on_write();
    ::memcpy(get_data() + (offset * sizeof(T)), source, (n * sizeof(T)));

}

} // rtl


#endif // CORE_RTL_COPY_ON_WRITE_H_