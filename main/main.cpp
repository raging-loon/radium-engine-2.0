#include <core/debug/globlog.h>
#include <core/debug/seh.h>
#include <renderer/interface/RenderDevice.h>
#include <renderer/interface/Display.h>

using namespace radium; 

int main(int argc, char** argv)
{
    radium::setSEHHandlers();

    GlobLoggers::init();
    ENGINE_INFO("hello");

    Display test;
    test.create(800, 600, 0, 0, "hello");
    
    RenderDevice t;
    t.init(test.generateRDConfig());
   
} 
  



