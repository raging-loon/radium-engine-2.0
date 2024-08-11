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

    constexpr function(T fn) 
        : m_fn(fn) {}

    constexpr function(T&& fn)
        : m_fn(rtl::move(fn)) {}

    constexpr function(function& other)
        : m_fn(other.m_fn)
    {
    
    }

    template <class Tx>
    function(Tx&& other)
        : m_fn(rtl::move(other))
    {
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
    constexpr T operator()(Args... args)
    {
        return (m_fn)(args...);
    }

    /// check if the function is set
    constexpr bool is_valid() 
    {
        return true;
    }

    constexpr const T& get()
    {
        return m_fn;
    }

private:

    T& m_fn;

};


} // rtl


#endif // CORE_RTL_FUNCTION_H_