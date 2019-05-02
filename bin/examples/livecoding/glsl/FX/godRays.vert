#version 120

varying vec3 v;
varying vec3 N;

void main(){
  gl_TexCoord[0] = gl_MultiTexCoord0;
  gl_FrontColor = gl_Color;
  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
