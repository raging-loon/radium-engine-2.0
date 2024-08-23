#include <core/debug/globlog.h>
#include <core/debug/seh.h>
#include <renderer/interface/Display.h>
using namespace radium; 

int main(int argc, char** argv)
{
    radium::setSEHHandlers();

    GlobLoggers::init();
    ENGINE_INFO("hello");

    //Display t;
    //t.create(100, 100, 0, 0, "niga");
    //t.show();
    //while (true) t.processEvents();
    //t.destroy();


} 
  



