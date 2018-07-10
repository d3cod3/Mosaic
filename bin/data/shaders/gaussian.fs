uniform sampler2DRect	tex0;
uniform float param1f0;//V@
uniform float param1f1;//R@
float size_cy = 1.0;

void main (void) {
    float rho = param1f1 + 0.01;

    float size_cx = param1f0/20.0;

    float direction = 0.0;
	float kernel_size = 9.0;
    vec2 dir = direction < 0.5 ? vec2(1.0,0.0) : vec2(0.0,1.0);

	float dx = 1.0 / size_cx;
	float dy = 1.0 / size_cy;
	vec2  st = gl_TexCoord [0].st;
	
	vec4	color = vec4 (0.0, 0.0, 0.0, 0.0);
	float	weight = 0.0;
	
	for (float i = -1.0*kernel_size ; i <= kernel_size ; i+=1.0) {
		float fac = exp (-(i * i) / (2.0 * rho * rho));
		weight += fac;
		color += texture2DRect(tex0, st + vec2 (dx*i, dy*i) * dir) * fac;
	}
	
	gl_FragColor =  color / weight;
}
