#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
	Bind();
};

void VAO::LinkAttrib(VBO VBO, GLuint location, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) const
{
	Bind();
	VBO.Bind();
	glVertexAttribPointer(location, numComponents, type,GL_FALSE, stride, offset);
	glEnableVertexAttribArray(location);
	VBO.Unbind();
	Unbind();
};

void VAO::Bind() const
{
	glBindVertexArray(ID);
};

void VAO::Unbind() const
{
	glBindVertexArray(0);
};

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
};