#version 120

varying vec3 v;
varying vec3 N;

uniform sampler2DRect tex0;
uniform float param1f0;//segments@

void main(){

    float segments = param1f0*4.0;

    vec2 uv = gl_TexCoord[0].st;
    vec2 normed = 2.0 * uv - 1.0;
    float r = length(normed);
    float theta = atan(normed.y / abs(normed.x));
    theta *= segments;

    vec2 newUv = (vec2(r * cos(theta), r * sin(theta)) + 1.0) / 2.0;

    gl_FragColor = texture2DRect(tex0, newUv);
}
