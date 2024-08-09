#ifndef CORE_RTL_SMART_PTR_H_
#define CORE_RTL_SMART_PTR_H_

#include <stdint.h>
#include "utility.h"
#include "core/memory/Memory.h"
#include <xutility>

namespace rtl
{


///
/// @brief
///		Generic Shared Pointer class
///		
///		create via @ref rtl::make_shared <YourType>(YourArgs...);
///		
///		This is a reference counted Smart Pointer.
///		It will use a structure called @ref __ref_cnt_ptr to hold
///		the pointer and it's reference count
/// 
///		Copying this class will simply increase the reference count
///		Moving this class will NOT
/// 
///		During destruction, this class will try to release itself
///			1. if the reference count is 1, we are the owner: destroy the data
///			2. otherwise, decrement the refcount
/// 
template <class T >
class shared_ptr
{

public:

	shared_ptr(T* _new)
	{
		_int_store = new __ref_cnt_ptr{ ._ptr = _new, ._refcount = 1 };
	}

	~shared_ptr()
	{
		release();
	}

	shared_ptr(const shared_ptr& other)
		: _int_store(other._int_store)
	{
		_int_store->_refcount++;
	}

	shared_ptr(const shared_ptr&& other)
		: _int_store(rtl::move(other._int_store))
	{
	}

	shared_ptr& operator=(shared_ptr& other)
	{
		_int_store = other._int_store;
		other._int_store->_refcount++;
		return *this;
	}

	shared_ptr& operator=(shared_ptr&& other)
	{
		_int_store = rtl::move(other)._int_store;
	}
	

	/// get the pointer
	T* operator->()
	{
		if (_int_store)
			return _int_store->_ptr;
		else
			return nullptr;
	}
	
	/// dereference the pointer
	T& operator*()
	{
		assert(_int_store);
		return *_int_store->_ptr;
	}

	void release()
	{
		if (!_int_store)
			assert(false && "_int_store should not be null");
		
		if (_int_store->_refcount == 1)
		{
			radium::Allocator::free_aligned(_int_store->_ptr);
			delete _int_store;
		}
		else
			_int_store->_refcount--;
	}

	uint32_t reference_count() const
	{
		return _int_store->_refcount;
	}

private:

	/// @brief
	///		A simple container for holding a pointer and  
	///		the number of shared_ptrs referencing it
	/// 
	struct __ref_cnt_ptr
	{
		T* _ptr;
		uint32_t _refcount;
	};

	__ref_cnt_ptr* _int_store;


};

/// Create a new shared pointer
template <class T, class... Args>
shared_ptr<T> make_shared(Args... args)
{
	T* nt = radium::Allocator::alloc_aligned<T>(1);

	return shared_ptr<T>(
		new (nt) T(rtl::forward<Args>(args)...)
	);
}

///
/// @brief
///		Generic Unique Smart Pointer class
/// 
///		This object cannot be shared or copied, it can only
///		be moved
/// 
///		Create with @ref rtl::make_unique<T>
///		
///		Access the data via the overloaded member access operators
/// 
template <class T>
class unique_ptr 
{
public:

	unique_ptr(T* _new) : m_ptr(_new) { assert(_new); }

	~unique_ptr()
	{
		if (m_ptr)
			radium::Allocator::free_aligned(m_ptr);
	}

	unique_ptr(unique_ptr&& other) 
		: m_ptr(rtl::move(other.m_ptr))
	{
		other.m_ptr = nullptr;
	}

	unique_ptr& operator=(unique_ptr&& other)
	{
		m_ptr = rtl::move(other.m_ptr);
		other.m_ptr = nullptr;

		return *this;
	}

	T& operator*()
	{
		assert(m_ptr);
		return *m_ptr;
	}

	T* operator->()
	{
		return m_ptr;
	}

private:

	T* m_ptr;

};


/// Create a new shared pointer
template <class T, class... Args>
unique_ptr<T> make_unique(Args... args)
{
	T* nt = radium::Allocator::alloc_aligned<T>(1);

	return unique_ptr<T>(
		new (nt) T(rtl::forward<Args>(args)...)
	);
}



} // rtl

#endif // CORE_RTL_SMART_PTR_H_