#ifndef CORE_RTL_ARRAY_H_
#define CORE_RTL_ARRAY_H_

#include "copy_on_write.h"

namespace rtl
{


///
/// @brief
///     array to hold T data
/// 
///     This uses a COW buffer to hold the data
/// 
///     elem_ptr points to the last element in the buffer,
///     as to reduce resizing.
/// 
template <class T>
class array
{
public:

    array() : m_index(0)
    {
    }

    void resize(size_t n)
    {
        m_data.resize(n);

    }

    // TODO: this might need to be optimzied in the future
    void push_back(const T& value)
    {
        size_t idx = size() - 1;
        if (should_resize())
        {
            resize(size() + 1);
        }
        (m_data.at_c(m_index++)) = value;
    }

    void push_back(T&& value)
    {
        size_t idx = size() - 1;
        if (should_resize())
        {
            resize(size() + 1);
        }
        (m_data.at_c(m_index++)) = rtl::move(value);

    }

    T operator[](size_t index)
    {
        return *m_data.at_c(index);
    }

    const T operator[](size_t index) const
    {
        return *m_data.at(index);
    }

    constexpr size_t size()
    {
        return m_index;
    }
private:
    /// Holds our data. 
    copy_on_write<T> m_data;

    /// Pointer to last element
    size_t m_index;

    constexpr bool should_resize()
    {
        return (m_index >= m_data.get_data_size() - 1);
    }
};

} // rtl


#endif // CORE_RTL_ARRAY_H_