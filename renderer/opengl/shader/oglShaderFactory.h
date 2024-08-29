#ifndef RENDERER_OPENGL_SHADER_OHL_SHADER_FACTORY_H_
#define RENDERER_OPENGL_SHADER_OHL_SHADER_FACTORY_H_

#include "oglShader.h"
#include "oglShaderPreprocessor.h"
#include <renderer/interface/ShaderProgram.h>
#include <core/rtl/string.h>
#include <GL/glew.h>
namespace radium
{

class oglShaderFactory
{
public:

    ///
    /// @brief
    ///     Compile and Link shaders as descriped in the ShaderDescription
    /// 
    /// @returns
    ///     -1 on failure
    GLuint createShaderProgram(ShaderDescription& sd);


    GLuint compileShaderFromFile(ShaderDescription& sd);

    GLuint compileShaderFromMemory(ShaderDescription& sd);
private:

    ///
    /// @brief
    ///     Open a shader source file
    ///         
    ///     The shader will be returned via the out parameter
    /// @returns
    ///     OK on success
    /// 
    Status openShaderSource(const char* filename, rtl::string& out);

    ///
    /// @brief
    ///     Compile a single shader
    /// 
    /// @returns
    ///     -1 on failure
    GLuint createShader(const rtl::string& source, const char* entryPoint, size_t size, GLenum shaderType);

    bool checkShaderCompilerError(GLuint id, GLenum type);
    bool checkLinkageError(GLuint program);

    GLuint linkShader(GLuint vs, GLuint ps);
private:
    /// preprocesses shader sources
    oglShaderPreprocessor m_preprocessor;
};


} // radium

#endif // RENDERER_OPENGL_SHADER_OHL_SHADER_FACTORY_H_