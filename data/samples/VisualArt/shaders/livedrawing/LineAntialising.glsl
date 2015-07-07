uniform sampler2D src_tex_unit0;
uniform vec2 src_tex_offset0;
uniform vec2 tempo_angle;

varying vec2 v0;
varying vec2 v1;
varying vec2 v2;
varying float l;
varying float p;

void main(void)
{
	vec4 color = texture2D(src_tex_unit0, gl_TexCoord[0].st);

	vec2 v = gl_FragCoord.xy;
	float d = dot(v1 - v0, v - v0) / (0.5 * l);
	float f = smoothstep(0.0, 0.1 * l, 0.5 * l - abs(d));
	
	gl_FragColor = vec4(color.rgb, f * color.a);
	//gl_FragColor = color;
}
