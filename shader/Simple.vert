#version 400 core

in vec3 Color;
in vec2 Vertex;
out vec3 FragColor;
void main()
{

  FragColor = Color;
  gl_Position = vec4(Vertex,0.0,1.0);
}
