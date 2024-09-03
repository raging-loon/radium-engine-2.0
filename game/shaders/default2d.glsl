// !section VS

#version 460

layout (location = 0) in vec2 iPosition;
layout (location = 1) in vec2 iTexCoords;

out vec2 texCoords;

void main()
{
    gl_Position = vec4(iPosition, 0.0f,1.0f);
    texCoords = iTexCoords;
}
// !endsection

// !section PS
#version 460

uniform sampler2D tex;

in vec2 texCoords;

out vec4 FragColor;
void main()
{
    FragColor = texture(tex, texCoords);
}
// !endsection