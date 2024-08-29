// !section VS

#version 460

layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec3 iColor;

out vec4 color;

void main()
{
    gl_Position = vec4(iPosition,1.0f);
    color = vec4(iColor, 1.0f);
}
// !endsection

// !section PS
#version 460


in vec4 color;

void main()
{
    FragColor = color;
}
// !endsection