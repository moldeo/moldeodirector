
uniform sampler2D src_tex_unit0;
uniform vec2 src_tex_offset0;
uniform vec2 tempo_angle;
uniform float fade_const;

const vec3 coef= vec3(0.2125, 0.7154, 0.0721);

uniform mat4 par_mat4;

/*
** Hue, saturation, luminance
*/

vec3 RGBToHSL(vec3 color)
{
	vec3 hsl; // init to 0 to avoid warnings ? (and reverse if + remove first part)
	
	float fmin = min(min(color.r, color.g), color.b);    //Min. value of RGB
	float fmax = max(max(color.r, color.g), color.b);    //Max. value of RGB
	float delta = fmax - fmin;             //Delta RGB value

	hsl.z = (fmax + fmin) / 2.0; // Luminance

	if (delta == 0.0)		//This is a gray, no chroma...
	{
		hsl.x = 0.0;	// Hue
		hsl.y = 0.0;	// Saturation
	}
	else                                    //Chromatic data...
	{
		if (hsl.z < 0.5)
			hsl.y = delta / (fmax + fmin); // Saturation
		else
			hsl.y = delta / (2.0 - fmax - fmin); // Saturation
		
		float deltaR = (((fmax - color.r) / 6.0) + (delta / 2.0)) / delta;
		float deltaG = (((fmax - color.g) / 6.0) + (delta / 2.0)) / delta;
		float deltaB = (((fmax - color.b) / 6.0) + (delta / 2.0)) / delta;

		if (color.r == fmax )
			hsl.x = deltaB - deltaG; // Hue
		else if (color.g == fmax)
			hsl.x = (1.0 / 3.0) + deltaR - deltaB; // Hue
		else if (color.b == fmax)
			hsl.x = (2.0 / 3.0) + deltaG - deltaR; // Hue

		if (hsl.x < 0.0)
			hsl.x += 1.0; // Hue
		else if (hsl.x > 1.0)
			hsl.x -= 1.0; // Hue
	}

	return hsl;
}

float HueToRGB(float f1, float f2, float hue)
{
	if (hue < 0.0)
		hue += 1.0;
	else if (hue > 1.0)
		hue -= 1.0;
	float res;
	if ((6.0 * hue) < 1.0)
		res = f1 + (f2 - f1) * 6.0 * hue;
	else if ((2.0 * hue) < 1.0)
		res = f2;
	else if ((3.0 * hue) < 2.0)
		res = f1 + (f2 - f1) * ((2.0 / 3.0) - hue) * 6.0;
	else
		res = f1;
	return res;
}


vec3 HSLToRGB(vec3 hsl)
{
	vec3 rgb;
	
	if (hsl.y == 0.0)
		rgb = vec3(hsl.z); // Luminance
	else
	{
		float f2;
		
		if (hsl.z < 0.5)
			f2 = hsl.z * (1.0 + hsl.y);
		else
			f2 = (hsl.z + hsl.y) - (hsl.y * hsl.z);
			
		float f1 = 2.0 * hsl.z - f2;
		
		rgb.r = HueToRGB(f1, f2, hsl.x + (1.0/3.0));
		rgb.g = HueToRGB(f1, f2, hsl.x);
		rgb.b= HueToRGB(f1, f2, hsl.x - (1.0/3.0));
	}
	
	return rgb;
}

// These parameter values are guesses - you'll need to tweak them


float ComputeOpacity(float hue, float saturation, float lightness) {    
		
	float target_hue = 0.53f;
	float tolerance_hue = 0.03f;
	float tolerance_lum = 0.03f;
	float tolerance_sat = 0.03f;
	float min_saturation = 0.3f;
	float min_lightness = 0.1f;
	float max_lightness = 0.9f;

	if (saturation < min_saturation) return 1.0f;    
	if (lightness < min_lightness) return 1.0f;    
	if (lightness > max_lightness) return 1.0f;    
	
	float delta_hue = abs(hue - target_hue);    
	
	float opacity = 1.0f - (delta_hue / tolerance_hue);    
	if (opacity < 0.0f) opacity = 0.0f;    
	return opacity;
}


