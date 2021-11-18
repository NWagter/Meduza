#type Vertex
#version 330 core

layout(location = 0) in vec3 a_pos;

uniform mat4 u_model;
uniform mat4 u_projectionView;

void main()
{
    gl_Position = u_projectionView * u_model * vec4(a_pos, 1.0);
}

#type Pixel
#version 330 core

uniform vec4 u_colour;

void main()
{
    gl_FragColor = u_colour;
}