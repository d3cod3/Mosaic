#version 150

// OF default uniforms and attributes
uniform mat4 modelViewProjectionMatrix;
uniform vec4 globalColor;

in vec4 position;
in vec2 texcoord;
in vec4 color;

// App uniforms and attributes
in vec4 iPositionScale;
in vec4 iColor;

out vec2 vTexCoord;
out vec4 vColor;

void main(void) 
{
	vTexCoord = texcoord;
	vColor = globalColor * iColor;
	gl_Position = modelViewProjectionMatrix * vec4(position.xy * iPositionScale.z + iPositionScale.xy, position.zw);
}
