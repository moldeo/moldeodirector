uniform sampler2D src_tex_unit0;
uniform vec2 src_tex_offset0;
uniform vec2 tempo_angle;
uniform vec2 dest_tex_size;

void main(void)
{
    
	vec2 texCoord = gl_TexCoord[0].st;
	texCoord = texCoord + vec2( tempo_angle.x* 0.01, tempo_angle.x * 0.01 );
	gl_FragColor = texture2D( src_tex_unit0, texCoord );
	
}
