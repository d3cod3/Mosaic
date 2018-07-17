#version 120

varying vec3 v;
varying vec3 N;

uniform sampler2DRect tex0;

void main(){
    vec4 sum = vec4(0);
    vec2 st = gl_TexCoord[0].st;
    int j;
    int i;

    for( i= -4 ;i < 4; i++){
        for (j = -3; j < 3; j++){
            sum += texture2DRect(tex0, st + vec2(j, i)*0.004) * 0.25;
        }
    }

    if (texture2DRect(tex0, st).r < 0.3){
        gl_FragColor = sum * sum * 0.012 + texture2DRect(tex0, st);
    } else {
        if (texture2DRect(tex0, st).r < 0.5){
            gl_FragColor = sum * sum * 0.009 + texture2DRect(tex0, st);
        } else {
            gl_FragColor = sum * sum * 0.0075 + texture2DRect(tex0, st);
        }
    }
}
