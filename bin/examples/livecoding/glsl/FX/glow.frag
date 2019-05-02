#version 120

/*
    Glitch Shader from ofxPostGlitch shaders collection from JeongHo Park <https://github.com/jeonghopark/ofxPostGlitch>
    adapted for Mosaic platform
*/

varying vec3 v;
varying vec3 N;

uniform sampler2DRect tex0;
uniform int param1i0;//blur@

float map(float value, float inMin, float inMax, float outMin, float outMax) {
  return outMin + (outMax - outMin) * (value - inMin) / (inMax - inMin);
}

void main(){

    float e = 2.718281828459045235360287471352;

    vec2 coord = gl_TexCoord[0].st;
    vec4 col = texture2DRect(tex0,coord);

    int blur_w = int(map(param1i0,0,30,0,8));
    float pi = 3.1415926535;
    vec4 gws = vec4(0.0,0.0,0.0,1.0);
    float weight;
    float k = 1.0;

    weight = 1.0/(float(blur_w)*2.0+1.0)/(float(blur_w)*2.0+1.0);

    for (int i = 0;i < blur_w*blur_w;i++){
        gws = gws + texture2DRect(tex0,vec2(coord.x+float(mod(float(i),float(blur_w))),coord.y+float(i/blur_w)))*weight*1.3;
        gws = gws + texture2DRect(tex0,vec2(coord.x-float(mod(float(i),float(blur_w))),coord.y+float(i/blur_w)))*weight*1.3;
        gws = gws + texture2DRect(tex0,vec2(coord.x+float(mod(float(i),float(blur_w))),coord.y-float(i/blur_w)))*weight*1.3;
        gws = gws + texture2DRect(tex0,vec2(coord.x-float(mod(float(i),float(blur_w))),coord.y-float(i/blur_w)))*weight*1.3;
    }


    gl_FragColor.rgba = col+gws;
}
