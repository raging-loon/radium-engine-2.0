#include <core/debug/globlog.h>
#include <core/debug/seh.h>
#include <renderer/interface/RenderDevice.h>
#include <renderer/interface/Display.h>
#include <core/engine/Config.h>
#include <core/io/file.h>
#include <resmgr/ResourceManager.h>
#include <resmgr/types/Image.h>
#include <core/rtl/hash_map.h>
#include <core/rtl/utility.h>
using namespace radium; 

int main(int argc, char** argv)
{
    radium::setSEHHandlers();

    GlobLoggers::init();


    //Config engineConfig;
    //if (engineConfig.readConfigFromFile("engine.ini") != OK)
    //    printf("an errror occured\n");

    //Display test;
    //test.create(800, 600, engineConfig["title"]);
    //
    //RenderDevice t;
    //t.init(test.getDisplayInfo());
    ResMgr::get().init();
     
     auto x = ResourceManager::get().loadResource<Image>("../game/res/20240101183819_1.jpg");
    auto s = ResourceManager::get().loadResource<Image>("../logo.png"); 
    auto v = ResourceManager::get().loadResource<Image>("../game/res/20240101183819_1thumbnail (2).jpg");
    ResourceManager::get().loadResource<Image>("../game/res/20240101183819_1thumbnail (3).jpg");
    auto t5= ResourceManager::get().loadResource<Image>("../game/res/20240101183819_1thumbnail (4).jpg");
    printf("0x%0X -> %d\n", x->getResourceID(), x.reference_count());
    printf("0x%0X -> %d\n", s->getResourceID(), s.reference_count());
    printf("0x%0X -> %d\n", v->getResourceID(), v.reference_count());
    ResMgr::get().terminate();
}

  



