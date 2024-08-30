#include "ResourceManager.h"

#include <stb_image.h>

using radium::ResourceManager;
using radium::Status;

Status ResourceManager::init()
{

#ifdef RADIUM_API_OPENGL
    stbi_set_flip_vertically_on_load(true);
#endif // RADIUM_API_OPENGL 

    return OK;
}