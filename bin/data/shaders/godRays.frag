#version 120

varying vec3 v;
varying vec3 N;

uniform sampler2DRect tex0;
uniform float param1f0;//light@

uniform vec2 resolution;
uniform float time;

vec2 lightPositionOnScreen = vec2(0.5,0.5);

const int NUM_SAMPLES = 50;

void main() {

  vec4 origColor = texture2DRect(tex0, gl_TexCoord[0].st);
  vec4 raysColor = texture2DRect(tex0, gl_TexCoord[0].st);

  float lightDirDOTviewDir = param1f0/2.0;

  if (lightDirDOTviewDir>0.0){
    float exposure	= 0.1/float(NUM_SAMPLES);
    float decay		= 1.0 ;
    float density	= 0.5;
    float weight	= 6.0;
    float illuminationDecay = 1.0;

    vec2 deltaTextCoord = vec2( gl_TexCoord[0].st - lightPositionOnScreen);
    vec2 textCoo = gl_TexCoord[0].st;
    deltaTextCoord *= 1.0 / float(NUM_SAMPLES) * density;



    for(int i=0; i < NUM_SAMPLES ; i++){
      textCoo -= deltaTextCoord;
      vec4 tsample = texture2DRect(tex0, textCoo );
      tsample *= illuminationDecay * weight;
      raysColor += tsample;
      illuminationDecay *= decay;
    }
    raysColor *= exposure * lightDirDOTviewDir;
    float p = 0.3 *raysColor.g + 0.59*raysColor.r + 0.11*raysColor.b;
    gl_FragColor = origColor + p;
    } else {
      gl_FragColor = origColor;
    }
}
