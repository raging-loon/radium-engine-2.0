#include <core/debug/globlog.h>
#include <core/debug/seh.h>
#include <renderer/interface/RenderDevice.h>
#include <renderer/interface/Display.h>
#include <renderer/interface/Buffer.h>
#include <core/system/timer.h>
#include <core/rtl/variant.h>
#include <core/engine/Config.h>
#include <core/system/profiler.h>
#include <renderer/opengl/shader/oglShaderPreprocessor.h>
#include <chrono>
#include <core/io/file.h>
using namespace radium; 

int main(int argc, char** argv)
{
    radium::setSEHHandlers();

    GlobLoggers::init();

  /*  Config engineConfig;
    if (engineConfig.readConfigFromFile("engine.ini") != OK)
        printf("an errror occured\n");

    Display test;
    test.create(800, 600, engineConfig["title"]);
    
    RenderDevice t;*/
    //t.init(test.getDisplayInfo());
    rtl::string source;

    File s;
    s.open("D:/dev/radium-engine-2.0/renderer/common/default.glsl", File::READ);
    source.resize(s.getSize() + 1);

    s.read(source.data(), s.getSize());
    source.setPos(s.getSize() + 2);
    source += '\0';
    //printf("%s\n",source.c_str());

    oglShaderPreprocessor test2(
        source
    );

    auto i = test2.extractSection("VS");
    test2.extractSection("VS");

    printf("%s\n",i.c_str());
} 
  



