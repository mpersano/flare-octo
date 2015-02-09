#pragma once

#include <memory>

#include <ggl/program.h>

enum program_id
{
	PROG_ARROW,
	NUM_PROGRAMS,
};

const ggl::program *
get_program(program_id id);
