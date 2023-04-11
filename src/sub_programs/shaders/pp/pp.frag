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

    // inverse
    // fragColor = vec4(vec3(1.0 - color), 1.0);
    // grayscale
    // fragColor = vec4(vec3(dot(color, vec3(0.299, 0.587, 0.114))), 1.0);
    // color
    // fragColor = vec4(color, 1.0);

    // Kernel effects
    const float offset = 1.0 / 300.0;
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right
    );

    float kernel[9] = float[](
        1.0 / 16, 2.0 / 16, 1.0 / 16,
        2.0 / 16, 4.0 / 16, 2.0 / 16,
        1.0 / 16, 2.0 / 16, 1.0 / 16
    );

    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(colorTexture, texCoord.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
    col += sampleTex[i] * kernel[i];

    fragColor = vec4(col, 1.0);
}