#define KERNEL_SIZE 9

// Sharpen kernel
// -1 -1 -1
// -1 +9 -1
// -1 -1 -1
float kernel[KERNEL_SIZE];

uniform sampler2D src_tex_unit0;
uniform vec2 src_tex_offset0;
uniform vec2 tempo_angle;

vec2 offset[KERNEL_SIZE];

void main(void)
{
    int i = 0;
    vec4 sum = vec4(0.0);

    offset[0] = vec2(-src_tex_offset0.s, -src_tex_offset0.t);
	offset[0] = vec2(-src_tex_offset0.s*2, -src_tex_offset0.t);
    offset[1] = vec2(0.0, -src_tex_offset0.t);
    offset[2] = vec2(src_tex_offset0.s, -src_tex_offset0.t);

    offset[3] = vec2(-src_tex_offset0.s, 0.0);
    offset[4] = vec2(0.0, 0.0);
    offset[5] = vec2(src_tex_offset0.s, 0.0);

    offset[6] = vec2(-src_tex_offset0.s, src_tex_offset0.t);
    offset[7] = vec2(0.0, src_tex_offset0.t);
    offset[8] = vec2(src_tex_offset0.s, src_tex_offset0.t);

    kernel[0] = -1.0;   kernel[1] = -1.0;   kernel[2] = -1.0;
    kernel[3] = -1.0;   kernel[4] = +9.0;   kernel[5] = -1.0;
    kernel[6] = -1.0;   kernel[7] = -1.0;   kernel[8] = -1.0;

	/*
    for(i = 0; i < KERNEL_SIZE; i++)
    {
        vec4 tmp = texture2D(src_tex_unit0, gl_TexCoord[0].st + offset[i]);
        sum += tmp * kernel[i];
    }
	*/
	
	
	vec4 pixel = texture2D(src_tex_unit0, gl_TexCoord[0].st + offset[4]);
	float alpha_final = 0.5;
	float alpha_pixel = pixel.a;
	
	vec4 left = texture2D(src_tex_unit0, gl_TexCoord[0].st + offset[3] );
	vec4 left2 = texture2D(src_tex_unit0, gl_TexCoord[0].st + offset[3]*2 );
	vec4 left3 = texture2D(src_tex_unit0, gl_TexCoord[0].st + offset[3]*3 );
	vec4 right = texture2D(src_tex_unit0, gl_TexCoord[0].st + offset[5] );
	vec4 right2 = texture2D(src_tex_unit0, gl_TexCoord[0].st + offset[5]*2 );
	vec4 right3 = texture2D(src_tex_unit0, gl_TexCoord[0].st + offset[5]*3 );
	vec4 up = texture2D(src_tex_unit0, gl_TexCoord[0].st + offset[1] );
	vec4 down = texture2D(src_tex_unit0, gl_TexCoord[0].st + offset[7] );
	
	
	float alpha_left = left.a;
	float alpha_left2 = left2.a;
	float alpha_left3 = left3.a;
	float alpha_right = right.a;
	float alpha_right2 = right2.a;
	float alpha_right3 = right3.a;
	float alpha_up = up.a;
	float alpha_down = down.a;
	float d_max = 0.0;
	float d_top = 0.05;
	
	if ( alpha_pixel > 0.5 ) {
		
		//HORIZONTAL
		//left border
		float d_left = abs(alpha_left - alpha_pixel);	
		if ( d_left > d_top ) { 
			alpha_final = ( alpha_pixel + alpha_left ) / 2; d_max = d_left; 			
		} else {
			float d_left2 = abs(alpha_left2 - alpha_pixel);	
			if ( d_left2 > d_top ) { 
				alpha_final = ( alpha_pixel + alpha_left2 ) / 6; d_max = d_left2; 
			} else {
				float d_left3 = abs(alpha_left3 - alpha_pixel);	
				if ( d_left3 > d_top ) { alpha_final = ( alpha_pixel + alpha_left3 ) / 8; d_max = d_left3; }	
			}
		}
		
		//right border
		float d_right = abs(alpha_right - alpha_pixel);	
		if ( d_right > d_top && d_right>d_max) { 
			alpha_final = ( alpha_pixel + alpha_right )/2; d_max = d_right; 
		} else {
			float d_right2 = abs(alpha_right2 - alpha_pixel);	
			if ( d_right2 > d_top && d_right2>d_max) { 
				alpha_final = ( alpha_pixel + alpha_right2 )/4; d_max = d_right2; 
			} else {
				float d_right3 = abs(alpha_right3 - alpha_pixel);	
				if ( d_right3 > d_top && d_right3>d_max) { alpha_final = ( alpha_pixel + alpha_right3 )/8; d_max = d_right3; }
			}
		}
		
/*
		//VERTICAL
		//up border
		float d_up = abs(alpha_up - alpha_pixel);	
		if ( d_up > d_top && d_up>d_max) { alpha_final = (alpha_pixel+alpha_up)/2.0;  d_max = d_up; }
		//down border
		float d_down = abs(alpha_down - alpha_pixel);	
		if ( d_down > d_top && d_down>d_max) { alpha_final = ( alpha_pixel + alpha_down )/2;   d_max = d_down; }
		
		*/
		
		
		if (d_max>d_top) {
			//gl_FragColor = vec4( 1.0, 0.0, 0.0, 1.0 );
			//gl_FragColor = vec4( 1.0*d_left, 0.0, 0.0, 1.0 );
			gl_FragColor = vec4(pixel.rgb, alpha_final );
		} else {
			alpha_final = alpha_pixel;
			gl_FragColor = vec4(pixel.rgb, alpha_final);
		}
		
		//gl_FragColor = vec4( max( 1.0-d_left, 0.0) , max(1.0-d_left,0.0), max(1.0-d_left,0.0), 1.0);
	} else {
		alpha_final = alpha_pixel;
		gl_FragColor = vec4(pixel.rgb, alpha_final);
		//gl_FragColor = vec4(pixel.rgb, 1.0);
		//gl_FragColor = vec4( 1.0, 1.0, 1.0, 1.0);
	}
	
	
    
	//gl_FragColor = vec4( alpha_pixel, alpha_pixel, alpha_pixel, alpha_final);
}




