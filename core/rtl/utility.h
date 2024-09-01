#ifndef CORE_RTL_UTILITY_H_
#define CORE_RTL_UTILITY_H_


/// 
/// This is the only STL library included in this project
/// why? There are something we cannot do with fancy
/// template metaprograming. 
///    
/// Instead we must rely on information provided by the compiler;
/// information found in the type_traits header
/// 
#include <type_traits>
#include <utility>

namespace rtl
{
/// disable qualifier warning
/// irrelavent in this case
#pragma warning(push)
#pragma warning(disable: 4180)

///
/// @brief
///    This was mostly copied from the STL because 
///    it has very little performance over head ( if any)
///    and is really the best way to implement perfect forwarding
///    and movement
/// 
///    @ref remove_reference<T>::type will simply give you the type without 
///    the reference
/// 
///    e.g. remove_reference<const int&>::type = int
/// 
///    This first class exists so the following two can use template specialization
/// 
template <class T>
struct remove_reference
{
    using type = T;
    using const_type = const T;
};

/// deduce type from reference
template <class T>
struct remove_reference<T&> 
{
    using type = T;
    using const_type = const T&;
};

/// deduce type from rvalue reference
template <class T>
struct remove_reference<T&&>
{
    using type = T;
    using const_type = const T&&;
};

/// used as a function argument
template <class T>
using remove_reference_t = typename remove_reference<T>::type;

/// end warning disable
#pragma warning(pop)

/// 
/// @brief
///    T& -> T&&
///    Used for perfect forwarding
/// 
template <class T>
constexpr T&& forward(remove_reference_t<T>& arg)
{
    return static_cast<T&&>(arg);
}

template <class T>
constexpr T&& forward(remove_reference_t<T>&& arg)
{
    return static_cast<T&&>(arg);
}


///
/// @brief
///    Used in move semantics
///    Will move stuff
/// 
template <class T>
constexpr typename remove_reference<T>::type&& move(T&& arg)
{
    return std::move(arg);
    //return static_cast<remove_reference<T>&&>(arg);
}

template <class T>
constexpr void swap(T& l, T& r)
{
    T temp = l;
    l = r;
    r = temp;
}

template <class T1, class T2>
struct pair
{
    T1 first;
    T2 second;

    pair() : first{}, second{} {};

    pair(const T1& x, const T2& y)
        : first(x), second(y) {}

    template <class U1, class U2>
    pair(U1&& x, U2&& y)
        : first(x), second(y) 
    {}

    pair(const pair& other)
        : first(other.first), second(other.second)
    {}

};



} // rtl

#endif // CORE_RTL_UTILITY_H_