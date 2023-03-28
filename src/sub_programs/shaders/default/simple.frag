#version 330 core

in vec4 vertexNormal;

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

out vec4 FragColor;

void main()
{
    vec3 normal = normalize(vertexNormal.xyz);
    vec3 viewDirection = normalize(camera.direction);
    vec3 lightDirection = normalize(vec3(0.0, -1.0, 0.0));
    vec3 reflectDirection = reflect(lightDirection, normal);

    // vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 lightColor = vec3(1.0, 0.8, 0.6);

    float diffuse = max(dot(normal, -lightDirection), 0.0);
    float specular = pow(max(dot(-viewDirection, reflectDirection), 0.0), shininess);

    vec3 color = ambientColor + (diffuseColor * diffuse + specularColor * specular) * lightColor;

    FragColor = vec4(color, 1.0);
}