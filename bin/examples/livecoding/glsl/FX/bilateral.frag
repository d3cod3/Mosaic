#version 120

varying vec3 v;
varying vec3 N;

const int GAUSSIAN_SAMPLES = 9;

varying vec2 textureCoordinate;
varying vec2 blurCoordinates[GAUSSIAN_SAMPLES];

uniform sampler2DRect tex0;
uniform float param1f0;//norm@

uniform vec2 resolution;
uniform float time;

float distanceNormalizationFactor = param1f0/10.0;

void main() {
    vec4 centralColor;
    float gaussianWeightTotal;
    vec4 sum;
    vec4 sampleColor;
    float distanceFromCentralColor;
    float gaussianWeight;



    centralColor = texture2DRect(tex0, blurCoordinates[4]);
    gaussianWeightTotal = 0.18;
    sum = centralColor * 0.18;

    sampleColor = texture2DRect(tex0, blurCoordinates[0]);
    distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, centralColor.a);
    gaussianWeight = 0.05 * (1.0 - distanceFromCentralColor);
    gaussianWeightTotal += gaussianWeight;
    sum += sampleColor * gaussianWeight;

    sampleColor = texture2DRect(tex0, blurCoordinates[1]);
    distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, centralColor.a);
    gaussianWeight = 0.09 * (1.0 - distanceFromCentralColor);
    gaussianWeightTotal += gaussianWeight;
    sum += sampleColor * gaussianWeight;

    sampleColor = texture2DRect(tex0, blurCoordinates[2]);
    distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, centralColor.a);
    gaussianWeight = 0.12 * (1.0 - distanceFromCentralColor);
    gaussianWeightTotal += gaussianWeight;
    sum += sampleColor * gaussianWeight;

    sampleColor = texture2DRect(tex0, blurCoordinates[3]);
    distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, centralColor.a);
    gaussianWeight = 0.15 * (1.0 - distanceFromCentralColor);
    gaussianWeightTotal += gaussianWeight;
    sum += sampleColor * gaussianWeight;

    sampleColor = texture2DRect(tex0, blurCoordinates[5]);
    distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, centralColor.a);
    gaussianWeight = 0.15 * (1.0 - distanceFromCentralColor);
    gaussianWeightTotal += gaussianWeight;
    sum += sampleColor * gaussianWeight;

    sampleColor = texture2DRect(tex0, blurCoordinates[6]);
    distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, centralColor.a);
    gaussianWeight = 0.12 * (1.0 - distanceFromCentralColor);
    gaussianWeightTotal += gaussianWeight;
    sum += sampleColor * gaussianWeight;

    sampleColor = texture2DRect(tex0, blurCoordinates[7]);
    distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, centralColor.a);
    gaussianWeight = 0.09 * (1.0 - distanceFromCentralColor);
    gaussianWeightTotal += gaussianWeight;
    sum += sampleColor * gaussianWeight;

    sampleColor = texture2DRect(tex0, blurCoordinates[8]);
    distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, centralColor.a);
    gaussianWeight = 0.05 * (1.0 - distanceFromCentralColor);
    gaussianWeightTotal += gaussianWeight;
    sum += sampleColor * gaussianWeight;

    gl_FragColor = sum / gaussianWeightTotal;
}
