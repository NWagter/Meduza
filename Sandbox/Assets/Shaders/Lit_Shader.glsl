#type Vertex
#version 330 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texC;

uniform mat4 u_model;
uniform mat4 u_projectionView;

out vec2 texC;
out vec3 normal;

void main()
{
    vec3 fragPos = vec3(u_model * vec4(a_pos, 1.0));
    gl_Position = u_projectionView * vec4(fragPos, 1.0);

    texC = a_texC;
    normal = mat3(transpose(inverse(u_model))) * a_normal;
}

#type Pixel
#version 330 core

in vec2 texC;
in vec3 normal;

uniform vec4 u_colour;
uniform sampler2D u_texture;

void main()
{
    vec4 c = texture(u_texture, texC) * u_colour;

    vec3 ambient = vec3(0.4f, 0.4f, 0.4f) * c.xyz;
    vec3 N = normalize(normal);

    vec3 light = vec3(1,0,-1);
    vec3 lightDir = normalize(light);   

    float diff = max(dot(N, lightDir), 0.0f);
    vec3 diffuse = vec3(0.8f, 0.8f, 0.8f) * diff * (c.xyz);

    gl_FragColor = vec4(ambient + diffuse, c.w);
}