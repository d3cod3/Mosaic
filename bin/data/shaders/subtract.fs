uniform sampler2DRect tex0;
uniform sampler2DRect tex1;

void main()
{
	vec4 color0 = texture2DRect(tex0,gl_TexCoord[0].st);
	vec4 color1 = texture2DRect(tex1,gl_TexCoord[0].st);
	gl_FragColor = color0 - color1;
}
