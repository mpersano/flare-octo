#include <cmath>

#include "util.h"
#include "programs.h"
#include "logo.h"

logo::logo(int width, int height)
: layer(width, height)
{
	// arrow vbo

	const int NUM_SEGMENTS = 20;
	const float THICK = 20;

	for (int i = 0; i < NUM_SEGMENTS; i++) {
		const float t = static_cast<float>(i)/(NUM_SEGMENTS - 1);
		arrow_vbo_.add_vertex({ { t, -THICK }, { t, 0 } });
		arrow_vbo_.add_vertex({ { t, THICK }, { t, 1 } });
	}

	arrow_vbo_.buffer(GL_STATIC_DRAW);

	// arrows

	const int NUM_ARROWS = 15;
	const float RADIUS = 120.;

	const glm::vec2 ORIGIN(.5f*width_, .5f*height_);

	for (int i = 0; i < NUM_ARROWS; i++) {
		const float a = 2.f*M_PI*(static_cast<float>(i)/NUM_ARROWS);

		const float s = sinf(a);
		const float c = cosf(a);

		arrows_.push_back(std::unique_ptr<arrow>(new arrow(ORIGIN, ORIGIN + glm::vec2(s, c)*RADIUS)));
	}
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

	prog->set_uniform_f("outer.t0", .2);
	prog->set_uniform_f("outer.t1", 1.);
	prog->set_uniform_f("outer.s0", .85);
	prog->set_uniform_f("outer.s1", 1.);

	prog->set_uniform_f("inner.t0", .1);
	prog->set_uniform_f("inner.t1", .7);
	prog->set_uniform_f("inner.s0", .87);
	prog->set_uniform_f("inner.s1", .97);

	for (const auto& arrow : arrows_) {
		const glm::vec2 p0 = arrow->ctl_points[0].eval(now);
		const glm::vec2 p1 = arrow->ctl_points[1].eval(now);
		const glm::vec2 p2 = arrow->ctl_points[2].eval(now);

		prog->set_uniform_f("p0", p0.x, p0.y);
		prog->set_uniform_f("p1", p1.x, p1.y);
		prog->set_uniform_f("p2", p2.x, p2.y);

		arrow_vbo_.draw(GL_TRIANGLE_STRIP);
	}
}

logo::arrow::arrow(const glm::vec2& from, const glm::vec2& to)
{
	ctl_points[0].init(from, 5.);
	ctl_points[1].init(.5f*(from + to), 80.);
	ctl_points[2].init(to, 20.);
}

void
logo::arrow::ctl_point::init(const glm::vec2& center, float shake_length)
{
	origin = center;

	const float a = frand(0, 2.*M_PI);
	shake_dir = shake_length*glm::vec2(sinf(a), sinf(a));
	phi = frand(3., 5.);
	theta = frand(3., 5.);
}

glm::vec2
logo::arrow::ctl_point::eval(float now) const
{
	return origin + shake_dir*cosf(phi + theta*now);
}
