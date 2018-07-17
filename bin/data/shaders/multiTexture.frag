#version 120

varying vec3 v;
varying vec3 N;

uniform sampler2DRect tex0;
uniform sampler2DRect tex1;
uniform sampler2DRect tex2;
uniform sampler2DRect tex3;

void main (void){
    vec2 pos = gl_TexCoord[0].st;

    vec4 mask = texture2DRect(tex0, pos);

    vec4 rTxt = texture2DRect(tex1, pos);
    vec4 gTxt = texture2DRect(tex2, pos);
    vec4 bTxt = texture2DRect(tex3, pos);

    vec4 color = vec4(0.0,0.0,0.0,1.0);
    color = mix(color, rTxt, mask.r );
    color = mix(color, gTxt, mask.g );
    color = mix(color, bTxt, mask.b );

    gl_FragColor = color;
}
