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

    //GlobLoggers::init();


    //Config engineConfig;
    //if (engineConfig.readConfigFromFile("engine.ini") != OK)
    //    printf("an errror occured\n");

    //Display test;
    //test.create(800, 600, engineConfig["title"]);
    //
    //RenderDevice t;
    //t.init(test.getDisplayInfo());
    ResMgr::get().init();

    auto s = ResourceManager::get().loadResource<Image>("../logo.png"); 
    auto v = ResourceManager::get().loadResource<Image>("../game/res/20240101183819_1thumbnail (2).jpg");
    auto d = ResourceManager::get().loadResource<Image>("../game/res/20240101183819_1thumbnail (3).jpg");
    auto x = ResourceManager::get().loadResource<Image>("../game/res/20240101183819_1.jpg");
    ////printf("%zd\n", ResMgr::get().getRIDRefCount(s->getResourceID()));

    ResMgr::get().terminate();
}

  



