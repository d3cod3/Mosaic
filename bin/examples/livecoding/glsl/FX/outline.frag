#version 120

/*
    Glitch Shader from ofxPostGlitch shaders collection from JeongHo Park <https://github.com/jeonghopark/ofxPostGlitch>
    adapted for Mosaic platform
*/

varying vec3 v;
varying vec3 N;

uniform sampler2DRect tex0;

void main(){

	int step = 5;
	vec4 cols[25];
    vec2 coord = gl_TexCoord[0].st;

	for (int i = 0;i < step;i++){
		for (int j = 0;j < step;j++){
			cols[i*step+j] = texture2DRect(tex0,vec2((coord.x+float(j)-1.0), (coord.y+float(i)-1.0)));
			cols[i*step+j].r = (cols[i*step+j].r + cols[i*step+j].g + cols[i*step+j].b) / 3.0;
		}
	}
	float mn = 1.0,mx = 0.0;
	for (int i = 0;i < step*step;i++){
		mn = min(cols[i].r,mn);
		mx = max(cols[i].r,mx);
	}
	float dst = abs(1.0 - (mx-mn));
	gl_FragColor.a = 1.0;
    gl_FragColor.rgb = vec3(dst,dst,dst)+cols[12].rgb;
}
