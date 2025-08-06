#ifndef VAO_H
#define VAO_H

#include "VBO.h"

class VAO
{
public:
	GLuint ID;

	VAO();

	void LinkAttrib(VBO VBO, GLuint location, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) const;

	void Bind() const;

	void Unbind() const;

	void Delete();
};

#endif