#include "oglShaderFactory.h"

#include <core/error.h>
#include <core/io/file.h>
#include <core/debug/globlog.h>
using radium::Status;
using radium::ShaderDescription;
using radium::oglShaderFactory;

GLuint oglShaderFactory::createShaderProgram(ShaderDescription& sd)
{
    if ((sd.shaderFlags & sd.SHADER_IN_FILE) == sd.SHADER_IN_FILE)
        return compileShaderFromFile(sd);
}


GLuint oglShaderFactory::compileShaderFromFile(ShaderDescription& sd)
{
    rtl::string source;
    rtl::string vertexSource;
    rtl::string pixelSource;

    Status readStat = openShaderSource(sd.sourceFile, source);

    if (readStat != OK)
    {
        ENGINE_ERROR("Failed to open source file at %s", sd.sourceFile);
        return GL_INVALID_VALUE;
    }

    vertexSource = m_preprocessor.extractSection(sd.vtxEntryPoint);
    pixelSource  = m_preprocessor.extractSection(sd.psEntryPoint);

    if (vertexSource.length() == 0)
    {
        ENGINE_ERROR("Failed to find section \"%s\" in shader source '%s'.", sd.vtxEntryPoint, sd.sourceFile);
        return GL_INVALID_VALUE;
    }

    if (pixelSource.length() == 0)
    {
        ENGINE_ERROR("Failed to find section \"%s\" in shader source '%s'.", sd.psEntryPoint, sd.sourceFile);
        return GL_INVALID_VALUE;
    }

    GLuint vs = createShader(vertexSource, nullptr, vertexSource.length(), GL_VERTEX_SHADER);
    GLuint ps = createShader(pixelSource, nullptr, pixelSource.length(), GL_FRAGMENT_SHADER);

    if (ps == GL_INVALID_VALUE)
    {
        ENGINE_ERROR("Failed to compile shader section %s in file %s", sd.psEntryPoint, sd.sourceFile);
        return GL_INVALID_VALUE;
    }

    if (vs == GL_INVALID_VALUE)
    {
        ENGINE_ERROR("Failed to compile shader section %s in file %s", sd.vtxEntryPoint, sd.sourceFile);
        return GL_INVALID_VALUE;
    }

    return linkShader(vs, ps);
}

Status oglShaderFactory::openShaderSource(const char* filename, rtl::string& out)
{
    File sourceFile;
    
    Status stat = sourceFile.open(filename, File::READ);
    
    if (stat != OK)
        return stat;

    size_t sourceSz = sourceFile.getSize();

    // +2 to end of file + null terminator
    out.resize(sourceSz + 2);

    sourceFile.read(out.data(), sourceSz);

    out.setPos(sourceSz + 1);
    out += '\0';

    m_preprocessor.setSource(out);
    return OK;
}

GLuint oglShaderFactory::createShader(const rtl::string& source, const char* entryPoint, size_t size, GLenum shaderType)
{
    assert(shaderType == GL_VERTEX_SHADER || shaderType == GL_FRAGMENT_SHADER);

    GLuint sid = glCreateShader(shaderType);
    const char* src = source.c_str();

    glShaderSource(sid, 1, (const GLchar**)(&src), (const GLint*)(&size));
    
    glCompileShader(sid);

    if (checkShaderCompilerError(sid, shaderType))
    {
        glDeleteShader(sid);
        return GL_INVALID_VALUE;
    }

    return sid;
}

bool oglShaderFactory::checkShaderCompilerError(GLuint id, GLenum type)
{
    char errorBuffer[256];

    int compileStatus = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compileStatus);

    if (compileStatus == GL_TRUE)
        return false;
    else
    {
        int len = -1;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        glGetShaderInfoLog(id, sizeof(errorBuffer), &len, errorBuffer);

        const char* typeStr = type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT";
        ENGINE_ERROR("Failed to compile %s shader: %s",typeStr, errorBuffer);
        return true;
    }

}

bool oglShaderFactory::checkLinkageError(GLuint program)
{
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if (status == GL_FALSE)
    {
        ENGINE_ERROR("Failed to link shader");
        return true;
    }

    glValidateProgram(program);

    glGetProgramiv(program, GL_VALIDATE_STATUS, &status);

    if (status == GL_FALSE)
    {
        ENGINE_ERROR("Failed to validate shader");
        return true;
    }

    return false;
}

GLuint oglShaderFactory::linkShader(GLuint vs, GLuint ps)
{
    GLuint shaderProgramID = glCreateProgram();

    glAttachShader(shaderProgramID, vs);
    glAttachShader(shaderProgramID, ps);

    glLinkProgram(shaderProgramID);

    glDeleteShader(vs);
    glDeleteShader(ps);

    if (checkLinkageError(shaderProgramID))
    {
        glDeleteProgram(shaderProgramID);
        return GL_INVALID_VALUE;
    }

    return shaderProgramID;
}
