#ifndef CORE_RTL_BASIC_STRING_H_
#define CORE_RTL_BASIC_STRING_H_

#include "copy_on_write.h"
#include "core/radium.h"
#include "core/error.h"
#include <limits.h>

namespace rtl
{


template<class T>
class basic_string
{
public:
    
    static constexpr size_t npos = UINT64_MAX;
    
    basic_string() : m_length(1) { }

    basic_string(const basic_string<T>& other)
        : m_chars(other.m_chars), m_length (other.m_length)
    {
    }



    basic_string(const T* source)
    {
        *this = source;
    }

    basic_string& operator=(basic_string& other)
    {
        m_chars = other.m_chars;
        m_length = other.length();
        return *this;

    }

    template <size_t N>
    basic_string& operator=(const T(&other)[N])
    {
        resize(N);
        m_length = N;
        assign(other);
        return *this;
    }

    basic_string& operator=(const T* other)
    {
        // todo: this  is temporary code
        size_t size = strlen(other);
        size += 1;
        m_length = size;
        resize(size);
        assign(other);

        return *this;
    }



    basic_string& operator+=(const T* other)
    {
        size_t olen = strlen(other) + 1;
        size_t newsize = length() + (olen) - 1;
        size_t oldlen = length();
        m_length = newsize;
        if(should_resize())
            resize(newsize);

        // -2 to copy over old data's null
        m_chars.memcpy(other, olen,  oldlen - 1);

        return *this;
    }

    basic_string& operator+=(basic_string& other)
    {
        size_t newsize = length() + (other.length() - 1);
        size_t oldlen = length();
        m_length = newsize;
        if (should_resize())
            resize(newsize + 1);

        m_chars.memcpy(other.c_str(), other.length() + 1, oldlen - 1);
        return *this;

    }

    /// return a substring
    basic_string<T> substr(size_t pos = 0, size_t count = npos);


    FORCEINLINE void resize(size_t n)
    {
        m_chars.resize(n);
    }

    /// copy these characters
    inline void assign(const T* chars)
    {
        m_chars.memcpy(chars, strlen(chars) + 1);
    }

    /// returns raw data from string
    constexpr T* data() 
    {
        return m_chars.copy();
    }

    /// returns a const c array
    constexpr const T* c_str() const
    {
        return m_chars.reference();
    }

    /// get the length
    constexpr size_t length() const
    {
        return m_length;
    }

    /// get reference character at pos
    constexpr T& operator[](size_t pos) { return m_chars.at_c(pos); }
    
    /// get const reference character at pos
    constexpr const T& operator[](size_t pos) const { return m_chars.at(pos); }

    /// Get the length of a string
    static size_t strlen(const T* other)
    {
        size_t size = 0;
        while (*other++ != 0) size++;
        return size;
    }

    /// get a const reference to the first character
    constexpr const T& front() const { return *m_chars.at(0); }
    /// get a reference to the first character
    constexpr T& front() { return m_chars.at_c(0); }
    
    /// get a const reference to the last character
    constexpr const T& back() const { return m_chars.at(length() - 2); }
    /// get a reference to the last character
    constexpr T& back() { return m_chars.at_c(length() - 2); }




private:
    /// Our buffer. COW happens implicitly
    copy_on_write<T> m_chars;
    size_t m_length;

    constexpr bool should_resize()
    {
        return m_length >= m_chars.get_data_size() - 1;
    }
};



template<class T>
basic_string<T> basic_string<T>::substr(size_t pos, size_t count)
{
    if (count > length())
        count = length();

    basic_string<T> newString;
    newString.resize(count - pos + 1);
    
    size_t idx = 0;
    for (size_t i = pos; i < count; i++)
    {
        newString[idx++] = m_chars.at(i);
    }

    newString[idx] = 0;
    return newString;
}

} // radium::rtl


#endif // CORE_RTL_BASIC_STRING_H_