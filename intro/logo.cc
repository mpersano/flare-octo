#include <cmath>
#include <cstdint>

#include <ggl/pixmap.h>

#include "util.h"
#include "programs.h"
#include "logo.h"

logo::logo(int width, int height)
: layer(width, height)
{
	init_arrows();
	init_arrow_texture();
}

void
logo::init_arrow_texture()
{
	ggl::pixmap pm(256, 64, ggl::pixmap::pixel_type::RGB_ALPHA);

	auto is_inside = [&](const glm::vec2& p, float radius_tail, float radius_head, float x_head, float x_tip) -> bool {
		const float ym = .5f*pm.height;

		float lo, hi;

		if (p.x < x_head) {
			lo = ym - radius_tail;
			hi = ym + radius_tail;
		} else if (p.x < x_tip) {
			float h = radius_head*(1. - (p.x - x_head)/(x_tip - x_head));

			lo = ym - h;
			hi = ym + h;
		} else {
			return false;
		}

		return p.y >= lo && p.y <= hi;
	};

	const float radius_tail = .25*pm.height;
	const float radius_head = .5*pm.height;
	const float x_head = .85*pm.width;
	const float x_tip = pm.width;

	static const int SQRT_SUBSAMPLES = 4;
	static const int NUM_SUBSAMPLES = SQRT_SUBSAMPLES*SQRT_SUBSAMPLES;

	const glm::vec2 dx(1./SQRT_SUBSAMPLES, 0);
	const glm::vec2 dy(0, 1./SQRT_SUBSAMPLES);

	uint32_t *p = reinterpret_cast<uint32_t *>(&pm.data[0]);

	for (int i = 0; i < pm.height; i++) {
		for (int j = 0; j < pm.width; j++) {
			const glm::vec2 pos(j, i);

			int alpha = 0;

			for (int k = 0; k < SQRT_SUBSAMPLES; k++) {
				for (int l = 0; l < SQRT_SUBSAMPLES; l++) {
					glm::vec2 v = pos + static_cast<float>(k)*dx + static_cast<float>(l)*dy;

					alpha += is_inside(v, radius_tail, radius_head, x_head, x_tip);

					// XXX: red,green
				}
			}

			alpha = (alpha*255)/NUM_SUBSAMPLES;

			*p++ = (alpha << 24) | 0xffffff;
		}
	}

	arrow_texture_.load(pm);

	arrow_texture_.set_wrap_s(GL_CLAMP);
	arrow_texture_.set_wrap_t(GL_CLAMP);

	arrow_texture_.set_mag_filter(GL_LINEAR);
	arrow_texture_.set_min_filter(GL_LINEAR);

	arrow_texture_.set_env_mode(GL_MODULATE);
}

void
logo::init_arrows()
{
	// vbo

	const int NUM_SEGMENTS = 20;
	const float THICK = 20;

	for (int i = 0; i < NUM_SEGMENTS; i++) {
		const float t = static_cast<float>(i)/(NUM_SEGMENTS - 1);
		arrow_vbo_.add_vertex({ { t, -THICK }, { t, 0 } });
		arrow_vbo_.add_vertex({ { t, THICK }, { t, 1 } });
	}

	arrow_vbo_.buffer(GL_STATIC_DRAW);

	// arrows

	const int NUM_ARROWS = 20;
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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	arrow_texture_.bind();

	const ggl::program *prog = get_program(PROG_ARROW);
	prog->use();
	prog->set_uniform_i("texture", 0);

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
	ctl_points[1].init(.5f*(from + to), 5.);
	ctl_points[2].init(to, 20.);
}

void
logo::arrow::ctl_point::init(const glm::vec2& center, float shake_length)
{
	origin = center;

	const float a = frand(0, 2.*M_PI);

	a0 = frand(0., 2.*M_PI);
	b0 = frand(1., 3.);
	r0 = frand(.9*shake_length, 1.1*shake_length);

	a1 = frand(0., 2.*M_PI);
	b1 = frand(1., 3.);
	r1 = frand(.9*shake_length, 1.1*shake_length);
}

glm::vec2
logo::arrow::ctl_point::eval(float now) const
{
	return origin + r0*cosf(a0 + b0*now) + r1*sinf(a1 + b1*now);
}
