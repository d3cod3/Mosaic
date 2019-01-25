#version 120

varying vec3 v;
varying vec3 N;

attribute vec4 iPositionScale;
attribute vec4 iColor;

attribute vec4 position;
attribute vec2 texcoord;
attribute vec4 color;

varying vec2 vTexCoord;
varying vec4 vColor;

void main(void) {

	vTexCoord = texcoord;
	vColor = gl_Color * iColor;
  	gl_Position = gl_ModelViewProjectionMatrix * vec4(position.xy * iPositionScale.z + iPositionScale.xy, position.zw);


}
