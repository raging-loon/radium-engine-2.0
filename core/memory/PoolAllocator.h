#ifndef CORE_MEMORY_POOL_ALLOCATOR_H_
#define CORE_MEMORY_POOL_ALLOCATOR_H_

#include <core/memory/Memory.h>
#include <core/error.h>
#include <type_traits>

namespace radium
{


///
/// @brief
///     Allocator for objects that should be placed sequentially in memory
///     e.g. for quicker cache access
/// 
///     To keep track of free memory, a singly-linked list of free chunks
///     is stored within the chunks themselves.
/// 
///     This only supports 4+ bytes on x86  and 8+ bytes on x64 because of that
///     
///     Allocation and free-ing are constant-time operations   
/// 
///     Important note: YOU are responsible for destroying objecsts
///     The pool allocator will only mark them as overwriteable, 
///     you must call their destructors
/// 
template <class T>
class PoolAllocator
{
    static_assert(sizeof(T) >= sizeof(void*), "T must be greater than 4 bytes (x86) or 8 bytes (x64)");

public:
    PoolAllocator() : m_pool(nullptr), m_head(nullptr) {

    }

    ~PoolAllocator()
    {
        if (m_pool)
            freePool();
        
    }

    ///
    /// @brief
    ///     Alloc n bytes
    ///     
    ///     This will pre-allocate the pool and fill the free list
    /// 
    ///     O(n-1) operation
    /// 
    Status initAlloc(size_t bytes)
    {
        if (m_pool)
            return ERR_ALREADY_INITIALIZED;

        m_pool = (T*)GenericAllocator::alloc_aligned(bytes, alignof(T));

        if (!m_pool)
            return ERR_UNSPECIFIED;

        _free_list* head = (_free_list*)((void*)m_pool);
        m_head = head;

        size_t bytesCovered = sizeof(T);
        int index = 0;
        // +1 for a weird issue of over allocation
        while (bytesCovered + 1 <= bytes)
        {
            bytesCovered += sizeof(T);
            head->next = (_free_list*)(m_pool + ++index);
            head = head->next;
        }
        head->next = nullptr;
        return OK;
    }

    ///
    /// @brief
    ///     Allocate nbytes * sizeof(T) bytes
    Status initAllocN(size_t nbytes)
    {
        return initAlloc(sizeof(T) * nbytes);
    }
    
    ///
    /// @brief
    ///     Free the pool
    ///     
    void freePool()
    {
        if (m_pool)
        {
            GenericAllocator::free_aligned(m_pool);
            m_pool = nullptr;
        }
    }

    ///
    /// @brief
    ///     Return the next free address
    ///     
    ///     Returns nullptr if the pool is full
    /// 
    T* alloc()
    {
        if (m_head == nullptr)
            return nullptr;

        T* location = (T*)m_head;
        m_head = m_head->next;

        return location;
    }

    ///
    /// @brief
    ///     Add ptr to the free list
    /// 
    void free(T* ptr)
    {
        *(void**)ptr = m_head;
        m_head = (_free_list*)ptr;
    }
    
private:

    struct _free_list { _free_list* next; };
    
    _free_list* m_head;
    
    T* m_pool;
    
    size_t size;

};

} // radium



#endif // CORE_MEMORY_POOL_ALLOCATOR_H_