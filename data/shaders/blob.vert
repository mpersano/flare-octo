#define PI 3.14159265

uniform float phase;
uniform float amp;
uniform float radius;

varying vec3 f_normal;

vec3 eval_coord(float phi, float theta)
{
	float offs =
		(amp + 4.*amp*sin(3.*phase + theta))*sin(phase + 5.*phi) + 
		(amp + 4.*amp*sin(2.*phase + 2.*phi))*sin(phase + 3.*theta); 

	float r = radius + offs;

	return r*vec3(-sin(phi)*cos(theta), -sin(phi)*sin(theta), -cos(phi));
}

void main(void)
{
	float phi = gl_Vertex.y*PI;
	float theta = gl_Vertex.x*2.*PI;

	vec3 pos = eval_coord(phi, theta);

	const float epsilon = .01;

	vec3 du = eval_coord(phi + epsilon, theta) - pos;
	vec3 dv = eval_coord(phi, theta + epsilon) - pos;

	vec3 normal = normalize(cross(du, dv));

	gl_Position = gl_ModelViewProjectionMatrix*vec4(pos, 1);
	f_normal = gl_NormalMatrix*normal;
}
