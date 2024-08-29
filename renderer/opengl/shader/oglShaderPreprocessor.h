#ifndef RENDERER_OPENGL_SHADER_OGL_SHADER_PREPROCESSOR_H_
#define RENDERER_OPENGL_SHADER_OGL_SHADER_PREPROCESSOR_H_

#include <core/rtl/hash_map.h>
#include <core/rtl/string.h>
namespace radium
{

using ShaderSectionMap = rtl::unordered_map<rtl::string, rtl::string>;

///
/// @brief
///     Process shader sources based on meta-commands within them
///     
///     It is nice to have all parts of a shader in a single file.
///     Using the pre-processor, you can indicate sections of a shader source
///     These meta-commands are in the form of '// !command command args'
///     
///     If you are editing in Visual Studio, the space between '//' and '!' is important
/// 
///     The main two meta-commands are !section "name" and !endsection
///     These indicate the start and end of a certain shader, e.g. the vertex shader
/// 
///     This class will attempt to parse your shader code and return a map of 
///     each section to its corresponding source code
/// 
///     Example of meta-commands
///     
///     @code
///     // !section VS
///     // this is our vertex shader
///     
///     layout ...
///     out vec4 ...
///     void main()
///     {
///         // do some fancy stuff
///     }
///     
///     // !endsection
/// 
///     // !section PS
///     // this is our pixel/fragment shader
///     in vec4 ...
///     void main()
///     {
///         // super fancy lighting
///         FragColor = ...
///     }
///     // !endsection
///     @endcode
/// 
class oglShaderPreprocessor
{
public:

    oglShaderPreprocessor(const rtl::string& source) : m_position(0)
    {
        m_source = source;
    }

    oglShaderPreprocessor() : m_position(0) {}

    void setSource(const rtl::string& source) { m_source = source; }

    rtl::string extractSection(const char* name);

private:
    U32 m_position;
    rtl::string m_source;
    
};

} // radium


#endif // RENDERER_OPENGL_SHADER_OGL_SHADER_PREPROCESSOR_H_