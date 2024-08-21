#ifndef SCENE_ECS_SPARSE_SET_H_
#define SCENE_ECS_SPARSE_SET_H_

#include <core/rtl/array.h>
#include <core/types.h>
#include <core/rtl/utility.h>

namespace radium
{

///
/// @brief
///     A sparse set implementations
/// 
///     https://skypjack.github.io/2020-08-02-ecs-baf-part-9/
/// 
template <typename Index = radium::I32>
class sparse_set
{
    using index_t = Index;
    /// tombstone value
    constexpr static index_t EMPTY_SLOT = -1;
public:

    sparse_set(index_t sparse_size = 32, index_t dense_size = 24)
    {
        m_sparse_array.resize(sparse_size);
        m_dense_array.resize(dense_size);
        m_sparse_array.fill(EMPTY_SLOT);
        m_dense_array.fill(EMPTY_SLOT);
    }
    ///
    /// @brief
    ///     Add ID to the dense array and associate
    ///     its position with the sparse array
    /// 
    index_t add(index_t id)
    {

        if (id > m_sparse_array.max_size())
        {
            m_sparse_array.resize(m_sparse_array.size() + id + 1);
            m_sparse_array.fill_remaining(EMPTY_SLOT);

        }

        m_dense_array.push_back(id);
        m_sparse_array[id] = (index_t)(m_dense_array.size()) - 1;
        printf("Added %d at index %d\n",id, m_sparse_array[id]);
        return get_position(id);
    }

    ///
    /// @remove
    ///     Remove ID if it exists
    ///     Will mark its spot with the tombstone value
    /// 
    void remove(index_t id)
    {
        if (!contains(id))
            return;
        
        I32 last = m_dense_array.back();

        rtl::swap(m_dense_array.back(), m_dense_array[m_sparse_array[id]]);
        rtl::swap(m_sparse_array[last], m_sparse_array[id]);
        m_dense_array.pop_back();
        m_sparse_array[id] = EMPTY_SLOT;
    }


    bool contains(index_t id)
    {
        return m_sparse_array[id] != EMPTY_SLOT;
    }

    index_t get_position(index_t pos)
    {
        size_t index = m_sparse_array[pos];
        if (index == -1)
            return -1;
        return m_dense_array[index];
    }



private:
    rtl::array<index_t> m_sparse_array;
    rtl::array<index_t> m_dense_array;

    
};

} // radium


#endif // SCENE_ECS_SPARSE_SET_H_