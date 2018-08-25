#version 120

const int GAUSSIAN_SAMPLES = 9;

varying vec3 v;
varying vec3 N;
varying vec2 textureCoordinate;
varying vec2 blurCoordinates[GAUSSIAN_SAMPLES];

void main() {
    v = vec3(gl_ModelViewMatrix * gl_Vertex);
    N = normalize(gl_NormalMatrix * gl_Normal);

    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_Position = ftransform();

    textureCoordinate = v.xy;

    // Calculate the positions for the blur
    int multiplier = 0;
    vec2 blurStep;
    vec2 singleStepOffset = vec2(0,0);

    for (int i = 0; i < GAUSSIAN_SAMPLES; i++) {
        multiplier = (i - ((GAUSSIAN_SAMPLES - 1) / 2));
        blurStep = float(multiplier) * singleStepOffset;
        blurCoordinates[i] = textureCoordinate + blurStep;
    }
}
