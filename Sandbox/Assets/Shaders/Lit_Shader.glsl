#type Vertex
#version 330 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texC;

uniform mat4 u_model;
uniform mat4 u_projectionView;

out vec2 texC;
out vec3 normal;
out vec3 posW;

void main()
{
    vec4 pos = u_model * vec4(a_pos, 1);
    posW = pos.xyz;
    
    gl_Position = u_projectionView * pos;

    texC = a_texC;
    normal = mat3(u_model) * a_normal;
}

#type Pixel
#version 330 core

in vec2 texC;
in vec3 normal;
in vec3 posW;

uniform vec4 u_colour;
uniform sampler2D u_texture;

void main()
{
    vec4 c = texture(u_texture, texC) * u_colour;

    vec3 norm = normalize(normal);

    vec3 ambient = vec3(0.4,0.4,0.4) * c.xyz;

    vec3 lightDir = normalize(vec3(1,0,-1) - posW);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(0.8,0.8,0.8);

    gl_FragColor = vec4(ambient + diffuse, 1) * c;
}