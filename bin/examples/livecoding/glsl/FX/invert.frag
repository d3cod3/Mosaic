#version 120

/*
    Glitch Shader from ofxPostGlitch shaders collection from JeongHo Park <https://github.com/jeonghopark/ofxPostGlitch>
    adapted for Mosaic platform
*/

varying vec3 v;
varying vec3 N;

uniform sampler2DRect tex0;
uniform float param1f0;//red@
uniform float param1f1;//green@
uniform float param1f2;//blue@


void main(){

    vec2 coord = gl_TexCoord[0].st;
	vec4 col = texture2DRect(tex0,coord);

	col.r = param1f0/10 - col.r;
	col.g = param1f1/10 - col.g;
	col.b = param1f2/10 - col.b;
	gl_FragColor = col;
}
