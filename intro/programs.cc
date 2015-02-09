#include <cstdio>

#include "programs.h"

namespace {

std::string
get_shader_path(const char *basename)
{
	std::string str("data/shaders/");
	str.append(basename);
	return str;
}

struct program_manager
{
	program_manager();

	program_manager(const program_manager&) = delete;
	program_manager& operator=(const program_manager&) = delete;

	const ggl::program *get(program_id id) const
	{ return programs_[id].get(); }

	std::unique_ptr<ggl::program> programs_[NUM_PROGRAMS];
};

program_manager::program_manager()
{
	struct {
		const char *vertex_shader;
		const char *frag_shader;
	} program_sources[] = {
		{ "vert-arrow.glsl", "frag-arrow.glsl" },
	};

	for (int i = 0; i < NUM_PROGRAMS; i++) {
		const auto& p = program_sources[i];

		std::unique_ptr<ggl::program> prog(new ggl::program);

		prog->attach_vertex_shader(get_shader_path(p.vertex_shader).c_str());
		prog->attach_fragment_shader(get_shader_path(p.frag_shader).c_str());
		prog->link();

		programs_[i] = std::move(prog);
	}
}

}

const ggl::program *
get_program(program_id id)
{
	static program_manager pm;

	return pm.get(id);
}
