#pragma once

#include "layer.h"

#include <ggl/vertex_array.h>

#include <glm/vec2.hpp>

class logo : public layer
{
public:
	logo(int width, int height);

	void draw(float now) const;

private:
	void draw_arrows(float now) const;

	struct arrow {
		arrow(const glm::vec2& from, const glm::vec2& to);

		struct ctl_point {
			void init(const glm::vec2& center, float shake_length);

			glm::vec2 eval(float now) const;
			glm::vec2 origin, shake_dir;
			float phi, theta; // lol
		};

		ctl_point ctl_points[3]; 
	};

	std::vector<std::unique_ptr<arrow>> arrows_;
	ggl::vbo<ggl::vertex_texcoord<GLfloat, 2, GLfloat, 2>> arrow_vbo_;
};