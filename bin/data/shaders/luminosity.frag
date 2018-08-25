#version 120

varying vec3 v;
varying vec3 N;

uniform sampler2DRect tex0;
uniform sampler2DRect tex1;

uniform vec2 resolution;
uniform float time;

//--------------------------------------------------------------
vec3 RGBToHSL(vec3 color) {
    // init to 0 to avoid warnings ? (and reverse if + remove first part)
	vec3 hsl;

    //Min. value of RGB
	float fmin = min(min(color.r, color.g), color.b);
    //Max. value of RGB
	float fmax = max(max(color.r, color.g), color.b);
    //Delta RGB value
	float delta = fmax - fmin;

    // Luminance
	hsl.z = (fmax + fmin) / 2.0;

    //This is a gray, no chroma...
	if (delta == 0.0) {
        // Hue
		hsl.x = 0.0;
        // Saturation
		hsl.y = 0.0;

    //Chromatic data...
	} else {
		if (hsl.z < 0.5) {
            // Saturation
			hsl.y = delta / (fmax + fmin);
		} else {
            // Saturation
			hsl.y = delta / (2.0 - fmax - fmin);
		}

		float deltaR = (((fmax - color.r) / 6.0) + (delta / 2.0)) / delta;
		float deltaG = (((fmax - color.g) / 6.0) + (delta / 2.0)) / delta;
		float deltaB = (((fmax - color.b) / 6.0) + (delta / 2.0)) / delta;

		if (color.r == fmax ) {
            // Hue
			hsl.x = deltaB - deltaG;
		} else if (color.g == fmax) {
            // Hue
			hsl.x = (1.0 / 3.0) + deltaR - deltaB;
		} else if (color.b == fmax) {
            // Hue
			hsl.x = (2.0 / 3.0) + deltaG - deltaR;
        }

		if (hsl.x < 0.0) {
            // Hue
			hsl.x += 1.0;
		} else if (hsl.x > 1.0) {
            // Hue
			hsl.x -= 1.0;
        }
	}

	return hsl;
}

//--------------------------------------------------------------
//
float HueToRGB(float f1, float f2, float hue) {
	if (hue < 0.0) {
		hue += 1.0;
    } else if (hue > 1.0) {
		hue -= 1.0;
    }

	float res;
	if ((6.0 * hue) < 1.0) {
		res = f1 + (f2 - f1) * 6.0 * hue;
	} else if ((2.0 * hue) < 1.0) {
		res = f2;
	} else if ((3.0 * hue) < 2.0) {
		res = f1 + (f2 - f1) * ((2.0 / 3.0) - hue) * 6.0;
	} else {
		res = f1;
    }

	return res;
}

//--------------------------------------------------------------
//
vec3 HSLToRGB(vec3 hsl) {
	vec3 rgb;

	if (hsl.y == 0.0) {
        // Luminance
		rgb = vec3(hsl.z);
    } else {
		float f2;

		if (hsl.z < 0.5) {
			f2 = hsl.z * (1.0 + hsl.y);
		} else {
			f2 = (hsl.z + hsl.y) - (hsl.y * hsl.z);
        }

		float f1 = 2.0 * hsl.z - f2;

		rgb.r = HueToRGB(f1, f2, hsl.x + (1.0 / 3.0));
		rgb.g = HueToRGB(f1, f2, hsl.x);
		rgb.b = HueToRGB(f1, f2, hsl.x - (1.0 / 3.0));
	}

	return rgb;
}

//--------------------------------------------------------------
// Luminosity Blend mode creates the result color by combining the hue and saturation of the base color with the luminance of the blend color.
vec3 BlendLuminosity(vec3 base, vec3 blend) {
	vec3 baseHSL = RGBToHSL(base);
	return HSLToRGB(vec3(baseHSL.r, baseHSL.g, RGBToHSL(blend).b));
}

void main(void) {
    vec2 coord = gl_TexCoord[0].st;
    vec4 base = texture2DRect(tex0, coord);
    float a = base.a;

    vec4 blend = texture2DRect(tex1, coord);

    vec3 compose = BlendLuminosity(base.rgb, blend.rgb);
    vec4 finalColor = vec4(compose, a);
    gl_FragColor = finalColor;
}
