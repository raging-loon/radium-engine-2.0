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

#set(API_DX11 "Use DirectX 11" OFF)
set(API_DX12 "Use DirectX 12" OFF)
set(API_OPENGL ON CACHE BOOL "Use OpenGL")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(RADIUM_DEBUG_BUILD=1)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(RADIUM_RELEASE_BUILD=1)
endif()

if(ENABLE_UNIT_TESTS)
    add_subdirectory("unittest")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/unit-test")
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")
    set(CONFIG_SOURCES
        "main/main.cpp"
     )
endif()

if(WIN32)
    add_compile_definitions(RADIUM_PLATFORM_WIN32=1)
endif()

if(API_OPENGL)
    add_compile_definitions(RADIUM_API_OPENGL=1)
endif()

if(ENABLE_PROFILER)
    add_compile_definitions(PROFILING_ENABLED=1)
endif()

# add our subdirectories
add_subdirectory(core)
add_subdirectory(scene)
add_subdirectory(platform)
add_subdirectory(renderer)
add_subdirectory(resmgr)


add_executable(radium-engine
    ${CONFIG_SOURCES}
    ${PLATFORM_SOURCES}
    ${GRAPHICS_SOURCES}
    ${CORE_SOURCES}
    ${SCENE_SOURCES}
    ${RESMGR_SOURCES}
    "scene/quadtree/QuadTree.cpp" 
     "renderer/common/vertex.cpp"
     "thirdparty/stb_image/stb_image.cpp" 
      

)


##########################
###### Graphics API ######
##########################

target_include_directories(radium-engine PUBLIC 
    "./" 
    "./thirdparty/glm-1.0.1/" 
    "./thirdparty/stb_image/" 
    ${ADDITIONAL_INCLUDES})


if(WIN32)
    target_link_libraries(radium-engine ${GRAPHICS_API_LIBS})
    if(MSVC)
        string(REGEX REPLACE "/W[1-3]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")    
    endif()
    add_compile_definitions(GLEW_STATIC=1)

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

