#version 330 core
layout (location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aUV;

uniform mat4 model;
uniform mat4 view_projection;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

void main()
{
    gl_Position = view_projection * model * vec4(aPos, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));
    TexCoord = aUV;

    Normal = mat3(transpose(inverse(model))) * aNorm;  
}