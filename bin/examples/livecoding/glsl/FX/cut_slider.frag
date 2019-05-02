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
    vec4 col_s = texture2DRect(tex0,coord + vec2(floor(sin(coord.y/30.0*rand+rand*rand))*30.0*rand,0));

    col = col_s;

	gl_FragColor.rgba = col.rgba;
}
