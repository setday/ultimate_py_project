#version 330 core

in vec3 vertexPosition;
in vec3 vertexNormal;

out vec4 fragmentColor;

struct Camera {
    vec3 position;
    vec3 direction;
    vec3 up;
};

uniform Camera camera;

uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform float shininess;

layout(location = 0) out vec4 colorTexture;
layout(location = 1) out vec4 positionTexture;
layout(location = 2) out vec4 normalTexture;

void main()
{
    vec3 normal = normalize(vertexNormal);
    vec3 viewDirection = normalize(camera.direction);
    vec3 lightDirection = normalize(vec3(0.0, -1.0, 0.0));
    vec3 reflectDirection = reflect(lightDirection, normal);

    // vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 lightColor = vec3(1.0, 0.8, 0.6);

    float diffuse = max(dot(normal, -lightDirection), 0.0);
    float specular = pow(max(dot(-viewDirection, reflectDirection), 0.01), shininess);

    vec3 color = ambientColor + (diffuseColor * diffuse + specularColor * specular) * lightColor;

    colorTexture = vec4(color, 1.0);
    positionTexture = vec4(vertexPosition, 1);
    normalTexture = vec4(vertexNormal, 1);
}