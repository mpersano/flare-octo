varying vec3 f_normal;

uniform sampler2D texture;

void main(void)
{
	gl_FragColor = texture2D(texture, .5*f_normal.xy + vec2(.5, .5));
}
