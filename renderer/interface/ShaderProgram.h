#ifndef RENDERER_INTERFACE_SHADER_PROGRAM_H_
#define RENDERER_INTERFACE_SHADER_PROGRAM_H_

#include <core/types.h>
namespace radium
{

struct ShaderDescription
{
    enum
    {
        SHADER_IN_FILE = (1 << 0),
        SHADER_DEBUG_MODE = (1 << 1),
        SHADER_HOT_RELOAD = (1 << 2),
        SHADER_IS_PRECOMPILED = (1 << 3),
        SHADER_IN_RES_PAK = ( 1 << 4 )
    };
    
    const char* vtxSource       {nullptr};
    const char* psSource        {nullptr};
    
    const char* vtxEntryPoint   {nullptr};
    const char* psEntryPoint    {nullptr};
    
    const char* sourceFile      {nullptr};

    VertexDescription* layout;

    U16 shaderFlags             { 0 };

};

} // radium



#endif // RENDERER_INTERFACE_SHADER_PROGRAM_H_