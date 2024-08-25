#include <core/debug/globlog.h>
#include <core/debug/seh.h>
#include <renderer/interface/RenderDevice.h>
#include <renderer/interface/Display.h>
#include <core/system/timer.h>
#include <core/rtl/variant.h>
#include <core/engine/Config.h>
using namespace radium; 

int main(int argc, char** argv)
{
    
    radium::setSEHHandlers();

    GlobLoggers::init();

    Timer ct;
    ct.reset();
    ct.tick();
    Config engineConfig;
    if (engineConfig.readConfigFromFile("engine.ini") != OK)
        printf("an errror occured\n");
    ct.tick();
    
    ENGINE_INFO("Took %f seconds to parse config", ct.getTotal());


    Display test;
    test.create(800, 600, 0, 0, engineConfig["title"]);
    Timer timer;
    timer.reset();
    timer.tick();

    RenderDevice t;
    t.init(test.getDisplayInfo());
    timer.tick();

    ENGINE_INFO("Took %f seconds to start up    ", timer.getTotal());


} 
  



