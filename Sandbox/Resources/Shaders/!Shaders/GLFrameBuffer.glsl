#type Vertex
#version 330 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texC;

out vec2 TexCoords;

void main()
{
    gl_Position = vec4(a_pos.x * 2, a_pos.y * 2, 0.0, 1.0); 
    TexCoords = vec2(a_texC.x, -a_texC.y);
}  

#type Pixel
#version 330 core

out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{ 
    FragColor = texture(screenTexture, TexCoords);
}