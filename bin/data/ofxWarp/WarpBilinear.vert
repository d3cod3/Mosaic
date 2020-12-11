#version 150

// OF default uniforms and attributes
uniform mat4 modelViewProjectionMatrix;
uniform vec4 globalColor;

in vec4 position;
in vec2 texcoord;
in vec4 color;

// App uniforms and attributes
out vec2 vTexCoord;
out vec4 vColor;

void main(void)
{
	vTexCoord = texcoord;
	vColor = globalColor;

	gl_Position = modelViewProjectionMatrix * position;
}
