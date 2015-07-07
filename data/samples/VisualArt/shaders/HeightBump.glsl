// Emboss kernel
// +2  0  0
//  0 -1  0
//  0  0 -1
#define KERNEL_SIZE 9

uniform sampler2D src_tex_unit0;
uniform vec2 tempo_angle;
uniform float fade_const;
uniform vec2 src_tex_offset0;

float kernel[KERNEL_SIZE];
vec2 offset[KERNEL_SIZE];

vec4 blur( int i, int j ) {

	int ik = 0;
    vec4 sum = vec4(0.0);

    offset[0] = vec2(-src_tex_offset0.s*(1-i), -src_tex_offset0.t*(1-j) );
    offset[1] = vec2( src_tex_offset0.s*i, -src_tex_offset0.t*(1-j) );
    offset[2] = vec2(src_tex_offset0.s*(1+i), -src_tex_offset0.t*(1-j) );

    offset[3] = vec2(-src_tex_offset0.s*(1-i), src_tex_offset0.t*j );
    offset[4] = vec2( src_tex_offset0.s*i, src_tex_offset0.t*j );
    offset[5] = vec2(src_tex_offset0.s*(1+i), src_tex_offset0.t*j );

    offset[6] = vec2(-src_tex_offset0.s*(1-i), src_tex_offset0.t*(1+j) );
    offset[7] = vec2( src_tex_offset0.s*i, src_tex_offset0.t*(1+j) );
    offset[8] = vec2(src_tex_offset0.s*(1+i), src_tex_offset0.t*(1+j) );

    kernel[0] = 1.0/16.0;   kernel[1] = 2.0/16.0;   kernel[2] = 1.0/16.0;
    kernel[3] = 2.0/16.0;   kernel[4] = 4.0/16.0;   kernel[5] = 2.0/16.0;
    kernel[6] = 1.0/16.0;   kernel[7] = 2.0/16.0;   kernel[8] = 1.0/16.0;

    for (ik = 0; ik < 4; ik++)
    {
        vec4 tmp = texture2D(src_tex_unit0, gl_TexCoord[0].st + offset[ik]);
        sum += tmp * kernel[ik];
    }

    for (ik = 5; ik < KERNEL_SIZE; ik++)
    {
        vec4 tmp = texture2D(src_tex_unit0, gl_TexCoord[0].st + offset[ik]);
        sum += tmp * kernel[ik];
    }
	
	vec4 color0 = texture2D(src_tex_unit0, gl_TexCoord[0].st + offset[4]);
    sum += color0 * kernel[4];
	return sum;
}



void main()
{
   vec3 ligthVector = vec3( 0.1f, 0.1f, -0.8f );
   
   vec2 texCoord = gl_TexCoord[0].xy;
   
   vec4 color0  = texture2D(src_tex_unit0, texCoord);
   vec4 colorlight = color0;
   
   vec4 color0left = blur(-1, 0); //texture2D(src_tex_unit0, texCoord + vec2( -src_tex_offset0.s,  0.0f));
   vec4 color0right = blur( 1, 0); //texture2D(src_tex_unit0, texCoord + vec2( src_tex_offset0.s,  0.0f));
   
   vec4 color0top = blur(0, -1); //texture2D(src_tex_unit0, texCoord + vec2( 0, -src_tex_offset0.t ));
   vec4 color0bottom = blur( 0, 1); //texture2D(src_tex_unit0, texCoord + vec2( 0,  src_tex_offset0.t ));
   
   float normalx = clamp( 200.0f * fade_const * ( ((color0left.r - color0.r) - (color0.r - color0right.r)) ) * 0.5f, -1.0f, 1.0f );
   float normaly = clamp( 200.0f * fade_const * ( ((color0top.r - color0.r) - (color0.r - color0bottom.r)) ) * 0.5f, -1.0f, 1.0f );
   
   vec3 colorlightVector = vec3( normalx, normaly, 1.0-sqrt(normalx*normalx+normaly*normaly) );
   float colorLuminance = dot( colorlightVector, ligthVector );
   //colorlight = vec4( colorLuminance, colorLuminance, colorLuminance, 1.0f );
   colorlight = vec4( (normalx+1.0f)*0.5f, (normaly+1.0f)*0.5f, 0.0f, 1.0f );
	
   float fade_constaux = 1.0f;
   gl_FragColor = (1.0f - fade_constaux) * color0 + fade_constaux * colorlight ;	
	
}