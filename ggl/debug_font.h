#pragma once

#include "texture.h"

namespace ggl {

class debug_font
{
public:
	debug_font();

	void draw_string(float x, float y, const char *str) const;
	void draw_string_fmt(float x, float y, const char *fmt, ...) const;

private:
	texture texture_;
};

}
