#version 120

varying vec3 normal;
varying vec3 sides;
varying vec2 v_texCoord;
varying vec4 v_color;

void main(){
  normal = gl_NormalMatrix * gl_Normal;
  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
  sides = gl_Position.xyz;
  sides.x = sides.x - 128.0;

  v_texCoord = vec2(gl_MultiTexCoord0);
  v_color = gl_Color;
}
