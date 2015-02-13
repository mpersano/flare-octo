#pragma once

#include <ggl/vertex_array.h>

#include "layer.h"

class blob : public layer
{
public:
	blob(int width, int height);

	void draw(float now) const;

private:
	ggl::indexed_vbo<GLuint, ggl::vertex_flat<GLfloat, 2>> vbo_;
};
