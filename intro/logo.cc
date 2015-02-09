#include <cmath>

#include "programs.h"
#include "logo.h"

logo::logo(int width, int height)
: layer(width, height)
{
	const int num_segments = 20;
	const float dt = 1./(num_segments - 1);

	const float thick = 20;

	float t = 0;

	for (int i = 0; i < num_segments; i++) {
		vbo_.add_vertex({ { t, -thick }, { t, 0 } });
		vbo_.add_vertex({ { t, thick }, { t, 1 } });

		t += dt;
	}

	vbo_.buffer(GL_STATIC_DRAW);
}

void
logo::draw(float now) const
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width_, 0, height_, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	const ggl::program *prog = get_program(PROG_ARROW);

	prog->use();

	prog->set_uniform_f("p0", 10, 100);
	prog->set_uniform_f("p1", 100 + 10.*sinf(2.*now), 200 + 120.*cosf(3.*now));
	prog->set_uniform_f("p2", 200 + 15.*cosf(.5 + 3.*now), 100 + 30.*cosf(5.*now));

	prog->set_uniform_f("thick", .2);
	prog->set_uniform_f("head", .85);

	vbo_.draw(GL_TRIANGLE_STRIP);
}
