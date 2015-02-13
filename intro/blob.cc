#include "programs.h"
#include "blob.h"

namespace {

const float Z_NEAR = .1;
const float Z_FAR = 1000.;
const float FOV = 45;

const int DENSITY = 32;

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

			vbo_.add_index(v1);
			vbo_.add_index(v2);

			vbo_.add_index(v2);
			vbo_.add_index(v3);

			vbo_.add_index(v3);
			vbo_.add_index(v0);
		}
	}

	vbo_.buffer(GL_STATIC_DRAW);
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

	get_program(PROG_BLOB)->use();
	vbo_.draw(GL_LINES);
}