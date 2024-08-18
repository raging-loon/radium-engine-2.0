#error "Deprecated Code"

#ifndef CORE_RTL_FUNCTION_H_
#define CORE_RTL_FUNCTION_H_

#include "utility.h"

namespace rtl
{


/// Base function pointer template. see @ref rtl::function< T(Args...)>
template <class T, class... Args>
class function
{
};


///
/// @brief 
///     function pointer template
///
///     Generic Function Pointer wrapper
///     
///     This can take take ordinary functions and lambdas
///     
///     Constructed via 
///     @code
///     rtl::function<ReturnType(ParameterTypes...)> myFunction = ...;         
///     @endcode
/// 
///     Called via overloaded '()' operator
/// 
template <class T, class... Args>
class function <T(Args...)>
{
public:
    using fn_ptr_t = T(*)(Args...);

    //constexpr function(fn_ptr_t fn) 
    //    : m_fn(fn) {}
    constexpr function() : m_fn(nullptr) {}
    constexpr function(fn_ptr_t && fn)
        : m_fn(rtl::move(fn)) {}

    constexpr function(function& other)
        : m_fn(other.m_fn)
    {
    
    }

    template <class Tx>
    function(Tx&& other)
    {
        if constexpr (std::is_class_v<Tx>)
            m_fn = &(rtl::move(other).operator ());

    }

    template<class Tx>
    function& operator=(Tx&& other)
    {
        m_fn = rtl::forward<Tx>(other);
        return *this;
    }

    function& operator=(function& other)
    {
        m_fn = other.m_fn;
        return *this;
    }

    function& operator=(function&& other)
    {
        m_fn = rtl::move(other.m_fn);
        return *this;

    }

    /// call the function
    constexpr T operator()(Args&&... args)
    {
        if constexpr(std::is_same_v<T, void>)
            m_fn(rtl::forward<Args>(args)...);
        else
            return m_fn(rtl::forward<Args>(args)...);
    }

    /// check if the function is set
    constexpr bool is_valid() 
    {
        return !!m_fn;
    }

    constexpr const fn_ptr_t get() const
    {
        return m_fn;
    }

private:

    fn_ptr_t m_fn;

};


} // rtl


#endif // CORE_RTL_FUNCTION_H_