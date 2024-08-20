#ifndef CORE_RTL_ARRAY_H_
#define CORE_RTL_ARRAY_H_

#include "copy_on_write.h"
#include "core/rtl/utility.h"
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
        m_data.resize(n );
    }

    /// Fill with T
    void fill(T value)
    {
        auto _end = m_data.get_num_data();
        for (size_t i = 0; i < _end; i++)
        {
            *m_data.at_pc(i) = value;
        }
    }

    void fill_remaining(T value)
    {
        auto _end = m_data.get_num_data();

        for (size_t i = m_index; i < _end; i++)
        {
            *m_data.at_pc(i) = value;
        }
    }


    // TODO: this might need to be optimzied in the future
    void push_back(const T& value)
    {
        size_t idx = size();
        if (should_resize())
        {
            resize(size() + 1);
        }
        (m_data.at_c(m_index++)) = value;
    }

    void push_back(T&& value)
    {
        size_t idx = size();
        if (should_resize())
        {
            resize(size() + 1);
        }
        (m_data.at_c(m_index++)) = rtl::move(value);
    }
    

    void pop_back()
    {
        m_index--;
    }

    T& operator[](size_t index)
    {
        return *m_data.at_pc(index);
    }

    const T& operator[](size_t index) const
    {
        return m_data.at(index);
    }

    constexpr size_t size() const { return m_index; }

    constexpr const T& front() const { return *m_data.at_p(0); }
    constexpr const T& back() const { return *m_data.at_p(m_index - 1); }

    constexpr T& front() { return *m_data.at_pc(0); }
    constexpr T& back() { return *m_data.at_pc(m_index - 1); }


private:
    /// Holds our data. 
    copy_on_write<T> m_data;

    /// Pointer to last element
    size_t m_index;

    constexpr bool should_resize()
    {
        return (m_index >= m_data.get_data_size());
    }
};

} // rtl


#endif // CORE_RTL_ARRAY_H_