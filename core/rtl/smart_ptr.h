#ifndef CORE_RTL_SMART_PTR_H_
#define CORE_RTL_SMART_PTR_H_

#include <stdint.h>

namespace rtl
{


template <class T>
class shared_ptr
{

public:

private:

	struct __ref_cnt_ptr
	{
		T* _ptr;
		uint32_t _refcount;
	};

	__ref_cnt_ptr* _int_store;

};

template <class T>
shared_ptr<T> make_shared()
{
	
}


} // rtl

#endif // CORE_RTL_SMART_PTR_H_