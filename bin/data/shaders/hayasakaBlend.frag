#version 120
#extension GL_ARB_texture_rectangle : enable

varying vec3 v;
varying vec3 N;

#define BlendLinearDodgef BlendAddf
#define BlendLinearBurnf BlendSubstractf
#define BlendAddf(base, blend) min(base + blend, 1.0)
#define BlendSubstractf(base, blend) max(base + blend - 1.0, 0.0)
#define BlendLightenf(base, blend) max(blend, base)
#define BlendDarkenf(base, blend) min(blend, base)
#define BlendLinearLightf(base, blend) (blend < 0.5 ? BlendLinearBurnf(base, (2.0 * blend)) : BlendLinearDodgef(base, (2.0 * (blend - 0.5))))
#define BlendScreenf(base, blend) (1.0 - ((1.0 - base) * (1.0 - blend)))
#define BlendOverlayf(base, blend) (base < 0.5 ? (2.0 * base * blend) : (1.0 - 2.0 * (1.0 - base) * (1.0 - blend)))
#define BlendSoftLightf(base, blend) ((blend < 0.5) ? (2.0 * base * blend + base * base * (1.0 - 2.0 * blend)) : (sqrt(base) * (2.0 * blend - 1.0) + 2.0 * base * (1.0 - blend)))
#define BlendColorDodgef(base, blend) ((blend == 1.0) ? blend : min(base / (1.0 - blend), 1.0))
#define BlendColorBurnf(base, blend) ((blend == 0.0) ? blend : max((1.0 - ((1.0 - base) / blend)), 0.0))
#define BlendVividLightf(base, blend) ((blend < 0.5) ? BlendColorBurnf(base, (2.0 * blend)) : BlendColorDodgef(base, (2.0 * (blend - 0.5))))
#define BlendPinLightf(base, blend) ((blend < 0.5) ? BlendDarkenf(base, (2.0 * blend)) : BlendLightenf(base, (2.0 *(blend - 0.5))))
#define BlendHardMixf(base, blend) ((BlendVividLightf(base, blend) < 0.5) ? 0.0 : 1.0)
#define BlendReflectf(base, blend) ((blend == 1.0) ? blend : min(base * base / (1.0 - blend), 1.0))
#define Blend(base, blend, funcf) vec3(funcf(base.r, blend.r), funcf(base.g, blend.g), funcf(base.b, blend.b))
#define BlendLightenBlendLightenf
#define BlendDarkenBlendDarkenf
#define BlendNormal(base, blend) (blend)
#define BlendMultiply(base, blend) (base * blend)
#define BlendAverage(base, blend) ((base + blend) / 2.0)
#define BlendAdd(base, blend) min(base + blend, vec3(1.0))
#define BlendSubstract(base, blend) max(base + blend - vec3(1.0), vec3(0.0))
#define BlendDifference(base, blend) abs(base - blend)
#define BlendNegation(base, blend) (vec3(1.0) - abs(vec3(1.0) - base - blend))
#define BlendExclusion(base, blend) (base + blend - 2.0 * base * blend)
#define BlendScreen(base, blend) Blend(base, blend, BlendScreenf)
#define BlendOverlay(base, blend) Blend(base, blend, BlendOverlayf)
#define BlendSoftLight(base, blend) Blend(base, blend, BlendSoftLightf)
#define BlendHardLight(base, blend) BlendOverlay(blend, base)
#define BlendColorDodge(base, blend) Blend(base, blend, BlendColorDodgef)
#define BlendColorBurn(base, blend) Blend(base, blend, BlendColorBurnf)
#define BlendLinearDodgeBlendAdd
#define BlendLinearBurnBlendSubstract
#define BlendLinearLight(base, blend) Blend(base, blend, BlendLinearLightf)
#define BlendVividLight(base, blend) Blend(base, blend, BlendVividLightf)
#define BlendPinLight(base, blend) Blend(base, blend, BlendPinLightf)
#define BlendHardMix(base, blend) Blend(base, blend, BlendHardMixf)
#define BlendReflect(base, blend) Blend(base, blend, BlendReflectf)
#define BlendGlow(base, blend) BlendReflect(blend, base)
#define BlendPhoenix(base, blend) (min(base, blend) - max(base, blend) + vec3(1.0))
#define BlendOpacity(base, blend, F, O) (F(base, blend) * O + blend * (1.0 - O))
#define GammaCorrection(color, gamma)pow(color, 1.0 / gamma)
#define LevelsControlInputRange(color, minInput, maxInput)min(max(color - vec3(minInput), vec3(0.0)) / (vec3(maxInput) - vec3(minInput)), vec3(1.0))
#define LevelsControlInput(color, minInput, gamma, maxInput)GammaCorrection(LevelsControlInputRange(color, minInput, maxInput), gamma)
#define LevelsControlOutputRange(color, minOutput, maxOutput) mix(vec3(minOutput), vec3(maxOutput), color)
#define LevelsControl(color, minInput, gamma, maxInput, minOutput, maxOutput) LevelsControlOutputRange(LevelsControlInput(color, minInput, gamma, maxInput), minOutput, maxOutput)


