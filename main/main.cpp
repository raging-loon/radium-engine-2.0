#include <core/debug/globlog.h>
#include <core/debug/seh.h>
#include <renderer/interface/RenderDevice.h>
#include <renderer/interface/Display.h>
#include <core/engine/Config.h>
#include <core/io/file.h>
#include <resmgr/types/Image.h>
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

    //ShaderDescription sd
    //{
    //    .vtxEntryPoint = "VS",
    //    .psEntryPoint = "PS",
    //    .sourceFile = "D:/dev/radium-engine-2.0/renderer/common/default.glsl",
    //    .shaderFlags = sd.SHADER_IN_FILE,
    //};

    //Shader* s = t.createShader(sd);
    //if (s == nullptr)
    //{
    //    printf("failed\n");
    //} else {
    //    delete s;
    //}

    Image it;
    File imageFile;
    imageFile.open("../logo.png", File::READ);
    byte* buffer = new byte[imageFile.getSize() + 1];
    memset(buffer, 0, imageFile.getSize() + 1);
    imageFile.read(buffer, imageFile.getSize());

    if (it.load(buffer, imageFile.getSize() + 1) != RES_OK)
    {
        printf("Failed\n");
    }
    else
    {
        printf("%s: %dx%d ch: %d\n", "../logo.png", it.getHeight(), it.getWidth(), it.getNumChannels());
    }

    delete[] buffer;
}

  



