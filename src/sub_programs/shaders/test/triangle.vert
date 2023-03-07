#version 330 core

layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 aNorm;
// layout (location = 3) in vec4 aColor;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

uniform vec3 cameraPosition;
uniform vec3 cameraDirection;
uniform vec3 cameraUp;

uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform float shininess;

out vec4 vertexNormal;
out vec2 screenCoords;

out vec3 fragAmbientColor;
out vec3 fragDiffuseColor;
out vec3 fragSpecularColor;
out float fragShininess;

out vec3 fragCameraDirection;

mat4 makeViewMatrix(vec3 pos, vec3 direction, vec3 up)
{
  vec3 backward = direction;
  vec3 right = normalize(cross(up, backward));
  vec3 upward = cross(backward, right);

  mat4 view = mat4(
    vec4(         right.x,          upward.x,          backward.x, 0.0),
    vec4(         right.y,          upward.y,          backward.y, 0.0),
    vec4(         right.z,          upward.z,          backward.z, 0.0),
    vec4(-dot(right, pos), -dot(upward, pos), -dot(backward, pos), 1.0)
  );

  return view;
}

void main()
{
  mat4 viewMatrix = makeViewMatrix(cameraPosition, cameraDirection, cameraUp);

  gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
  vertexNormal = modelMatrix * vec4(aNorm, 0.0);

  fragCameraDirection = cameraDirection;

  fragAmbientColor = ambientColor;
  fragDiffuseColor = diffuseColor;
  fragSpecularColor = specularColor;
  fragShininess = shininess;
}
