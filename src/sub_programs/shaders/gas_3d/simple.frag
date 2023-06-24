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

uniform sampler3D tex0;
uniform sampler3D tex1;

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
    vec3 color = ambientColor * 0.8;

    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    // vec3 lightColor = vec3(1.0, 0.8, 0.6);

    vec3 normal = normalize(vertexNormal);
    vec3 viewDirection = normalize(camera.direction);

    vec3 lightPosition = vec3(0.0, 0.0, -4.0);

    vec3 lightDirection = normalize(vec3(0.0, -1.0, 0.0));
    vec3 reflectDirection = reflect(lightDirection, normal);

    float diffuse = max(dot(normal, -lightDirection), 0.0);
    float specular = pow(max(dot(-viewDirection, reflectDirection), 0.01), shininess);

    // color += (diffuseColor * diffuse + specularColor * specular) * lightColor;

    float extraIntensity = sin(time + 17) * 0.25 + 0.25;

//    color += applyPointLight(vec3(1.0, 0.6, 1.0), vec3(6.0, 0.0, -30.0), normal, viewDirection) * extraIntensity;

    extraIntensity = sin(time + 3) * 0.25 + 0.25;

//    color += applyPointLight(vec3(1.0, 0.6, 0.6), vec3(-2.0, 0.0, -16.0), normal, viewDirection) * extraIntensity;

    extraIntensity = sin(time) * 0.25 + 0.5;

//    color += applyPointLight(lightColor, vec3(0.0, 0.0, -4.0), normal, viewDirection) * extraIntensity;

    color += applyDirectionalLight(lightColor, lightDirection, normal, viewDirection);
    lightDirection = normalize(vec3(0.0, -1.0, -1.0));
    color += applyDirectionalLight(lightColor, lightDirection, normal, viewDirection);
    lightDirection = normalize(vec3(-1.0, -1.0, -1.0));
    color += applyDirectionalLight(lightColor, lightDirection, normal, viewDirection);

    if (isEmitter == 1) {
        color = diffuseColor;
    }

    if (texturesCount > 0) {
        vec3 texCoords = realVertexPosition + vec3(5.5, 5.5, 25.5);
        texCoords = texCoords / 10.0;
        colorTexture = vec4(texture(tex0, texCoords).rrr, 0.5);
    } else {
        colorTexture = vec4(color, 0.5);
    }

    positionTexture = vec4(vertexPosition, 1);
    normalTexture = vec4(vertexNormal, 1);

    color = vec3(0.1, 0.1, 0.1);

    int steps = 256;
    float stepSize = 100.0 / float(steps);
    float delta = 1.0 / float(steps);

    // volume ray marching

    vec3 rayOrigin = realVertexPosition + vec3(5.5, 5.5, 25.5);
    vec3 rayDirection = -normalize(camera.position - realVertexPosition);

    float alpha = 0.0;

    vec3 p = rayOrigin;

    for (int i = 0; i < steps; i++) {
        p += rayDirection * stepSize;
        float d = texture(tex0, p / 10.0).r * stepSize * (1.0 - alpha);
        color += texture(tex1, p / 10.0).rgb * d;
        alpha += d;
    }

    alpha = clamp(alpha, 0.0, 1.0);

    colorTexture = vec4(color, alpha);
}
