varying vec3 f_normal;

void main(void)
{
	gl_FragColor = vec4(f_normal, 1);
}
