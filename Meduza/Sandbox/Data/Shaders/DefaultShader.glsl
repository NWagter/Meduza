#type Vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 a_textureCoords;

out vec2 v_textureCoords;

void main()
{
    v_textureCoords = a_textureCoords;
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