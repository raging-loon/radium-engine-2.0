#ifndef CORE_LOG_LOG_H_
#define CORE_LOG_LOG_H_

#include "core/rtl/string.h"
#include "core/rtl/utility.h"
#include "core/log/colors.h"
#include "outputsystems/OutputSystem.h"
#include <stdarg.h>
#include <type_traits>


namespace radium
{

enum class LogLevel : int
{
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};


///
/// @brief 
///     Logging Class
/// 
///     The Logger class is responsible for constructing output
///     
///     Output of the logs is delegated to an @ref OutputSystem
///     
///     Logger::setOutputSystem<Type>() creates a new output system
///     
///     Logger::setOutputSystem<Type>(ConstructionArgs&&...) creates a new output system
///                                            and passes args... to its constructor
/// 
///     Logger::info, Logger::debug, etc. are wrappers around Logger::log
///     
/// 
class Logger
{
public:

    Logger(const rtl::string& name) 
        : m_name(rtl::move(name)), m_outputSystem{nullptr}
    {}
    Logger(const char* name) : m_name(name), m_outputSystem{ nullptr } {}
    ~Logger();
    ///
    /// @brief
    ///     Log to the @ref OutputSystem
    /// 
    ///     1. Log with LogLevel ll
    ///     2. Construct a log based on msg and args
    ///     3. Forward constructed log to the output system
    ///     
    void log(LogLevel ll, const char* msg, ...);

    /// Set the output system
    template <class OutputSystemType>
    void setOutputSystem()
    {
        static_assert(std::is_base_of_v<radium::OutputSystem, OutputSystemType> && "OutputSystemType must derive from radium::OutputSytem");

        if (m_outputSystem)
            delete m_outputSystem;
        m_outputSystem = new OutputSystemType();
    }

    /// Set the output system and pass @ref ConstructionArgs to its constructor
    template <class OutputSystemType, class...ConstructionArgs>
    void setOutputSystem(ConstructionArgs&&... args)
    {
        static_assert(std::is_base_of_v<radium::OutputSystem, OutputSystemType> && "OutputSystemType must derive from radium::OutputSytem");

        if (m_outputSystem)
            delete m_outputSystem;
        m_outputSystem = new OutputSystemType(rtl::forward<ConstructionArgs>(args)...);
    }

    /// fwds to Log with LogLevel::DEBUG
    template<class... Args>
    constexpr void debug(const char* message, Args&&... args)
    {
        log(LogLevel::DEBUG, message, rtl::forward<Args>(args)...);
    }

    /// fwds to Log with LogLevel::INFO
    template <class... Args>
    constexpr void info(const char* message, Args&&... args)
    {
        log(LogLevel::INFO, message, rtl::forward<Args>(args)...);
    }

    /// fwds to Log with LogLevel::WARNING
    template <class... Args>
    constexpr void warning(const char* message, Args&&... args)
    {
        log(LogLevel::WARNING, message, rtl::forward<Args>(args)...);
    }

    /// fwds to Log with LogLevel::ERROR
    template <class... Args>
    constexpr void error(const char* message, Args&&... args)
    {
        log(LogLevel::ERROR, message, rtl::forward<Args>(args)...);
    }

    /// fwds to Log with LogLevel::CRITICAL
    template <class... Args>
    constexpr void critical(const char* message, Args&&... args)
    {
        log(LogLevel::CRITICAL, message, rtl::forward<Args>(args)...);
    }

private:
    
    OutputSystem* m_outputSystem;

    rtl::string m_name;

    const char* m_colorMap[5] =
    {
        {Colors::GREEN}, /// DEBUG
        {Colors::GREEN}, /// INFO
        {Colors::YELLOW},/// WARNING
        {Colors::RED},   /// ERROR
        {Colors::RED}    /// CRITICAL
    };

};


} // radium


#endif //CORE_LOG_LOG_H_