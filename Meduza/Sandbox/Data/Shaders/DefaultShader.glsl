#type Vertex
#version 330 core

layout(location = 0) in vec3 a_pos;

uniform vec4 u_colour;
uniform vec3 u_position;

out vec4 v_colour;

void main()
{
    v_colour = u_colour;

    gl_Position = vec4(a_pos.x + u_position.x, a_pos.y + u_position.y, a_pos.z + u_position.z, 1.0);
}


#type Pixel
#version 330 core

out vec4 FinalColour;
in vec4 v_colour;

void main()
{
    FinalColour = v_colour;
}
