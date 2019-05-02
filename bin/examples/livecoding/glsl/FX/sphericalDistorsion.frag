#version 120

varying vec3 v;
varying vec3 N;

uniform sampler2DRect tex0;
uniform float param1f0;//size@
uniform float param1f1;//amount@
uniform vec2 size;

void main(void){
	vec2 st = gl_TexCoord[0].st;

	vec2 imageCenter = size / 2.;
	vec2 P = (st / imageCenter) - 1.; // to normalized image coordinates
	P /= param1f0;
	vec2 Pp = P / (1. - param1f1 * dot(P, P));
	P *= param1f0;
	st = (Pp + 1.) * imageCenter;  // back to pixel coordinates

	gl_FragColor = texture2DRect(tex0, st);
}
