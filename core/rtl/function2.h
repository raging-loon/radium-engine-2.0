#ifndef CORE_RTL_FUNCTION2_H_
#define CORE_RTL_FUNCTION2_H_

#include <core/rtl/utility.h>
#include <core/rtl/smart_ptr.h>


#include <memory>
namespace rtl2
{
template <class RType, class... Args>
class Callable
{
public:
    virtual ~Callable() = default;
    virtual RType invoke(Args... args) = 0;
};

template <class Fn, class RType, class... Args>
class CallableWrapper : public Callable<RType, Args...>
{
public:
    explicit CallableWrapper(Fn fn) : m_fn(rtl::move(fn)) {}

    RType invoke(Args... args) override
    {
        if constexpr (std::is_same_v<RType, void>)
            m_fn(rtl::forward<Args>(args)...);
        else
        return m_fn(rtl::forward<Args>(args)...);
    }

private:
    Fn m_fn;
};

template <class Signature>
class function;

template <class Ret, class... Args>
class function <Ret(Args...)>
{

public:
    
    
    template <class Fn>
    function(Fn fn)
        : m_functor(rtl::make_unique<CallableWrapper<Fn, Ret, Args...>>(rtl::move(fn))) {}

    function() {}

    template<class Fn>
    function& operator=(const function& other)
    {
        m_functor = (rtl::make_unique<CallableWrapper<Fn, Ret, Args...>>(other.m_functor));
        return *this;
    }

    Ret operator()(Args&&...args)
    {
        if constexpr (std::is_same_v<Ret, void>)
            m_functor->invoke(rtl::forward<Args>(args)...);
        else
            return  m_functor->invoke(rtl::forward<Args>(args)...);
    }

private:
    rtl::unique_ptr<Callable<Ret, Args...>> m_functor;
};




} // rtl



#endif // CORE_RTL_FUNCTION2_H_