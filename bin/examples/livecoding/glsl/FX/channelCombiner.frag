#version 120

varying vec3 v;
varying vec3 N;

uniform sampler2DRect tex0;
uniform sampler2DRect tex1;
uniform sampler2DRect tex2;
uniform sampler2DRect tex3;

void main(void){
	vec2 st = gl_TexCoord[0].st;

	float r = texture2DRect(tex0, st).r;
	float g = texture2DRect(tex1, st).r;
	float b = texture2DRect(tex2, st).r;
	float a = texture2DRect(tex3, st).r;

	gl_FragColor = vec4(r,g,b,a);
}
