#include "Texture.h"
#include "external/stb_image/stb_image.h"

Texture::Texture(const std::string& filepath) {
	m_rendererId = 0;
	m_filePath = filepath;
	m_localBuffer = nullptr; //TODO if i wont be using it, i can make it local in this function and just stbi_image_free(m_localBuffer) at the end
	m_width = 0;
	m_height = 0;
	m_bitsPerPixel = 0;

	stbi_set_flip_vertically_on_load(1); //flips the orientation of the input texture 
	m_localBuffer = stbi_load(filepath.c_str(), &m_width, &m_height, &m_bitsPerPixel, 4); //desired channels - we want RGBA = 4

	//generete and bind
	glGenTextures(1, &m_rendererId);
	glBindTexture(GL_TEXTURE_2D, m_rendererId);

	//TODO in future watch video about mipmapping and other stuff setting here
	//u need to specify these:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //setting the minification filter (if it needs to be scaled down) [can also use eg GL_NEAREST)]
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //setting the magnification filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//set
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer); //u toho rgba - je dobre specifikovat kolik bitu per channel, vezme to i bez te osmicky, ale...
	//unbind
	glBindTexture(GL_TEXTURE_2D, 0);
	CHECK_GL_ERROR();
}
Texture::~Texture() {
	glDeleteTextures(1, &m_rendererId);
	CHECK_GL_ERROR();
}
void Texture::bind(const int slot) const {
	glActiveTexture(GL_TEXTURE0 + slot); //sets the next bound texture to be bound to this slot
	glBindTexture(GL_TEXTURE_2D, m_rendererId);
	CHECK_GL_ERROR();
}
void Texture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
	CHECK_GL_ERROR();
}
