#version 120

varying vec3 v;
varying vec3 N;

uniform sampler2DRect tex0;
uniform float param1f0;//amount@
uniform float param1f1;//angle@


void main() {

        float amount = param1f0;
        float angle = param1f1;

       vec2 vUv = gl_TexCoord[0].st;
       vec2 offset = amount * vec2( cos(angle), sin(angle));
       vec4 cr = texture2DRect(tex0, vUv + offset);
       vec4 cga = texture2DRect(tex0, vUv);
       vec4 cb = texture2DRect(tex0, vUv - offset);
       gl_FragColor = vec4(cr.r, cga.g, cb.b, cga.a);

}
