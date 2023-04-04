#version 330 core

out vec4 fragColor;

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

uniform sampler2D colorTexture;
uniform sampler2D positionTexture;
uniform sampler2D normalTexture;

in vec2 texCoord;

void main()
{
    vec3 color = texture(colorTexture, texCoord).xyz;
    vec3 position = texture(positionTexture, texCoord).xyz;
    vec3 normal = texture(normalTexture, texCoord).xyz;

    vec3 lightDirection = normalize(vec3(0.0, 0.0, 1.0));
    vec3 viewDirection = normalize(camera.position - position);
    vec3 halfDirection = normalize(lightDirection + viewDirection);

    float diffuse = max(dot(normal, lightDirection), 0.0);
    float specular = pow(max(dot(normal, halfDirection), 0.0), shininess);

    fragColor = vec4(color, 1.0);
}