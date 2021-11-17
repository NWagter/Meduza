#type Vertex
#version 330 core

layout(location = 0) in vec3 a_pos;

uniform mat4 u_model;
uniform mat4 u_projectionView;
uniform float u_radius;

out vec3 o_pos;

void main()
{
	o_pos = a_pos * 2.0;
	vec4 pos = u_model * vec4(a_pos * u_radius, 1);

	gl_Position = u_projectionView * pos;
}

#type Pixel
#version 330 core

in vec3 o_pos;

uniform vec4 u_colour;
void main()
{
	float thickness = 1.0;
	float fade = 0.005;

	float distance = 1.0 - length(o_pos);

	float circle = smoothstep(0.0, fade, distance);
	circle *= smoothstep(thickness + fade, thickness, distance);

	gl_FragColor = u_colour;
	gl_FragColor.a *= circle;
}