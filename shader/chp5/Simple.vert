#version 400 core

in vec3 Color;
in vec3 Vertex;
out vec3 FragColor;

uniform mat4 modelViewProjectionMatrix;

void main()
{

  FragColor = Color;
  gl_Position = modelViewProjectionMatrix*vec4(Vertex,1.0);
}
