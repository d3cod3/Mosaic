#version 120

varying vec3 v;
varying vec3 N;

uniform sampler2DRect tex0;
uniform float param1f0;//contrast@
uniform float param1f1;//bright@
uniform float param1f2;//sat@

const vec3 LumCoeff = vec3(0.2125, 0.7154, 0.0721);

void main(){

	float contrast = param1f0/3.0 + 1.0;
	float brightness = 1.0 + param1f1/5.0;
	float saturation = param1f2/5.0;

	vec4 color = texture2DRect(tex0,gl_TexCoord[0].st);

	///////////////////////////////////////////////
	// brightness, saturation, contrast
	vec3 AvgLumin = vec3(0.5, 0.5, 0.5);
	vec3 brtColor = color.rgb * brightness;
	float intensityf = dot(brtColor, LumCoeff);
	vec3 intensity = vec3(intensityf,intensityf,intensityf);
	vec3 satColor = mix(intensity, brtColor, saturation);
	vec3 conColor = mix(AvgLumin, satColor, contrast);
	vec4 correctedColor = vec4(conColor.rgb,color.a);

	gl_FragColor =  vec4(correctedColor.r , correctedColor.g, correctedColor.b, correctedColor.a);
}
