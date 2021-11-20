#type Vertex
#version 330 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texC;

layout(location = 3) in mat4 a_model;
layout(location = 7) in vec4 a_colour;
layout(location = 8) in vec4 a_uv;

uniform mat4 u_projectionView;

out vec4 colour;
out vec2 texC;

void main()
{
    gl_Position = u_projectionView * a_model * vec4(a_pos, 1.0);

    vec2 tCoord = vec2(a_uv.x + (a_uv.z * a_texC.x),
                        a_uv.y + (a_uv.w * a_texC.y));
    texC = tCoord;
    colour = a_colour;
}

#type Pixel
#version 330 core

in vec4 colour;
in vec2 texC;

uniform sampler2D u_texture;

void main()
{
    gl_FragColor = texture(u_texture, texC) * colour;
}