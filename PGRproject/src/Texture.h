#pragma once
#include "Renderer.h"

class Texture {
private:
	unsigned int m_rendererId;
	std::string m_filePath;
	unsigned char* m_localBuffer;
	int m_width, m_height, m_bitsPerPixel;

public:
	Texture(const std::string& filepath);
	~Texture();

	void bind(const int slot = 0) const;
	void unbind();

	inline int getWidth() const { return m_width; };
	inline int getHeight() const { return m_height; };
};

