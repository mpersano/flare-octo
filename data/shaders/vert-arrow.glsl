// quadratic bezier

uniform vec2 p0, p1, p2;

vec2
eval_position(float u)
{
	float w0 = (1. - u)*(1. - u);
	float w1 = 2.*u*(1. - u);
	float w2 = u*u;

	return p0*w0 + p1*w1 + p2*w2;
}

vec2
eval_direction(float u)
{
	float w0 = 2.*(u - 1.);
	float w1 = 2.*(1. - 2.*u);
	float w2 = 2.*u;

	return p0*w0 + p1*w1 + p2*w2;
}

void main(void)
{
	float t = gl_Vertex.x;
	float l = gl_Vertex.y;

	vec2 p = eval_position(t);
	vec2 d = eval_direction(t);

	vec2 n = normalize(vec2(-d.y, d.x));

	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = gl_ModelViewProjectionMatrix*vec4(p + l*n, 0., 1.);
}
