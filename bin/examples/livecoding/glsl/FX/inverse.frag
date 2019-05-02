#version 120

varying vec3 v;
varying vec3 N;

uniform sampler2DRect tex0;

void main(){
	vec4 color = texture2DRect(tex0,gl_TexCoord[0].st);
	gl_FragColor = vec4( vec3(1.0,1.0,1.0) - color.rgb, 1.0);
}
