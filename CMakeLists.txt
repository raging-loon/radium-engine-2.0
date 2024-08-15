cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()
set(CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)

project(radium-engine VERSION 2.0)


option(ENABLE_UNIT_TESTS "Enable unit tests" OFF)

##########################
###### UNIT TESTING ###### 
##########################

if(ENABLE_UNIT_TESTS)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_Declare(
    glm
    URL https://github.com/g-truc/glm/releases/download/1.0.1/glm-1.0.1-light.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(glm) 

enable_testing()

add_subdirectory("unittest")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/unit-test")

else()
##########################
###### NORMAL BUILD ######
##########################

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")
set(CONFIG_SOURCES
    main.cpp
 )

endif()


add_executable(radium-engine
    ${CONFIG_SOURCES}
    #"core/rtl/__copy_on_write.h"
    "core/rtl/copy_on_write.h"
    "core/rtl/string.h"
    "core/rtl/basic_string.h"
    "core/radium.h"
 "core/memory/Memory.h" "core/memory/Memory.cpp" "core/rtl/smart_ptr.h" "core/rtl/utility.h" 
 "core/rtl/function.h" "core/rtl/array.h" "core/error.h"
 "core/log/log.h"
 "core/log/colors.h" "core/log/colors.cpp" "core/log/outputsystems/OutputSystem.h" "core/log/log.cpp"
 "core/log/outputsystems/StdOutSystem.h"  "core/log/outputsystems/StdoutSystem.cpp" 
 "core/log/outputsystems/FileOutputSystem.h" "core/log/outputsystems/FileOutputSystem.cpp" "core/rtl/string.cpp" "core/math/vec2.h" "core/math/vec2.cpp" "core/rtl/hash.h" "core/rtl/hash_map.h" "core/rtl/iterator.h")

target_include_directories(radium-engine PUBLIC "./")

##########################
###### UNIT TESTING ######
##########################
if(ENABLE_UNIT_TESTS)

target_link_libraries(
  radium-engine 
  GTest::gtest_main
)
include_directories("${CMAKE_SOURCE_DIR}/_deps/glm-src/")
include(GoogleTest)
gtest_discover_tests(radium-engine)


endif() 