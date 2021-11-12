#type Vertex
#version 330 core

layout(location = 0) in vec3 a_pos;

uniform mat4 u_projectionView;

void main()
{
	vec4 pos = vec4(a_pos, 1);
	gl_Position = u_projectionView * pos;
}

#type Pixel
#version 330 core

uniform vec4 u_colour;

void main()
{
	gl_FragColor = u_colour;
}