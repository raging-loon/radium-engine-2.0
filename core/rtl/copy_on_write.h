#ifndef CORE_RTL_COPY_ON_WRITE_H_
#define CORE_RTL_COPY_ON_WRITE_H_

#include "core/radium.h"
#include "core/memory/Memory.h"

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
///		0		    32           64    
///		┌────────────┬───────────┬──────┐
///		│  Ref Count │ Data Size │ Data │    
///		└────────────┴───────────┴──────┘
/// 
///		When a copy occurs:
///			1. Create a new buffer and copy the existing buffer's data into it.
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
		if (m_dataPtr)
		{
			if (*get_refc_ptr() == 1)
				radium::Allocator::free_aligned(m_dataPtr);
			else
				*get_refc_ptr() -= 1;
		}
	}

	copy_on_write(copy_on_write& other)
		: m_dataPtr(other.m_dataPtr)
	{
		*(other.get_refc_ptr()) += 1;
	}

	copy_on_write& operator=(copy_on_write& other)
	{
		m_dataPtr = other.m_dataPtr;
		*(other.get_refc_ptr()) += 1;
	}



	uint32_t get_size() const
	{
		if (!m_dataPtr)
			return 0;
		else
			return get_data_size();
	}
	
	///
	/// PURPOSE
	/// 	Get create a copy of the buffer
	/// 
	T* copy()
	{
		__copy_on_write();
		return m_dataPtr;
	}


	const T* reference() const
	{
		return m_dataPtr;
	}
	
	///
	/// PURPOSE
	/// 	Resize the buffer to (n * T) + DATA_SECTION_OFFSET bytes
	///		Will create a new copy
	///		
	void resize(int n);



private:
	// todo: align this if necessary
	static constexpr size_t REF_SECTION_OFFSET = 0;
	static constexpr size_t DATA_SIZE_SECTION_OFFSET = REF_SECTION_OFFSET + 1;
	static constexpr size_t DATA_SECTION_OFFSET = DATA_SIZE_SECTION_OFFSET + 2;
	 
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
	if(!m_dataPtr || get_size() == 0)
		return 0;

	uint32_t size = get_size();

	uint32_t* old_size_ptr = get_data_size_ptr();
	uint32_t* old_ref_count_ptr = get_refc_ptr();
	
	
	if (*old_ref_count_ptr <= 1)
		return *old_ref_count_ptr;

	(*old_ref_count_ptr) -= 1;
	
	T* old_data_ptr = get_data();

	T* newBuffer = radium::Allocator::alloc_aligned<T>(size + DATA_SECTION_OFFSET);

	m_dataPtr = newBuffer;

	*get_data_size_ptr() = *old_size_ptr;
	*get_refc_ptr() = 1;

	memcpy(get_data(), old_data_ptr, *old_size_ptr);

	return 1;

}

template<class T>
void copy_on_write<T>::resize(int n)
{
	uint32_t rc = __copy_on_write();
	// Allocate T * n + room for the headers
	
	int curSize = get_size();

	T* newBuffer = radium::Allocator::alloc_aligned<T>(n + DATA_SECTION_OFFSET);
	printf("%lld\n", radium::Allocator::get_num_bytes_aligned(newBuffer));
	
	T* oldBuffer = m_dataPtr;
	m_dataPtr = newBuffer;

	uint32_t* refc = get_refc_ptr();
	uint32_t* data_size = get_data_size_ptr();
	if (curSize == 0)
		rc = 1;
	
	*refc = rc;


	*data_size = n;

	if (oldBuffer && rc == 1)
		radium::Allocator::free_aligned(m_dataPtr);
}

} // rtl


#endif // CORE_RTL_COPY_ON_WRITE_H_