#version 120

varying vec3 v;
varying vec3 N;

uniform sampler2DRect tex0;
uniform sampler2DRect tex1;

void main (void){
    vec2 st = gl_TexCoord[0].st;
    vec4 mask = texture2DRect(tex0, st);
    vec4 image = texture2DRect(tex1, st);

    gl_FragColor = vec4(image.rgb,mask.r);
}
