#include <unistd.h>
#include <cmath>

#include <memory>

#include <GL/glew.h>

#include <ggl/window.h>

#include "logo.h"

namespace {

class intro_window : public ggl::window
{
public:
	intro_window();

	void init();
	void draw(float t);

private:
	std::unique_ptr<layer> logo_;
};

intro_window::intro_window()
: ggl::window(512, 256, "", false)
, logo_(new logo(width_, height_))
{ }

void
intro_window::draw(float now)
{
	glViewport(0, 0, width_, height_);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	logo_->draw(now);
}

} // namespace

int
main(int argc, char *argv[])
{
	intro_window().run();
}
