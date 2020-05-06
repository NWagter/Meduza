#type Vertex
#version 330 core

layout(location = 0) in vec3 a_pos;

uniform mat4 u_viewProjection;
uniform vec4 u_textureSpace;
uniform vec4 u_colour;
uniform vec3 u_position;
uniform vec3 u_size;

out vec4 v_colour;
out vec2 v_textureCoords;

void main()
{
    v_colour = u_colour;

    vec2 uv = vec2(gl_VertexID & 1, (gl_VertexID >> 1) & 1);

    v_textureCoords =
        vec2(u_textureSpace.x + (u_textureSpace.z * uv.x),
            u_textureSpace.y + (u_textureSpace.w * uv.y));

    vec3 pos = a_pos + u_position;
    pos = pos * u_size;

    gl_Position = u_viewProjection * vec4(pos.x, pos.y, pos.z, 1.0);
}


#type Pixel
#version 330 core

out vec4 FinalColour;
in vec4 v_colour;

in vec2 v_textureCoords;

uniform sampler2D u_texture;

void main()
{
    FinalColour = texture(u_texture, v_textureCoords) * v_colour;
}