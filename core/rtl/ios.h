#ifndef CORE_RTL_IOS_H_
#define CORE_RTL_IOS_H_



namespace rtl
{


template <class CharT, class OutputT>
class ostream
{
public:
    using StreamType = CharT;

    void operator<<();

private:
    OutputT<CharT> m_output;
};

} // rtl


#endif // CORE_RTL_IOS_H_