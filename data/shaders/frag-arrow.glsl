struct arrow
{
	float s0, s1;
	float t0, t1;
};

uniform arrow outer, inner;

bool is_inside(in arrow a)
{
	float t_lo, t_hi;

	if (gl_TexCoord[0].s < a.s0) {
		t_lo = .5 - a.t0;
		t_hi = .5 + a.t0;
	} else if (gl_TexCoord[0].s < a.s1) {
		float h = .5*a.t1*(1. - ((gl_TexCoord[0].s - a.s0)/(a.s1 - a.s0)));

		t_lo = .5 - h;
		t_hi = .5 + h;
	} else {
		return false;
	}

	return gl_TexCoord[0].t >= t_lo && gl_TexCoord[0].t <= t_hi;
}

void main(void)
{
	if (!is_inside(outer))
		discard;

	vec4 color;

	if (is_inside(inner))
		color = vec4(1, 1, 1, 1);
	else
		color = vec4(.5, .5, .5, 1);

	gl_FragColor = color;
}
