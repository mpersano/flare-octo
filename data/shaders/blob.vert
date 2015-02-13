#define PI 3.14159265

const float phase = .1;
const float amp = 10.;

vec3 eval_coord(float phi, float theta)
{
	float offs =
		(amp + 4.*amp*sin(3.*phase + theta))*sin(phase + 5.*phi) + 
		(amp + 4.*amp*sin(2.*phase + 2.*phi))*sin(phase + 3.*theta); 

	float r = 100. + offs;

	return r*vec3(-sin(phi)*cos(theta), -sin(phi)*sin(theta), -cos(phi));
}

void main(void)
{
	float phi = gl_Vertex.y*PI;
	float theta = gl_Vertex.x*2.*PI;

	vec3 pos = eval_coord(phi, theta);

	gl_Position = gl_ModelViewProjectionMatrix*vec4(pos, 1);
}
