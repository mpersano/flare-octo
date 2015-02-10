#pragma once

#include <GL/glew.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <string>

#include "shader.h"

namespace ggl {

class program
{
public:
	program();
	~program();

	program(const program&) = delete;
	program& operator=(const program&) = delete;

	void attach(const shader& shader) const;
	void attach(GLenum type, const char *path) const;

	void attach_vertex_shader(const char *path) const;
	void attach_fragment_shader(const char *path) const;

	void link() const;

	GLint get_uniform_location(const GLchar *name) const;
	GLint get_attribute_location(const GLchar *name) const;

	class uniform
	{
	public:
		uniform(GLint location)
		: location_(location)
		{ }

		GLfloat operator=(GLfloat v) const
		{ set(v); return v; }

		const glm::vec2& operator=(const glm::vec2& v) const
		{ set(v.x, v.y); return v; }

		const glm::vec3& operator=(const glm::vec3& v) const
		{ set(v.x, v.y, v.z); return v;}

		const glm::vec4& operator=(const glm::vec4& v) const
		{ set(v.x, v.y, v.z, v.w); return v; }

		void set(GLfloat v0) const;
		void set(GLfloat v0, GLfloat v1) const;
		void set(GLfloat v0, GLfloat v1, GLfloat v2) const;
		void set(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const;

		void set(GLint v0) const;
		void set(GLint v0, GLint v1) const;
		void set(GLint v0, GLint v1, GLint v2) const;
		void set(GLint v0, GLint v1, GLint v2, GLint v3) const;

	private:
		GLint location_;
	};

	uniform get_uniform(const GLchar *name) const
	{ return uniform(get_uniform_location(name)); }

	void parameter_i(GLenum name, GLint value);

	void use() const;

	std::string get_info_log() const;

private:
	GLuint id_;
};

}
