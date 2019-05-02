#version 120

varying vec3 v;
varying vec3 N;

uniform sampler2DRect tex0;

uniform float param1f0;//amount@
float kernel[9];
vec2 offset[9];

void main(void){
    vec2  st = gl_TexCoord[0].st;
    vec4 sum = vec4(0.0);

    offset[0] = vec2(-1.0, -1.0);
    offset[1] = vec2(0.0, -1.0);
    offset[2] = vec2(1.0, -1.0);
    offset[3] = vec2(-1.0, 0.0);
    offset[4] = vec2(0.0, 0.0);
    offset[5] = vec2(1.0, 0.0);
    offset[6] = vec2(-1.0, 1.0);
    offset[7] = vec2(0.0, 1.0);
    offset[8] = vec2(1.0, 1.0);

    kernel[0] = 1.0/16.0;   kernel[1] = 2.0/16.0;   kernel[2] = 1.0/16.0;
    kernel[3] = 2.0/16.0;   kernel[4] = 4.0/16.0;   kernel[5] = 2.0/16.0;
    kernel[6] = 1.0/16.0;   kernel[7] = 2.0/16.0;   kernel[8] = 1.0/16.0;

    int i = 0;
    for (i = 0; i < 4; i++){
        vec4 tmp = texture2DRect(tex0, st + offset[i]);
        sum += tmp * kernel[i];
    }

    for (i = 5; i < 9; i++){
        vec4 tmp = texture2DRect(tex0, st + offset[i]);
        sum += tmp * kernel[i];
    }

    vec4 color0 = texture2DRect(tex0, st + offset[4]);
    sum += color0 * kernel[4];

    gl_FragColor = (1.0 - param1f0) * color0 +  param1f0 * vec4(sum.rgb, color0.a);
}
