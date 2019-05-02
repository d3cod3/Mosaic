#version 120

/*
    Glitch Shader from ofxPostGlitch shaders collection from JeongHo Park <https://github.com/jeonghopark/ofxPostGlitch>
    adapted for Mosaic platform
*/

varying vec3 v;
varying vec3 N;

uniform sampler2DRect tex0;
uniform float param1f0;//slit@


void main(){

	float slit_h = param1f0;

    vec2 coord = gl_TexCoord[0].st;
    vec2 texCoord = vec2(3.0+floor(coord.x/slit_h)*slit_h ,coord.y);
    vec4 col = texture2DRect(tex0,texCoord);

    gl_FragColor.rgba = col.rgba;
}