void main(void)
{
    vec2 coord0 = gl_TexCoord[0].st;
	
	float src_intensity;

	vec4 src_color = texture2D(src_tex_unit0, coord0);
	//vec4 src_l_color = texture2D(src_tex_unit0, coord0 - vec2());
	//vec3 back_color = vec3( 53.0 / 255.0, 198.0/255.0, 96.0 / 255.0 );
	
	vec3 back_color = vec3( 49.0 / 255.0, 187.0/255.0, 84.0 / 255.0 );
	vec3 back_color_HSL = RGBToHSL(back_color);
	
	vec3 src_color_RGB = src_color.rgb;
	vec3 src_color_HSL = RGBToHSL(src_color_RGB);
	
	
	float delta_hue = abs(src_color_HSL.r - back_color_HSL.r);
	float delta_sat = abs(src_color_HSL.g - back_color_HSL.g);
	float delta_lum = abs(src_color_HSL.b - back_color_HSL.b);
	
	vec3 dist = back_color - src_color.rgb;
	
	float delta_color = sqrt(dist.x*dist.x + dist.y*dist.y + dist.z*dist.z);
	
	//float delta_color_HSL = 
	
	//gl_FragColor = vec4( d4, d4, d4, 1.0 );
	
	//if ( d4 > 0.2 ) {
	//	gl_FragColor = vec4( src_color.rgb, 1.0);	
	//} else {
	//	gl_FragColor = vec4( src_color.rgb, 1.0f - ( d4 / 0.2 )  );
	//}
	
	float d4 =0.0;
	
	//d4 = delta_hue;	
	//d4 = delta_sat;
	//d4 = delta_lum;
	//d4 = delta_color;	
	//gl_FragColor = vec4( d4, d4, d4, 1.0);		
	//gl_FragColor = vec4( src_color.rgb, 1.0f - ( d4 / 0.2 )  );

	float d_color = (delta_hue*2 + delta_sat*2 + delta_lum*2) / 6.0;
	
	float d_color_l = (delta_hue*1 + delta_sat*1 + delta_lum*3) / 5.0;
	
	float d_color_h = (delta_hue*5 + delta_sat*1 + delta_lum*1) / 7.0;
	
	float d_color_s = (delta_hue*4 + delta_sat*4 + delta_lum*1) / 9.0;
	
	float alpha = 1.0;
	float tolerance_hue = 0.1;
		
	
	//colores muy desaturados (grises, blancos y negros) : entran de una
	if ( src_color_HSL.g < 0.2 ) {			
	
		alpha = 1.0f;

		//violeta: grises,blancos,negros: fadear...
		
		if ( d_color < 0.01 ) {
			//alpha = 1.0 - 0.2 * d_color/0.01;
			gl_FragColor = vec4( 1.0, 0.0, 1.0, 1.0 );
		} else gl_FragColor = vec4( 0.0, 1.0, 1.0, 1.0 );
		//
		/*
		if (src_color_HSL.b > 0.43 ) {
			gl_FragColor = vec4( src_color_HSL.b, 0, src_color_HSL.b, alpha );
		}
		*/
	} else {			
		
		
			//TONOS OSCUROS
			if ( src_color_HSL.b < 0.22 ) {

				alpha = 1.0f;
				
				//si la saturacion del color sube: tener en cuenta el chroma
				if ( d_color < 0.01 ) {
					//alpha = d_color/0.01;
					alpha = 0.0;
				}
								
				//marron: oscuros
				gl_FragColor = vec4( 0.0, 0.0, 0, 1.0 );
				
			} else {
				
				//TONOS CLAROS
				if (src_color_HSL.b > 0.93 ) {						
					alpha = 1.0f;
				
					//TONOS MUY CLAROS SE VEN MAS...
					
					if ( delta_hue < 0.02 && src_color_HSL.g > 0.4 ) {
						alpha = 1.0*d_color_l;
					}
					
				
					//amarillo: claros
					gl_FragColor = vec4( 1, 1, 1, 1.0 );
					
				} else {
					//AQUI ENTRAN LOS TONOS MEDIOS
				
					if ( delta_hue < 0.1 ) {
						
						//CERCANOS AL VERDE: azul
						gl_FragColor = vec4( 0.0, 0.0, 1.0, 1.0 );
						
						alpha = 0.0f;	
													
						//alpha = 1.0*d_color_l;
					} else {
						//OPACO: TONOS MEDIOS LEJANOS AL chroma
						alpha = 1.0;

						if ( delta_hue<0.2 ) {
							alpha = delta_hue/0.2;
						} else {
							alpha = 1.0;
						}
						
						//rojo: opaco por lejania de chroma
						gl_FragColor = vec4( 1.0, 0, 0, 1.0 );
					}	
				}			
			}
	}	
		
	if (alpha<0.0f) alpha = 0.0f;
	if (alpha>1.0f) alpha = 1.0f;
	gl_FragColor = vec4( src_color.rgb, alpha );
	
	
	
	
	
	//d4 = src_color_HSL.r;
	//d4 = src_color_HSL.g;
	//d4 = src_color_HSL.b;
	//float alpha = ComputeOpacity(src_color_HSL.r,src_color_HSL.g,src_color_HSL.b);
	
	//gl_FragColor = vec4( d_color,d_color,d_color, 1.0 );
}
