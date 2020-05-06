#type Vertex
#version 330 core

layout(location = 0) in vec3 a_pos;

uniform mat4 u_viewProjection;

uniform vec4 u_colour;
uniform vec3 u_position;
uniform vec3 u_size;

out vec4 v_colour;

void main()
{
    v_colour = u_colour;

    vec3 pos = a_pos + u_position;
    pos = pos * u_size;

    gl_Position = u_viewProjection * vec4(pos.x, pos.y, pos.z, 1.0);
}


#type Pixel
#version 330 core

out vec4 FinalColour;
in vec4 v_colour;

void main()
{
    FinalColour = v_colour;
}
