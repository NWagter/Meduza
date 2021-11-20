#type Vertex
#version 330 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texC;

layout(location = 3) in mat4 a_model;
layout(location = 7) in vec4 a_colour;
layout(location = 8) in vec4 a_uv;

uniform mat4 u_projectionView;

out vec4 colour;

void main()
{
    gl_Position = u_projectionView * a_model * vec4(a_pos, 1.0);
    colour = a_colour;
}

#type Pixel
#version 330 core

in vec4 colour;

void main()
{
    gl_FragColor = colour;
}