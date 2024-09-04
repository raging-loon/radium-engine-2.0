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
#include <renderer/interface/Texture.h>
using namespace radium; 

int main(int argc, char** argv)
{
    radium::setSEHHandlers();

    GlobLoggers::init();
    ResMgr::get().init();

    Config engineConfig;
    if (engineConfig.readConfigFromFile("engine.ini") != OK)
        printf("an errror occured\n");

    Display test;
    test.create(800, 600, engineConfig["title"]);
    
    RenderDevice rd;
    rd.init(test.getDisplayInfo());
    test.show();


    auto myImage = ResMgr::get().loadResource<Image>("../game/res/20240101183819_1thumbnail.jpg");

    float testVertices[] =
    {
        -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f
    };

    float testVertices2[] =
    {
        -0.5f,  0.1f, 0.0f, 0.0f, 0.0f, 0.0f,
         0.5f,  0.2f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.5f, -0.3f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.4f, 0.0f, 0.0f, 0.0f, 1.0f
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

    Layout _2d_layout[2] = {
            {3, 0, sizeof(Vertex)},
            {3, offsetof(Vertex, texCoord), sizeof(Vertex)},
    };


    ShaderDescription sd =
    {
        .vtxEntryPoint = "VS",
        .psEntryPoint = "PS",
        .sourceFile = "../game/shaders/default.glsl",
        .shaderInputLayout = _2d_layout,
        .numLayouts = 2,
        .shaderFlags = sd.SHADER_IN_FILE,
    };

    TextureDescription td =
    {
        .data = myImage->getImageData(),
        .height = myImage->getHeight(),
        .width = myImage->getWidth()

    };

    auto* tex = rd.createTexture(td);
    auto vbuf = rd.createBuffer(b);
    auto ibuf = rd.createBuffer(b2);
    vbuf->bind();
    auto* shader = rd.createShader(sd);
    shader->bind();
    b.data = testVertices2;
    auto vbuf2 = rd.createBuffer(b);
    auto ibuf2 = rd.createBuffer(b2);

    while (!(GetKeyState(VK_SPACE) & 0x8000))
    {
        test.processEvents();
        glClearColor(0.1, 0.1, 0.1, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /*    vbuf->bind();
        ibuf->bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);*/

        vbuf2->bind();
        ibuf2->bind();
        shader->bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(int)));

        rd.swapBuffers();
    }


    ResMgr::get().terminate();


}

  



