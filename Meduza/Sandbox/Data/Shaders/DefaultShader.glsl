#type Vertex
#version 330 core

layout(location = 0) in vec3 a_pos;

layout(location = 1) in vec4 a_texture;
layout(location = 2) in vec4 a_colour;
layout(location = 3) in vec3 a_postion;
layout(location = 4) in vec3 a_size;

uniform mat4 u_viewProjection;

out vec4 v_colour;

void main()
{
    v_colour = a_colour;

    vec3 pos = a_pos * a_size;

    gl_Position = u_viewProjection * vec4(pos.x + a_postion.x, pos.y + a_postion.y, pos.z + a_postion.z, 1.0);
}


#type Pixel
#version 330 core

out vec4 FinalColour;
in vec4 v_colour;

void main()
{
    FinalColour = v_colour;
}
