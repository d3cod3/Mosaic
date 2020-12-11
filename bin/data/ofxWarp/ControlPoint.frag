#version 150

in vec2 vTexCoord;
in vec4 vColor;

out vec4 fragColor;

void main(void) 
{
	vec2 uv = vTexCoord * 2.0 - 1.0;
	float d = dot(uv, uv);
	float rim = smoothstep(0.7, 0.8, d);
	rim += smoothstep(0.3, 0.4, d) - smoothstep(0.5, 0.6, d);
	rim += smoothstep(0.1, 0.0, d);
	fragColor = mix(vec4( 0.0, 0.0, 0.0, 0.25), vColor, rim);
}
