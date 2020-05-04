#type Vertex
#version 330 core

layout (location = 0) in vec3 aPos;

void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}


#type Pixel
#version 330 core

out vec4 FragColor;

void main()
{
   FragColor = vec4(1.0f, 0.f, 0.f, 1.0f);
}