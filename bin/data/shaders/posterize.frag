#version 120

varying vec3 v;
varying vec3 N;

uniform sampler2DRect tex0;
uniform float param1f0;//level@


void main() {
	float colorLevels = param1f0/3.0;

	vec2 uv = gl_TexCoord[0].xy;
	vec4 textureColor = texture2DRect(tex0, uv);

	gl_FragColor = floor((textureColor * colorLevels) + vec4(0.5)) / colorLevels;

}
