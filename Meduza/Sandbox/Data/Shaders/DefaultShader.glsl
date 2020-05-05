#type Vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 a_textureCoords;

out vec2 v_textureCoords;

uniform vec4 u_textureSpace;

void main()
{

    vec2 uv = vec2(gl_VertexID & 1, (gl_VertexID >> 1) & 1);

    v_textureCoords =
        vec2(u_textureSpace.x + (u_textureSpace.z * uv.x),
            u_textureSpace.y + (u_textureSpace.w * uv.y));

    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}


#type Pixel
#version 330 core

out vec4 colour;

in vec2 v_textureCoords;

uniform sampler2D u_texture;

void main()
{
   colour = texture(u_texture, v_textureCoords);
}