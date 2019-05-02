#version 120

/*
    Glitch Shader from ofxPostGlitch shaders collection from JeongHo Park <https://github.com/jeonghopark/ofxPostGlitch>
    adapted for Mosaic platform
*/

varying vec3 v;
varying vec3 N;

uniform sampler2DRect tex0;
uniform float param1f0;//rand@

void main(){

    float rand = param1f0/10.0;

    vec2 coord = gl_TexCoord[0].st;

    vec4 col = texture2DRect(tex0,coord);
    vec4 col_r = texture2DRect(tex0,coord + vec2(-35.0*rand,0));
    vec4 col_l = texture2DRect(tex0,coord + vec2( 35.0*rand,0));
    vec4 col_g = texture2DRect(tex0,coord + vec2( -7.5*rand,0));


    col.b = col.b + col_r.b*max(1.0,sin(coord.y*1.2)*2.5)*rand;
    col.r = col.r + col_l.r*max(1.0,sin(coord.y*1.2)*2.5)*rand;
    col.g = col.g + col_g.g*max(1.0,sin(coord.y*1.2)*2.5)*rand;

    gl_FragColor.rgba = col.rgba;
}
