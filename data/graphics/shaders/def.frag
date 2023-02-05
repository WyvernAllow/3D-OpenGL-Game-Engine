#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;  

uniform sampler2D tex;

uniform vec3 lightColor;
uniform vec3 ambientColor;
uniform vec3 lightDirection;

void main()
{
    vec3 objColor = vec3(texture(tex, TexCoord));

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-lightDirection);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambientColor + diffuse) * objColor;

    FragColor = vec4(result, 1.0);
}