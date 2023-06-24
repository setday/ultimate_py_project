#version 330 core

in vec3 vertexPosition;
in vec3 realVertexPosition;
in vec3 vertexNormal;
in vec2 texCoords;

uniform float time;

uniform int isEmitter;

uniform struct Camera {
    vec3 position;
    vec3 direction;
    vec3 up;
} camera;

uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform float shininess;

uniform sampler2D tex0;
uniform sampler2D tex1;

uniform int texturesCount;

layout(location = 0) out vec4 colorTexture;
layout(location = 1) out vec4 positionTexture;
layout(location = 2) out vec4 normalTexture;

vec3 applyDirectionalLight(vec3 lightColor, vec3 lightDirection, vec3 normal, vec3 viewDirection)
{
    vec3 reflectDirection = reflect(lightDirection, normal);

    float diffuse = max(dot(normal, -lightDirection), 0.0);
    float specular = pow(max(dot(-viewDirection, reflectDirection), 0.01), shininess);

    return (diffuseColor * diffuse + specularColor * specular) * lightColor;
}

vec3 applyPointLight(vec3 lightColor, vec3 lightPosition, vec3 normal, vec3 viewDirection)
{
    vec3 lightDirection = normalize(lightPosition - realVertexPosition);
    vec3 reflectDirection = reflect(lightDirection, normal);

    float dist = length(lightPosition - realVertexPosition);

    float intensity = 0.7 / (1.0 + 0.1 * dist + 0.1 * pow(dist, 2.0));

    float diffuse = max(dot(normal, lightDirection), 0.0);
    float specular = 0; //pow(max(dot(-viewDirection, reflectDirection), 0.01), shininess);

    return (diffuseColor * diffuse + specularColor * specular) * lightColor * intensity;
}

void main()
{
     colorTexture = vec4(texture(tex0, texCoords).rgb, texture(tex1, texCoords).r);
//    colorTexture = vec4(texture(tex1, texCoords).rrr / 2, 1);
    positionTexture = vec4(vertexPosition, 1);
    normalTexture = vec4(vertexNormal, 1);
}
