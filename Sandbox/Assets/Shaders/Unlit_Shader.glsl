#type Vertex
#version 330 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texC;

uniform mat4 u_model;
uniform mat4 u_projectionView;
uniform vec4 u_uv;

out vec2 texC;

void main()
{
    gl_Position = u_projectionView * u_model * vec4(a_pos, 1.0);

    vec2 tCoord = vec2(u_uv.x + (u_uv.z * a_texC.x),
			            u_uv.y + (u_uv.w * a_texC.y));
    texC = tCoord;
}

#type Pixel
#version 330 core

in vec2 texC;

uniform vec4 u_colour;
uniform sampler2D u_texture;

void main()
{
    gl_FragColor = texture(u_texture, texC) * u_colour;
}