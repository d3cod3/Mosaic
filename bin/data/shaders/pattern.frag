#version 120

varying vec3 v;
varying vec3 N;

uniform float time;
uniform vec2 resolution;
uniform vec4 mouse;

uniform float param1f0;//amount@
uniform float param1f1;//units@
uniform float param1f2;//speed@

void main(void){
    float tot = param1f0*3.1415926;
    float n = param1f1;
    float speed = param1f2;

    vec2 p = -1.0 + 2.0 * gl_FragCoord.xy / resolution.xy;
    p.y *= resolution.y/resolution.x;
    p *= 100.0;

    float df = tot/n;
    float c = 1.;
    float t = time*speed;

    for (float phi =0.0; phi < tot; phi+=df){
        c+=cos(cos(phi)*p.x+sin(phi)*p.y+t*phi/tot);
    }

    gl_FragColor = vec4(c,c,c,1.0);
}
