#version 120

varying vec3 v;
varying vec3 N;

uniform sampler2DRect tex0;
uniform float param1f0;//v@


void main() {

    float v = param1f0/10.0;

    vec2 vUv = gl_TexCoord[0].st;
    vec4 sum = vec4( 0.0 );

    float vv = v * abs( 1.0 - vUv.y );

    sum += texture2DRect( tex0, vec2( vUv.x, vUv.y - 4.0 * vv ) ) * 0.051;
    sum += texture2DRect( tex0, vec2( vUv.x, vUv.y - 3.0 * vv ) ) * 0.0918;
    sum += texture2DRect( tex0, vec2( vUv.x, vUv.y - 2.0 * vv ) ) * 0.12245;
    sum += texture2DRect( tex0, vec2( vUv.x, vUv.y - 1.0 * vv ) ) * 0.1531;
    sum += texture2DRect( tex0, vec2( vUv.x, vUv.y ) ) * 0.1633;
    sum += texture2DRect( tex0, vec2( vUv.x, vUv.y + 1.0 * vv ) ) * 0.1531;
    sum += texture2DRect( tex0, vec2( vUv.x, vUv.y + 2.0 * vv ) ) * 0.12245;
    sum += texture2DRect( tex0, vec2( vUv.x, vUv.y + 3.0 * vv ) ) * 0.0918;
    sum += texture2DRect( tex0, vec2( vUv.x, vUv.y + 4.0 * vv ) ) * 0.051;

    gl_FragColor = sum;
}
