#ifndef CORE_RTL_COPY_ON_WRITE_H_
#define CORE_RTL_COPY_ON_WRITE_H_

#include "core/radium.h"
#include <stdint.h>
#include <assert.h>
#include <string.h>

namespace rtl
{
///
///	PURPOSE
///	
/// 	** inspired by Godot Engine's CowData **
/// 
///		Provide a Copy on Write buffer for clients
/// 
///		m_dataPtr holds a pointer to a heap allocated 
///		buffer of memory
/// 
///		When the copy constructor or copy assignment
///		operator is used, the pointer to the other COWs
///		buffer is used and it's refcounter incremented
/// 
///		Reference counters are stored inside the allocated buffer
///		0		    32          64    
///		+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
///		|  Ref Count | Data Size | Data |    
///		+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// 
///		When a copy occurs:
///			1. Create a new buffer and copy the existing buffer's
///			   data into it.
///			2. Decrement the old buffer's ref count
///			3. Set the new buffer's ref count to 1
///			4. Set the current buffer to the new buffer		
/// 
template <class T>
class copy_on_write
{
public:

	copy_on_write()
		: m_dataPtr(nullptr)
	{
	}

	~copy_on_write()
	{
		if (get_refc_ptr() != nullptr)
			delete[] m_dataPtr;
	}
	void resize(int n);

	uint32_t get_size() const
	{
		if (!m_dataPtr)
			return 0;
		else
			return get_data_size();
	}
	T* copy()
	{
		__copy_on_write();
		return m_dataPtr;
	}
private:
	// todo: align this if necessary
	static constexpr size_t REF_SECTION_OFFSET = 0;
	static constexpr size_t DATA_SIZE_SECTION_OFFSET = REF_SECTION_OFFSET + sizeof(uint32_t);
	static constexpr size_t DATA_SECTION_OFFSET = DATA_SIZE_SECTION_OFFSET + sizeof(uint32_t);


	FORCEINLINE T* get_data()
	{
		return m_dataPtr + DATA_SECTION_OFFSET;
	}

	FORCEINLINE uint32_t get_data_size() const
	{
		return (uint32_t)*(m_dataPtr + DATA_SIZE_SECTION_OFFSET);
	}

	FORCEINLINE uint32_t* get_refc_ptr()
	{
		return (uint32_t*)(m_dataPtr + REF_SECTION_OFFSET);
	}

	FORCEINLINE uint32_t* get_data_size_ptr()
	{
		return (uint32_t*)(m_dataPtr + DATA_SIZE_SECTION_OFFSET);
	}
	
	uint32_t __copy_on_write();

	T* m_dataPtr;    
	 

};
template<class T>
uint32_t copy_on_write<T>::__copy_on_write()
{
	if (!m_dataPtr || get_data_size() == 0)
		return;

	uint32_t* refc = get_refc_ptr();
	uint32_t datasz = get_size();
	if (*refc > 0)
	{
		//TODO: replace with our own memory allocator

		T* newBuffer = new T[datasz];
		
		auto* refc_ptr = get_refc_ptr();
		auto* datasz_Ptr = get_data_size_ptr();
		T* data_ptr = get_data();

		*refc_ptr--;

		memcpy(newBuffer, data_ptr, datasz);
		m_dataPtr = newBuffer;

		*(get_data_size_ptr()) = datasz_Ptr;
		*(get_refc_ptr()) = 0;
	}
}

template<class T>
void copy_on_write<T>::resize(int n)
{
	if (!m_dataPtr)
	{
		m_dataPtr = new T[n];
		*(get_refc_ptr()) = 0;

		*(get_data_size_ptr()) = n;
		return;

	}

	uint32_t datasz = get_data_size();
	uint32_t* refc = get_refc_ptr();

	T* data_ptr = get_data();

	T* newBuffer = new T[n];

	T* oldBuffer = m_dataPtr;

	m_dataPtr = newBuffer;

	*(get_data_size_ptr()) = n;
	
	if(refc)
		*(get_refc_ptr()) = *refc;
	else
		*(get_refc_ptr()) = 0;

	memcpy(get_data(), data_ptr, n);

	if (refc && *refc == 0)
		delete oldBuffer;
}

}


#endif // CORE_RTL_COPY_ON_WRITE_H_