#include <core/debug/globlog.h>
#include <core/debug/seh.h>
#include <renderer/interface/RenderDevice.h>
#include <renderer/interface/Display.h>
#include <core/system/timer.h>
using namespace radium; 

int main(int argc, char** argv)
{
    Timer timer;
    timer.reset();
    timer.tick();

    radium::setSEHHandlers();

    GlobLoggers::init();
    ENGINE_INFO("hello");



    Display test;
    test.create(800, 600, 0, 0, "hello");
    
    RenderDevice t;
    t.init(test.getDisplayInfo());

    ENGINE_INFO("Took %f seconds to start up",timer.getTotal());
   
} 
  



