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
uniform float param1f2;//twist@
uniform float param1f3;//mult@

void main(){

    float timer = param1f0;
    float rand = param1f1/10;
    float twist = param1f2;
    float mult = param1f3;

    vec2 coord = gl_TexCoord[0].st;
    vec2 texCoord = vec2(max(3.0,coord.x+sin(coord.y/(153.25*rand*rand)*rand+rand*twist+timer*3.0)*mult),
						  max(3.0,coord.y+cos(coord.x/(251.57*rand*rand)*rand+rand*twist+timer*2.4)*mult)-3.);


    vec4 col = texture2DRect(tex0,texCoord);

    gl_FragColor.rgba = col.rgba;
}
