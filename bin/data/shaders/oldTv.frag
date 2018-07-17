#version 120

varying vec3 v;
varying vec3 N;

uniform float time;
uniform sampler2DRect tex0;

uniform float param1f0;//light@
uniform float param1f1;//rows@

void main(void){

    float brightness = param1f0/4.0;
    float rows = param1f1/2.0;

    vec2 st = gl_TexCoord[0].st;
    vec2 uv = 0.5 + (1.0/st-0.5)*( (1.0-brightness) + brightness*sin(0.2*time) );

    vec3 col;

    col.r = texture2DRect(tex0, vec2(st.x+0.003,st.y)).r;
    col.g = texture2DRect(tex0, vec2(st.x+0.000,st.y)).g;
    col.b = texture2DRect(tex0, vec2(st.x-0.003,st.y)).b;

    col = clamp(col * 0.5 + 0.5 * col * col * 1.2,0.0,1.0);

    col *= 0.5 + 0.5 * 16.0 * uv.x * uv.y * (1.0-uv.x) * (1.0-uv.y);
    col *= vec3(0.8,1.0,0.7);
    col *= 0.9 + 0.1 * sin(10.0 * time + st.y * rows);
    col *= 0.97 + 0.03 * sin(110.0 * time);

    gl_FragColor = vec4(col,1.0);
}
