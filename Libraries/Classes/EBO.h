#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>
#include <vector>

class EBO
{
public:
	GLuint ID;

	EBO(GLuint* indices, GLsizeiptr size);
	EBO(std::vector<unsigned int> indices);

	void Bind() const;

	void Unbind() const;

	void Delete();
};


#endif