vec4 Desaturate(vec3 color, float Desaturation){
    vec3 grayXfer = vec3(0.3, 0.59, 0.11);
    vec3 gray = vec3(dot(grayXfer, color));
    return vec4(mix(color, gray, Desaturation), 1.0);
}
vec3 RGBToHSL(vec3 color){
    vec3 hsl;
    float fmin = min(min(color.r, color.g), color.b);
    float fmax = max(max(color.r, color.g), color.b);
    float delta = fmax - fmin;
    hsl.z = (fmax + fmin) / 2.0;
    if (delta == 0.0){
        hsl.x = 0.0;
        hsl.y = 0.0;
    } else {
        if (hsl.z < 0.5)
            hsl.y = delta / (fmax + fmin);
        else
            hsl.y = delta / (2.0 - fmax - fmin);

        float deltaR = (((fmax - color.r) / 6.0) + (delta / 2.0)) / delta;
        float deltaG = (((fmax - color.g) / 6.0) + (delta / 2.0)) / delta;
        float deltaB = (((fmax - color.b) / 6.0) + (delta / 2.0)) / delta;

        if (color.r == fmax )
            hsl.x = deltaB - deltaG;
        else if (color.g == fmax)
            hsl.x = (1.0 / 3.0) + deltaR - deltaB;
        else if (color.b == fmax)
            hsl.x = (2.0 / 3.0) + deltaG - deltaR;

        if (hsl.x < 0.0)
            hsl.x += 1.0;
        else if (hsl.x > 1.0)
            hsl.x -= 1.0;
    }
    return hsl;
}
float HueToRGB(float f1, float f2, float hue){
    if (hue < 0.0)
        hue += 1.0;
    else if (hue > 1.0)
        hue -= 1.0;

    float res;
    if ((6.0 * hue) < 1.0)
        res = f1 + (f2 - f1) * 6.0 * hue;
    else if ((2.0 * hue) < 1.0)
        res = f2;
    else if ((3.0 * hue) < 2.0)
        res = f1 + (f2 - f1) * ((2.0 / 3.0) - hue) * 6.0;
    else
        res = f1;

    return res;
}
vec3 HSLToRGB(vec3 hsl){
    vec3 rgb;
    if (hsl.y == 0.0)
        rgb = vec3(hsl.z);
    else {
        float f2;

        if (hsl.z < 0.5)
            f2 = hsl.z * (1.0 + hsl.y);
        else
            f2 = (hsl.z + hsl.y) - (hsl.y * hsl.z);

        float f1 = 2.0 * hsl.z - f2;
        rgb.r = HueToRGB(f1, f2, hsl.x + (1.0/3.0));
        rgb.g = HueToRGB(f1, f2, hsl.x);
        rgb.b= HueToRGB(f1, f2, hsl.x - (1.0/3.0));
    }
    return rgb;
}
vec3 ContrastSaturationBrightness(vec3 color, float brt, float sat, float con){
    const float AvgLumR = 0.5;
    const float AvgLumG = 0.5;
    const float AvgLumB = 0.5;
    const vec3 LumCoeff = vec3(0.2125, 0.7154, 0.0721);
    vec3 AvgLumin = vec3(AvgLumR, AvgLumG, AvgLumB);
    vec3 brtColor = color * brt;
    vec3 intensity = vec3(dot(brtColor, LumCoeff));
    vec3 satColor = mix(intensity, brtColor, sat);
    vec3 conColor = mix(AvgLumin, satColor, con);
    return conColor;
}
vec3 BlendHue(vec3 base, vec3 blend){
    vec3 baseHSL = RGBToHSL(base);
    return HSLToRGB(vec3(RGBToHSL(blend).r, baseHSL.g, baseHSL.b));
}
vec3 BlendSaturation(vec3 base, vec3 blend){
    vec3 baseHSL = RGBToHSL(base);
    return HSLToRGB(vec3(baseHSL.r, RGBToHSL(blend).g, baseHSL.b));
}
vec3 BlendColor(vec3 base, vec3 blend){
    vec3 blendHSL = RGBToHSL(blend);
    return HSLToRGB(vec3(blendHSL.r, blendHSL.g, RGBToHSL(base).b));
}
vec3 BlendLuminosity(vec3 base, vec3 blend){
    vec3 baseHSL = RGBToHSL(base);
    return HSLToRGB(vec3(baseHSL.r, baseHSL.g, RGBToHSL(blend).b));
}

