#version 330
in vec3 color;
out vec4 fragment;

void main()
{
  float gamma = 2.2;
  fragment = vec4(pow(color, vec3(1.0/gamma)), 1.0);
}
