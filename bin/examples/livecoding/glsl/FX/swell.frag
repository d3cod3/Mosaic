#version 120

/*
    Glitch Shader from ofxPostGlitch shaders collection from JeongHo Park <https://github.com/jeonghopark/ofxPostGlitch>
    adapted for Mosaic platform
*/

varying vec3 v;
varying vec3 N;

uniform sampler2DRect tex0;
uniform float param1f0;//timer@
uniform float param1f1;//rand@

void main(){

    float timer = param1f0;
    float rand = param1f1/10;

    vec2 coord = gl_TexCoord[0].st;
    vec4 col = texture2DRect(tex0,coord);
    vec4 col_s = texture2DRect(tex0,coord + vec2(sin(coord.y*0.03+timer*20.0)*(6.0+12.0*rand),0));

    col = col_s;

    gl_FragColor.rgba = col.rgba;
}
