#pragma once

class layer
{
public:
	layer(int width, int height)
	: width_(width), height_(height)
	{ }

	virtual ~layer() { }

	virtual void draw(float now) const = 0;

protected:
	int width_, height_;
};
