#version 120

varying vec3 v;
varying vec3 N;

uniform sampler2DRect tex0;
uniform float param1f0;//gamma@

void main(void){
	vec2 st = gl_TexCoord[0].st;
	vec4 color = texture2DRect(tex0, st);

	float gammaCorrection = 1.0 / (param1f0/3.0);
	color.rgb = 1.0 * pow(color.rgb / vec3(1.0), vec3(gammaCorrection));


	gl_FragColor = color;
}
