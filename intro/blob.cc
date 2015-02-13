#include <cmath>

#include "programs.h"
#include "blob.h"

namespace {

const float Z_NEAR = .1;
const float Z_FAR = 1000.;
const float FOV = 45;

const int DENSITY = 64;

}

blob::blob(int width, int height)
: layer(width, height)
{
	// vertices

	for (int i = 0; i <= DENSITY; i++) {
		const float u = static_cast<float>(i)/DENSITY;

		for (int j = 0; j <= DENSITY; j++) {
			const float v = static_cast<float>(j)/DENSITY;
			vbo_.add_vertex({ { u, v } });
		}
	}

	// indices

	for (int i = 0; i < DENSITY; i++) {
		for (int j = 0; j < DENSITY; j++) {
			const int v0 = i*(DENSITY + 1) + j;
			const int v1 = (i + 1)*(DENSITY + 1) + j;
			const int v2 = (i + 1)*(DENSITY + 1) + j + 1;
			const int v3 = i*(DENSITY + 1) + j + 1;

			vbo_.add_index(v0);
			vbo_.add_index(v1);
			vbo_.add_index(v2);

			vbo_.add_index(v2);
			vbo_.add_index(v3);
			vbo_.add_index(v0);
		}
	}

	vbo_.buffer(GL_STATIC_DRAW);

	// texture
	
	texture_.load(*ggl::pixmap::load_from_png("data/images/fakephong.png"));

	texture_.set_wrap_s(GL_CLAMP);
	texture_.set_wrap_t(GL_CLAMP);

	texture_.set_mag_filter(GL_LINEAR);
	texture_.set_min_filter(GL_LINEAR);

	texture_.set_env_mode(GL_MODULATE);

}

void
blob::draw(float now) const
{
	const float aspect = static_cast<float>(width_)/height_;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FOV, aspect, Z_NEAR, Z_FAR);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -300);
	glRotatef(10.*now, 1, 0, 0);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	texture_.bind();

	const ggl::program *prog = get_program(PROG_BLOB);

	prog->use();
	prog->get_uniform("phase").set(now);
	prog->get_uniform("amp").set(7.f + 7.f*sinf(.5f*now));
	prog->get_uniform("radius").set(100.f);

	vbo_.draw(GL_TRIANGLES);
}
