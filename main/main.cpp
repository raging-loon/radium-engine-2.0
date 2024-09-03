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
#include <renderer/interface/Interface.h>
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
    
    RenderDevice rd;
    rd.init(test.getDisplayInfo());
    test.show();

    float testVertices[] =
    {
        -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f
    };

    int testIndices[] =
    {
        0,1,2,
        2,3,0
    };

    BufferDescription b =
    {
        .type = BUFFER_TYPE_VERTEX,
        .size = sizeof(float),
        .count = sizeof(testVertices) / sizeof(float),
        .binding = 0,
        .data = testVertices
    };

    BufferDescription b2 =
    {
        .type = BUFFER_TYPE_INDEX,
        .size = sizeof(int),
        .count = sizeof(testIndices) / sizeof(int),
        .binding = 0,
        .data = testIndices
    };

    ShaderDescription sd =
    {
        .vtxEntryPoint = "VS",
        .psEntryPoint = "PS",
        .sourceFile = "../renderer/common/default.glsl",
        .shaderFlags = sd.SHADER_IN_FILE,
    };

    auto* shader = rd.createShader(sd);

    auto vbuf = rd.createBuffer(b);
    auto ibuf = rd.createBuffer(b2);

    

    while (true)
    {
        test.processEvents();
        glClearColor(0.1, 0.1, 0.1, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        rd.bindVertexArray();
        vbuf->bind();
        ibuf->bind();
        shader->bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


        rd.swapBuffers();
    }

}

  



