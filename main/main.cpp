#include <core/debug/globlog.h>
#include <core/debug/seh.h>
#include <renderer/interface/RenderDevice.h>
#include <renderer/interface/Display.h>
#include <core/engine/Config.h>
#include <core/io/file.h>
#include <resmgr/ResourceManager.h>
#include <resmgr/types/Image.h>
#include <core/rtl/hash_map.h>
using namespace radium; 

int main(int argc, char** argv)
{
    radium::setSEHHandlers();

    GlobLoggers::init();

    rtl::unordered_map<int, double> test;
    for (int i = 0; i < 10; i++)
    {
        test.insert({ i, (double)(i / 2) });
    }

    test.find(2)->displacement++;
    for(const auto& i: test)
        printf("%d | %d => %lf\n", i.first, i.displacement, i.second);
    printf("\n\n\n");
    int t = 1;


    printf("%d\n",test.index_of(1));
    test.erase(test.find(1));

    if (test.find(t) == test.end())
        printf("removed\n");
    t = 19;
    test.insert({ 19, 19 / 2 });
    if (test.find(t) == test.end())
        printf("not inserted\n");
    for (const auto& i : test)
        printf("%d | %d => %lf\n", i.first, i.displacement, i.second);
  /*  Config engineConfig;
    if (engineConfig.readConfigFromFile("engine.ini") != OK)
        printf("an errror occured\n");

    Display test;
    test.create(800, 600, engineConfig["title"]);
    
    RenderDevice t;
    t.init(test.getDisplayInfo());
    auto s = ResourceManager::get().loadResource<Image>("../logo.png");
    ENGINE_INFO("Loaded image : %dx%d nc: %d",s->getHeight(), s->getWidth(), s->getNumChannels());*/

}

  



