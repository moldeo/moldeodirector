varying vec2 v0;
varying vec2 v1;
varying vec2 v2;
varying float l;
varying float p;

attribute vec2 point0;
attribute vec2 point1;
attribute vec2 point2;
attribute float quad_width;
attribute float pressure;

void main() 
{
    gl_Position = ftransform();
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

	v0 = point0;
	v1 = point1;
	v2 = point2;
	l = quad_width;
	p = pressure;
}
