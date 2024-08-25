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
    Timer timer;
    timer.reset();
    timer.tick();

    radium::setSEHHandlers();

    GlobLoggers::init();
    ENGINE_INFO("hello");

    Config engineConfig;
    if (engineConfig.readConfigFromFile("engine.ini") != OK)
        printf("an errror occured\n");


    //Display test;
    //test.create(800, 600, 0, 0, "hello");

    //RenderDevice t;
    //t.init(test.getDisplayInfo());

    //ENGINE_INFO("Took %f seconds to start up    ", timer.getTotal());

    //rtl::variant < rtl::typelist<int, double, rtl::string> > m_cfgVar;

    //m_cfgVar.set<rtl::string>((const char*)"hello");

    //printf("%s\n", m_cfgVar.as < rtl::string>().c_str());
} 
  



