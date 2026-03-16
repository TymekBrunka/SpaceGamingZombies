#version 330
uniform sampler2D sprites;
uniform vec2 pixelSize;

in mat4 transforms;
in vec4 tex_cords;
in vec2 sprite_size;

in vec2 shape_pos;
in vec2 shape_tex_pos;
#define stp shape_tex_pos

out vec2 tex_pos;

void main()
{
  gl_Position = transforms * vec4(vec2(shape_pos.x * sprite_size.x, shape_pos.y * sprite_size.y), 1.0, 1.0);
  gl_Position.x *= pixelSize.x;
  gl_Position.y *= pixelSize.y;
  gl_Position.zw = vec2(1.0);
  tex_pos.x = tex_cords.b * stp.x + tex_cords.r * (1.0 - stp.x);
  tex_pos.y = tex_cords.a * stp.y + tex_cords.g * (1.0 - stp.y);
}
