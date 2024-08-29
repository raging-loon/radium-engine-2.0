#include <core/debug/globlog.h>
#include <core/debug/seh.h>
#include <renderer/interface/RenderDevice.h>
#include <renderer/interface/Display.h>
#include <renderer/interface/Buffer.h>
#include <core/system/timer.h>
#include <core/rtl/variant.h>
#include <core/engine/Config.h>
#include <core/system/profiler.h>
#include <renderer/opengl/shader/oglShaderFactory.h>
#include <chrono>
#include <core/io/file.h>
using namespace radium; 

int main(int argc, char** argv)
{
    radium::setSEHHandlers();

    GlobLoggers::init();

    Config engineConfig;
    if (engineConfig.readConfigFromFile("engine.ini") != OK)
        printf("an errror occured\n");

    Display test;
    test.create(800, 600, engineConfig["title"]);
    
    RenderDevice t;
    t.init(test.getDisplayInfo());

    ShaderDescription sd
    {
        .vtxEntryPoint = "VS",
        .psEntryPoint = "PS",
        .sourceFile = "D:/dev/radium-engine-2.0/renderer/common/default.glsl",
        .shaderFlags = sd.SHADER_IN_FILE,
    };

    Shader* s = t.createShader(sd);
    if (s == nullptr)
    {
        printf("failed\n");
    } else {
        delete s;
    }
}

  



