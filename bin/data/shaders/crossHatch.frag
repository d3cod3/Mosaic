#version 120

varying vec3 v;
varying vec3 N;

uniform sampler2DRect tex0;
uniform vec2 resolution;

uniform float param1f0;//space@
uniform float param1f1;//width@

const vec3 W = vec3(0.2125, 0.7154, 0.0721);

void main() {

 float crosshatchSpacing = param1f0/10.0;
 float lineWidth = param1f1/10.0;

 vec2 textureCoordinate = gl_TexCoord[0].xy;
 float luminance = dot(texture2DRect(tex0, textureCoordinate).rgb, W);

  vec4 colorToDisplay = vec4(1.0, 1.0, 1.0, 1.0); // use sample color?
  if (luminance < 1.00)
  {
    if (mod(textureCoordinate.x + textureCoordinate.y, crosshatchSpacing) <= lineWidth)
    {
      colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);
    }
  }
  if (luminance < 0.75)
  {
    if (mod(textureCoordinate.x - textureCoordinate.y, crosshatchSpacing) <= lineWidth)
    {
      colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);
    }
  }
  if (luminance < 0.50)
  {
    if (mod(textureCoordinate.x + textureCoordinate.y - (crosshatchSpacing / 2.0), crosshatchSpacing) <= lineWidth)
    {
      colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);
    }
  }
  if (luminance < 0.3)
  {
    if (mod(textureCoordinate.x - textureCoordinate.y - (crosshatchSpacing / 2.0), crosshatchSpacing) <= lineWidth)
    {
      colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);
    }
  }

  gl_FragColor = colorToDisplay;
}
