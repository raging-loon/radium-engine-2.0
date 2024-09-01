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


    Config engineConfig;
    if (engineConfig.readConfigFromFile("engine.ini") != OK)
        printf("an errror occured\n");

    Display test;
    test.create(800, 600, engineConfig["title"]);
    
    RenderDevice t;
    t.init(test.getDisplayInfo());
    ResMgr::get().init();
    
    auto s = ResourceManager::get().loadResource<Image>("../logo.png");
    ResMgr::get().isValidResource(s->getResourceID());
    auto v = ResourceManager::get().loadResource<Image>("../logo.png");
    ENGINE_INFO("Loaded image : %dx%d nc: %d",s->getHeight(), s->getWidth(), s->getNumChannels());

    RID id = s->getResourceID();

    if (ResMgr::get().isValidResource(id))
        printf("valid\n");
    if (v.isSame(s))
        printf("yte\n");


}

  



