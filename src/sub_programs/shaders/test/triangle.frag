#version 330 core

in vec4 vertexNormal;

in vec3 fragCameraDirection;

in vec3 fragAmbientColor;
in vec3 fragDiffuseColor;
in vec3 fragSpecularColor;
in float fragShininess;

out vec4 FragColor;

void main()
{
    vec3 normal = normalize(vertexNormal.xyz);
    vec3 cameraDirection = normalize(fragCameraDirection);
    vec3 lightDirection = normalize(vec3(0.0, -1.0, 0.0));
    vec3 halfVector = normalize(lightDirection + cameraDirection);
    vec3 reflectDirection = reflect(lightDirection, normal);
    vec3 viewDirection = normalize(fragCameraDirection);

    float diffuse = max(dot(normal, -lightDirection), 0.0);
    float specular = pow(max(dot(viewDirection, reflectDirection), 0.0), fragShininess);

    vec3 color = fragAmbientColor + fragDiffuseColor * diffuse + fragSpecularColor * specular;

    FragColor = vec4(color, 1.0);

    // FragColor= vec4(halfVector, 1.0);
}