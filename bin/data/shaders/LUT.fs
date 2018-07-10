uniform sampler2DRect tex0;
uniform sampler2DRect tex1;

float size = 32.0;

void main(void){
    vec2 st = gl_FragCoord.st;
    
    vec4 srcColor = texture2DRect(tex0, st);
    
    float x = srcColor.r * (size-1.0);
    float y = srcColor.g * (size-1.0);
    float z = srcColor.b * (size-1.0);
    
    vec3 color = texture2DRect(tex1, vec2(floor(x)+1.0 +(floor(y)+1.0)*size, floor(z)+1.0)).rgb;
    
    gl_FragColor = vec4( color , 1.0);
}