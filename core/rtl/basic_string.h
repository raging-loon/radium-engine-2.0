#ifndef CORE_RTL_BASIC_STRING_H_
#define CORE_RTL_BASIC_STRING_H_

#include "copy_on_write.h"
#include "core/radium.h"


namespace rtl
{


template<class T>
class basic_string
{
public:

	basic_string() { }

	basic_string(basic_string& other)
		: m_chars(other.m_chars)
	{
	}

	basic_string(const T* source)
	{
		*this = source;
	}

	basic_string& operator=(basic_string& other)
	{
		m_chars = other.m_chars;
		return *this;

	}

	template <size_t N>
	basic_string& operator=(const T(&other)[N])
	{
		resize(N);
		assign(other);
		return *this;
	}

	basic_string& operator=(const T* other)
	{
		// todo: this  is temporary code
		size_t size = strlen(other);
		size += 1;
		resize(size);
		assign(other);

		return *this;
	}

	template <size_t N>
	basic_string& operator+=(const T(&other)[N])
	{
		// +2, old null and other null
		size_t newsize = length() + (N - 1);
		size_t oldlen = length();
		resize(newsize);
		// -2 to copy over old data's null
		m_chars.memcpy(other, N , oldlen - 1);

		return *this;
	}


	basic_string& operator+=(basic_string& other)
	{
		size_t newSize = length() + (other.length() - 1);
		size_t oldlen = length();

		resize(newSize);
		m_chars.memcpy(other.c_str(), other.length(), oldlen - 1);
		return *this;

	}


	FORCEINLINE void resize(int n)
	{
		m_chars.resize((size_t)n);
	}

	inline void assign(const T* chars)
	{
		m_chars.memcpy(chars, strlen(chars) + 1);
	}

	FORCEINLINE T* data() 
	{
		return m_chars.copy();
	}

	FORCEINLINE const T* c_str() const
	{
		return m_chars.reference();
	}

	constexpr size_t length() const
	{
		return m_chars.get_data_size();
	}


	T& operator[](size_t pos)
	{
		return *(m_chars.at_c(pos));
	}

	const T& operator[](size_t pos) const
	{
		return *(m_chars.at(pos));
	}

	static size_t strlen(const T* other)
	{
		size_t size = 0;
		while (*other++) size++;
		return size;
	}

private:
	/// Our buffer. COW happens implicitly
	copy_on_write<T> m_chars;


	FORCEINLINE void resize(size_t n)
	{
		m_chars.resize(n);
	}


};



} // radium::rtl


#endif // CORE_RTL_BASIC_STRING_H_