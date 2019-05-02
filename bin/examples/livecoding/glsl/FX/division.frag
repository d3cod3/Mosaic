#version 120

varying vec3 v;
varying vec3 N;

uniform sampler2DRect tex0;
uniform sampler2DRect tex1;

uniform vec2 resolution;
uniform float time;


void main(void) {
    vec2 coord = gl_TexCoord[0].st;
    vec4 base = texture2DRect(tex0, coord);
    float a = base.a;

    vec4 blend = texture2DRect(tex1, coord);

    vec3 compose = base.rgb / blend.rgb;
    compose = compose * compose * compose * compose * compose;
    vec4 finalColor = vec4(compose, a);
    gl_FragColor = finalColor;
}
