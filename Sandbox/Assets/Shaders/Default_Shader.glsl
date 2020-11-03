#type Vertex
#version 140
#extension GL_ARB_explicit_attrib_location : require
#extension GL_ARB_explicit_uniform_location : require

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec2 a_textC;

void main()
{
    gl_Position = vec4(a_pos.x, a_pos.y, a_pos.z, 1.0);
}

#type Pixel
#version 140

void main()
{
    gl_FragColor = vec4(0.0, 1.0, 0.1, 1.0);
}