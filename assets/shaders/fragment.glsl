#version 330
uniform sampler2D sprites;
in vec2 tex_pos;
out vec4 fragment;

void main()
{
  // float gamma = 2.2;
  // fragment = vec4(pow(color, vec3(1.0/gamma)), 1.0);
  fragment = texture(sprites, tex_pos);
}
