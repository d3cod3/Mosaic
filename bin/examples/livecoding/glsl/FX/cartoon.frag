#version 120

varying vec3 v;
varying vec3 N;

varying vec2 leftTextureCoordinate;
varying vec2 rightTextureCoordinate;
varying vec2 topTextureCoordinate;
varying vec2 topLeftTextureCoordinate;
varying vec2 topRightTextureCoordinate;
varying vec2 bottomTextureCoordinate;
varying vec2 bottomLeftTextureCoordinate;
varying vec2 bottomRightTextureCoordinate;

uniform sampler2DRect tex0;
uniform float param1f0;//level@

uniform vec2 resolution;
uniform float time;

void main(void){

    float quantizationLevels = param1f0;

    vec2 textureCoordinate = gl_TexCoord[0].xy;
    vec4 textureColor = texture2DRect(tex0, textureCoordinate);

    float bottomLeftIntensity = texture2DRect(tex0, bottomLeftTextureCoordinate).r;
    float topRightIntensity = texture2DRect(tex0, topRightTextureCoordinate).r;
    float topLeftIntensity = texture2DRect(tex0, topLeftTextureCoordinate).r;
    float bottomRightIntensity = texture2DRect(tex0, bottomRightTextureCoordinate).r;
    float leftIntensity = texture2DRect(tex0, leftTextureCoordinate).r;
    float rightIntensity = texture2DRect(tex0, rightTextureCoordinate).r;
    float bottomIntensity = texture2DRect(tex0, bottomTextureCoordinate).r;
    float topIntensity = texture2DRect(tex0, topTextureCoordinate).r;
    float h = -topLeftIntensity - 2.0 * topIntensity - topRightIntensity + bottomLeftIntensity + 2.0 * bottomIntensity + bottomRightIntensity;
    float v = -bottomLeftIntensity - 2.0 * leftIntensity - topLeftIntensity + bottomRightIntensity + 2.0 * rightIntensity + topRightIntensity;

    float mag = length(vec2(h, v));

    vec3 posterizedImageColor = floor((textureColor.rgb * quantizationLevels) + 0.5) / quantizationLevels;

    float thresholdTest = 1.0 - step(1.0, mag);

    gl_FragColor = vec4(posterizedImageColor * thresholdTest, textureColor.a);

}
