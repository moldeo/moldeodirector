uniform sampler2D src_tex_unit0;
uniform vec2 src_tex_offset0;
uniform vec2 tempo_angle;
uniform vec2 dest_tex_size;


void main(void)
{
/*
	glm::mat4 currMat(1.0f);
	currMat = glm::translate(currMat, glm::vec3(0.5f, 0.5f, 0.0f));
	currMat = glm::rotate(currMat, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	currMat = glm::translate(currMat, glm::vec3(-0.5f, -0.5f, 0.0f));


	vec2 texCoord = (rotMatrix * vec4(gl_PointCoord, 0, 1)).xy
*/
    gl_FragColor = texture2D(src_tex_unit0, gl_TexCoord[0].st);
}
