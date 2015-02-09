uniform float head;
uniform float thick;

void main(void)
{
	float t_lo, t_hi;

	if (gl_TexCoord[0].s < head) {
		t_lo = .5 - thick;
		t_hi = .5 + thick;
	} else {
		t_lo = .5*(gl_TexCoord[0].s - head)/(1. - head);
		t_hi = 1. - t_lo;
	}

	if (gl_TexCoord[0].t < t_lo || gl_TexCoord[0].t > t_hi)
		discard;

	gl_FragColor = vec4(1, 1, 1, 1);
}
