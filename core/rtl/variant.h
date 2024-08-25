#ifndef CORE_RTL_VARIANT_H_
#define CORE_RTL_VARIANT_H_

#include <type_traits>
#include <core/rtl/utility.h>
namespace rtl
{

template <typename... Types>
struct typelist {};

template <typename... Types>
class variant;


///
/// @brief 
///     Variant, holds @Types types in a union
///     
template <typename... Types>
class variant<typelist<Types...> >
{
public:

    variant() : m_idx(0) {}
    
    template <typename T>
    void set(T&& val)
    {
        new (&m_varStorage.data) T(rtl::forward<T>(val));
        m_idx = find < T, 0, Types...>();
    }

    template <typename T>
    T& as()
    {
        return *reinterpret_cast<T*>(&m_varStorage.data);
    }

private:
    
    template <typename T, size_t idx, typename first, typename...list>
    static constexpr size_t find()
    {
        if constexpr (std::is_same_v<T, first>)
            return idx;
        else
            return find<T, idx + 1, list...>();
    }


private:

    union Storage
    {
        Storage() {}
        ~Storage() {}
        typename std::aligned_union<0, Types...>::type data;
    };

    //Storate m_varStorage;
    size_t m_idx{ 0 };
    Storage m_varStorage;

};


} // rtl 


#endif // CORE_RTL_VARIANT_H_