uniform sampler2DRect tex0;
uniform sampler2DRect tex1;
uniform int param1i0;//mode@

void main(){
    int mode = param1i0;
    vec4 baseCol = texture2DRect(tex0, gl_TexCoord[0].st);
    vec4 blendCol = texture2DRect(tex1, gl_TexCoord[0].st);

    vec3 result;
    if (mode == 0){
        result = mix(baseCol.rgb, blendCol.rgb, blendCol.a);
    } else if (mode == 1) {
        result = BlendMultiply(baseCol.rgb, blendCol.rgb);
    } else if (mode == 2) {
        result = BlendAverage(baseCol.rgb, blendCol.rgb);
    } else if (mode == 3) {
        result = BlendAdd(baseCol.rgb, blendCol.rgb);
    } else if (mode == 4) {
        result = BlendSubstract(baseCol.rgb, blendCol.rgb);
    } else if (mode == 5) {
        result = BlendDifference(baseCol.rgb, blendCol.rgb);
    } else if (mode == 6) {
        result = BlendNegation(baseCol.rgb, blendCol.rgb);
    } else if (mode == 7) {
        result = BlendExclusion(baseCol.rgb, blendCol.rgb);
    } else if (mode == 8) {
        result = BlendScreen(baseCol.rgb, blendCol.rgb);
    } else if (mode == 9) {
        result = BlendOverlay(baseCol.rgb, blendCol.rgb);
    } else if (mode == 10){
        result = BlendSoftLight(baseCol.rgb, blendCol.rgb);
    } else if (mode == 11){
        result = BlendHardLight(baseCol.rgb, blendCol.rgb);
    } else if (mode == 12){
        result = BlendColorDodge(baseCol.rgb, blendCol.rgb);
    } else if (mode == 13){
        result = BlendColorBurn(baseCol.rgb, blendCol.rgb);
    } else if (mode == 14){
        result = BlendLinearLight(baseCol.rgb, blendCol.rgb);
    } else if (mode == 15){
        result = BlendVividLight(baseCol.rgb, blendCol.rgb);
    } else if (mode == 16){
        result = BlendPinLight(baseCol.rgb, blendCol.rgb);
    } else if (mode == 17){
        result = BlendHardMix(baseCol.rgb, blendCol.rgb);
    } else if (mode == 18){
        result = BlendReflect(baseCol.rgb, blendCol.rgb);
    } else if (mode == 19){
        result = BlendGlow(baseCol.rgb, blendCol.rgb);
    } else if (mode == 20){
        result = BlendPhoenix(baseCol.rgb, blendCol.rgb);
    } else if (mode == 21){
        result = BlendHue(baseCol.rgb, blendCol.rgb);
    } else if (mode == 22){
        result = BlendSaturation(baseCol.rgb, blendCol.rgb);
    } else if (mode == 23){
        result = BlendColor(baseCol.rgb, blendCol.rgb);
    } else if (mode == 24){
        result = BlendLuminosity(baseCol.rgb, blendCol.rgb);
    } else {
        result = BlendNormal(baseCol.rgb, blendCol.rgb);
    }
    gl_FragColor = vec4(result.rgb, baseCol.a);
}
