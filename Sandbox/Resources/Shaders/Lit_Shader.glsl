#type Vertex
#version 330 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texC;

layout(location = 3) in mat4 a_model;
layout(location = 7) in vec4 a_colour;
layout(location = 8) in vec4 a_uv;
layout(location = 9) in float a_textureId;

uniform mat4 u_projectionView;

out vec4 colour;
out vec3 normal;
out vec3 posW;
out vec2 texC;
out float texId;

void main()
{
    vec4 pos = a_model * vec4(a_pos, 1);
    posW = pos.xyz;
    
    gl_Position = u_projectionView * pos;

    texC = a_texC;
    normal = mat3(a_model) * a_normal;
    colour = a_colour;

    texId = a_textureId;
}

#type Pixel
#version 330 core

in vec4 colour;
in vec3 normal;
in vec3 posW;
in vec2 texC;

in float texId;

uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;

vec4 GetTexture()
{
    if (ceil(texId) == 0)
        return texture(u_texture0, texC);
    if (ceil(texId) == 1)
        return texture(u_texture1, texC);
    if (ceil(texId) == 2)
        return texture(u_texture2, texC);

    return texture(u_texture0, texC);
}

void main()
{
    vec4 c = GetTexture() * colour;

    vec3 norm = normalize(normal);

    vec3 ambient = vec3(0.4,0.4,0.4) * c.xyz;

    vec3 lightDir = normalize(vec3(1,0,-1) - posW);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(0.8,0.8,0.8);

    gl_FragColor = vec4(ambient + diffuse, 1) * c;
}