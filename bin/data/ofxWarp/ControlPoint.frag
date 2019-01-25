#version 120

varying vec3 v;
varying vec3 N;

varying vec2 vTexCoord;
varying vec4 vColor;

void main(void) {

	vec2 coord = gl_TexCoord[0].st;
	vec2 uv = coord * 2.0 - 1.0;
	float d = dot(uv, uv);
	float rim = smoothstep(0.7, 0.8, d);
	rim += smoothstep(0.3, 0.4, d) - smoothstep(0.5, 0.6, d);
	rim += smoothstep(0.1, 0.0, d);
	gl_FragColor = mix(vec4( 0.0, 0.0, 0.0, 0.25), vColor, rim);

}
