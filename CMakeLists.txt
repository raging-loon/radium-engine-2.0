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
option(ENABLE_PROFILER "Enable Profiling" OFF)


set(API_DX11 "Use DirectX 11" ON)
set(API_DX12 "Use DirectX 12" OFF)

if(ENABLE_UNIT_TESTS)

    add_subdirectory("unittest")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/unit-test")

else()

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")
    set(CONFIG_SOURCES
        "main/main.cpp"
     )
endif()

if(ENABLE_PROFILER)
    add_compile_definitions(PROFILING_ENABLED=1)
endif()



if(WIN32)
    add_compile_definitions(RADIUM_PLATFORM_WIN32=1)

    file(GLOB_RECURSE PLATFORM_SOURCES 
        "${CMAKE_SOURCE_DIR}/platform/windows/*.h"
        "${CMAKE_SOURCE_DIR}/platform/windows/*.cpp")


    if(API_DX11)
        set(GRAPHICS_API_LIBS d3dcompiler.lib D3D11.lib dxgi.lib dxguid.lib)
        file(GLOB_RECURSE GRAPHICS_API_SOURCES
            "${CMAKE_SOURCE_DIR}/renderer/dx11/*.h"
            "${CMAKE_SOURCE_DIR}/renderer/dx11/*.cpp"
        )

        set(GRAPHICS_API_SOURCES ${GRAPHICS_API_SOURCES} "${CMAKE_SOURCE_DIR}/thirdparty/dx11error/dxerr.cpp")
        add_compile_definitions(RADIUM_API_DX11=1)

        set(ADDITIONAL_INCLUDES ${ADDITIONAL_INCLUDES} "${CMAKE_SOURCE_DIR}/thirdparty/dx11error/")

    elseif(API_DX12)
        set(GRAPHICS_API_LIBS d3dcompiler.lib D3D12.lib dxgi.lib dxguid.lib)
        file(GLOB_RECURSE GRAPHICS_API_SOURCES
            "${CMAKE_SOURCE_DIR}/renderer/dx12/*.h"
            "${CMAKE_SOURCE_DIR}/renderer/dx12/*.cpp"
        )

        add_compile_definitions(RADIUM_API_DX12=1)
    endif()
 
elseif(UNIX)
    message(FATAL_ERROR "Lazy developers forgot to port")
    file(GLOB_RECURSE PLATFORM_SOURCES 
        "${CMAKE_SOURCE_DIR}/platform/unix/*.h"
        "${CMAKE_SOURCE_DIR}/platform/unix/*.cpp"
)

endif()

add_executable(radium-engine
    ${CONFIG_SOURCES}
    ${PLATFORM_SOURCES}
    ${GRAPHICS_API_SOURCES}
    #"core/rtl/__copy_on_write.h"
    "core/rtl/copy_on_write.h"
    "core/rtl/string.h"
    "core/rtl/basic_string.h"
    "core/radium.h"
    "core/memory/Memory.h" 
    "core/memory/Memory.cpp" "core/rtl/smart_ptr.h" "core/rtl/utility.h" 
    "core/rtl/array.h" 
    "core/error.h"
    "core/debug/globlog.h"
    "core/log/colors.h" 
    "core/log/colors.cpp" "core/log/outputsystems/OutputSystem.h" "core/log/log.cpp"
    "core/log/outputsystems/StdOutSystem.h"  "core/log/outputsystems/StdoutSystem.cpp" 
    "core/log/outputsystems/FileOutputSystem.h" 
    "core/log/outputsystems/FileOutputSystem.cpp" "core/rtl/string.cpp"
    "core/rtl/hash.h" 
    "core/rtl/hash_map.h" "core/rtl/iterator.h" "core/types.h" "core/engine/Application.h" "core/io/file.h" 
    "core/debug/backtrace.h" 
    "core/debug/globlog.h" "core/debug/globlog.cpp"  "core/debug/seh.h"  
    "core/thread/thread.h" 
    "core/rtl/function.h" "core/thread/mutex.h"
    "core/memory/PoolAllocator.h" 
    "scene/ecs/registry.h" "scene/ecs/ComponentPool.h" "scene/ecs/sparse_set.h" "scene/ecs/entity.h"
    "scene/component/Sprite2D.h" 
    "scene/ecs/ComponentPoolFactory.h"  "scene/ecs/registry.cpp" "scene/component/Transform3D.h" 
    "renderer/interface/RenderDevice.h"
    "renderer/interface/Display.h" "scene/quadtree/QuadTree.h" "scene/component/Box2D.h"
    "scene/quadtree/QuadTree.cpp" "scene/SceneManager.h" "scene/Scene.h" 
     "renderer/interface/DisplayInfo.h" "core/system/timer.h" "core/engine/Config.h" "core/rtl/variant.h" "core/engine/Config.cpp" "core/system/profiler.h" "core/system/profiler.cpp")


##########################
###### Graphics API ######
##########################

target_include_directories(radium-engine PUBLIC "./" "./thirdparty/glm-1.0.1/" ${ADDITIONAL_INCLUDES})
if(WIN32)
    target_link_libraries(radium-engine ${GRAPHICS_API_LIBS})
endif()


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

