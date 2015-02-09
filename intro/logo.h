#pragma once

#include "layer.h"

#include <ggl/vertex_array.h>

class logo : public layer
{
public:
	logo(int width, int height);

	void draw(float now) const;

private:
	ggl::vbo<ggl::vertex_texcoord<GLfloat, 2, GLfloat, 2>> vbo_;
};
