#version 150

uniform sampler2D uTexture;
uniform vec3 uLuminance;
uniform vec3 uGamma;
uniform vec4 uEdges;
uniform vec4 uCorners;
uniform float uExponent;

in vec2 vTexCoord;
in vec4 vColor;

out vec4 fragColor;

float map(in float value, in float inMin, in float inMax, in float outMin, in float outMax)
{
  return outMin + (outMax - outMin) * (value - inMin) / (inMax - inMin);
}

void main(void)
{
	vec4 texColor = texture(uTexture, vTexCoord);

	vec2 mapCoord = vec2(map(vTexCoord.x, uCorners.x, uCorners.z, 0.0, 1.0), map(vTexCoord.y, uCorners.y, uCorners.w, 0.0, 1.0));

	float a = 1.0;
	if (uEdges.x > 0.0) a *= clamp(mapCoord.x / uEdges.x, 0.0, 1.0);
	if (uEdges.y > 0.0) a *= clamp(mapCoord.y / uEdges.y, 0.0, 1.0);
	if (uEdges.z > 0.0) a *= clamp((1.0 - mapCoord.x) / uEdges.z, 0.0, 1.0);
	if (uEdges.w > 0.0) a *= clamp((1.0 - mapCoord.y) / uEdges.w, 0.0, 1.0);

	const vec3 one = vec3(1.0);
	vec3 blend = (a < 0.5) ? (uLuminance * pow(2.0 * a, uExponent)) : one - (one - uLuminance) * pow(2.0 * (1.0 - a), uExponent);

	texColor.rgb *= pow(blend, one / uGamma);

	fragColor = texColor * vColor;
}
