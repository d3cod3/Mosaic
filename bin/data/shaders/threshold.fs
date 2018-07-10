uniform sampler2DRect tex0;
uniform float param1f0;//thresh@
float enabled = 1.0;

void main()
{
    vec4 color = texture2DRect(tex0,gl_TexCoord[0].st);
    float c = color.g;
    c = c - (param1f0/16.0);
    c = max(c,0.0);
    c = c/c;
    gl_FragColor = enabled > 0.0 ? vec4(c,c,c,1.0) : color;
}
