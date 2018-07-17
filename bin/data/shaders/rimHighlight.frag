#version 120

varying vec3 normal;
varying vec3 sides;
varying vec2 v_texCoord;
varying vec4 v_color;

uniform sampler2DRect tex0;

uniform vec2 resolution;
uniform float time;

void main(){
  float intensity;
  vec3 n = normalize(normal);
  vec4 color;
  intensity = dot(sides,n);

  gl_FragColor = texture2DRect(tex0, v_texCoord);
  if (intensity >= 64.0){
    gl_FragColor.b = gl_FragColor.b / 1.5;
    gl_FragColor.r = gl_FragColor.r * 1.5;
    gl_FragColor.g = gl_FragColor.g * 1.25;
  }else{
    gl_FragColor = gl_FragColor * v_color;
  }
}
