#version 120

/*
    Glitch Shader from ofxPostGlitch shaders collection from JeongHo Park <https://github.com/jeonghopark/ofxPostGlitch>
    adapted for Mosaic platform
*/

varying vec3 v;
varying vec3 N;

uniform sampler2DRect tex0;
uniform float param1f0;//blur_x@
uniform float param1f1;//blur_y@

float pix_w,pix_h;

void main(){

    float blurX = param1f0;
    float blurY = param1f1;

    pix_w = 1.0;
    pix_h = 1.0;

    vec2 coord = gl_TexCoord[0].st;
    vec4 col = texture2DRect(tex0,coord);

    vec4 col_s[5],col_s2[5];
    for (int i = 0;i < 5;i++){
        col_s[i] = texture2DRect(tex0,coord +  vec2(-pix_w*float(i)*blurX ,-pix_h*float(i)*blurY));
        col_s2[i] = texture2DRect(tex0,coord + vec2( pix_w*float(i)*blurX , pix_h*float(i)*blurY));
    }
    col_s[0] = (col_s[0] + col_s[1] + col_s[2] + col_s[3] + col_s[4])/5.0;
    col_s2[0]= (col_s2[0]+ col_s2[1]+ col_s2[2]+ col_s2[3]+ col_s2[4])/5.0;
    col = (col_s[0] + col_s2[0]) / 2.0;

    gl_FragColor.rgba = col.rgba;
}
