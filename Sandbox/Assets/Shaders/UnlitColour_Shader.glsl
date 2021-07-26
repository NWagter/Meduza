#type Vertex
#version 140
#extension GL_ARB_explicit_attrib_location : require
#extension GL_ARB_explicit_uniform_location : require

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_normals;
layout(location = 2) in vec2 a_textC;

uniform mat4 u_model;
uniform mat4 u_projection;

out vec2 textC;

void main()
{
    textC = a_textC;

    gl_Position = vec4(a_pos, 1.0);
}

#type Pixel
#version 140

in vec2 textC;
uniform sampler2D u_texture;
uniform vec4 u_colour;

void main()
{
    gl_FragColor = u_colour;
}