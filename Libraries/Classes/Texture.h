#ifndef TEXTURE_H
#define TEXTURE_H


#include <stb/stb_image.h>

#include "Shader.h"

// Texture class for loading, binding, and managing OpenGL textures
class Texture
{
public:
	GLuint ID;      // OpenGL texture ID
	const char* type;    // Texture type (e.g., GL_TEXTURE_2D)
	GLuint unit;

	// Constructor: loads image, creates texture, sets parameters, and generates mipmaps
	Texture(const char* path, GLuint slot);

	// Set texture uniform in shader
	void useTex(Shader& shader, const char* uniform);

	// Bind texture for use
	void Bind();

	// Unbind texture
	void Unbind();

	// Delete texture from GPU
	void Delete();
};

#endif