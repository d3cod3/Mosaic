#version 120

varying vec3 v;
varying vec3 N;

uniform sampler2DRect uTexture;
uniform vec3 uLuminance;
uniform vec3 uGamma;
uniform vec4 uEdges;
uniform vec4 uCorners;
uniform float uExponent;

float map(float value, float inMin, float inMax, float outMin, float outMax){
  return outMin + (outMax - outMin) * (value - inMin) / (inMax - inMin);
}

void main(void){

	vec2 coord = gl_TexCoord[0].st;
    vec4 texColor = texture2DRect(uTexture, coord);

	vec2 mapCoord = vec2(map(coord.x, uCorners.x, uCorners.z, 0.0, 1.0), map(coord.y, uCorners.y, uCorners.w, 0.0, 1.0));

	float a = 1.0;
	if (uEdges.x > 0.0) a *= clamp(mapCoord.x / uEdges.x, 0.0, 1.0);
	if (uEdges.y > 0.0) a *= clamp(mapCoord.y / uEdges.y, 0.0, 1.0);
	if (uEdges.z > 0.0) a *= clamp((1.0 - mapCoord.x) / uEdges.z, 0.0, 1.0);
	if (uEdges.w > 0.0) a *= clamp((1.0 - mapCoord.y) / uEdges.w, 0.0, 1.0);

	const vec3 one = vec3(1.0);
	vec3 blend = (a < 0.5) ? (uLuminance * pow(2.0 * a, uExponent)) : one - (one - uLuminance) * pow(2.0 * (1.0 - a), uExponent);

	texColor.rgb *= pow(blend, one / uGamma);

	gl_FragColor = texColor;
}
