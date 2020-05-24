#type Vertex
#version 330 core

layout(location = 0) in vec3 a_pos;

layout(location = 1) in vec4 a_texture;
layout(location = 2) in vec4 a_colour;
layout(location = 3) in vec3 a_postion;
layout(location = 4) in vec3 a_size;
layout(location = 5) in float a_textureID;

uniform mat4 u_viewProjection;

out vec4 v_colour;
out vec2 v_textureCoords;
out float v_textureID;

void main()
{
    v_colour = a_colour;
    v_textureID = a_textureID;
    vec2 uv = vec2(gl_VertexID & 1, (gl_VertexID >> 1) & 1);

    v_textureCoords =
        vec2(a_texture.x + (a_texture.z * uv.x),
            a_texture.y + (a_texture.w * uv.y));

    vec3 pos = a_pos * a_size;

    gl_Position = u_viewProjection * vec4(pos.x + a_postion.x, pos.y + a_postion.y, pos.z + a_postion.z, 1.0);
}


#type Pixel
#version 330 core

out vec4 FinalColour;
in vec4 v_colour;

in vec2 v_textureCoords;
in float v_textureID;

uniform sampler2D u_texture[16];

void main()
{
    int id = int(v_textureID);
    FinalColour = texture(u_texture[id], v_textureCoords) * v_colour;
}