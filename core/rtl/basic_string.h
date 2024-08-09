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

	basic_string()
	{

	}

	basic_string(basic_string& other)
		: m_chars(other.m_chars)
	{
	}

	basic_string& operator=(basic_string& other)
	{
		m_chars = other.m_chars;
		return *this;

	}

	basic_string& operator=(const T* other)
	{
		// todo: this  is temporary code

		int size = 0;
		const T* temp = other;
		while (*temp++)
			size++;
		size += 1;
		m_length = size;
		resize(size);
		assign(other);

		return *this;
	}

	template <size_t N>
	basic_string& operator=(const T(&other)[N])
	{
		resize(N - 1);
		m_length = N;
		assign(other);
		return *this;
	}



	void resize(int n)
	{
		m_chars.resize(n);
	}

	void assign(const T* chars)
	{
		T* raw_data = m_chars.copy();

		int idx = 0;
		while (*chars)
		{
			*(raw_data + idx++) = *chars++;
		
		}
		*(raw_data + idx) = 0;

		m_length = idx;

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
		return m_length;
	}


	T& operator[](size_t pos)
	{
		return *(m_chars.at_c(pos));
	}

	const T& operator[](size_t pos) const
	{
		return *(m_chars.at(pos));
	}


private:
	/// Our buffer. COW happens implicitly
	copy_on_write<T> m_chars;

	/// Number of characters in our string
	size_t m_length;


};



} // radium::rtl


#endif // CORE_RTL_BASIC_STRING_H_