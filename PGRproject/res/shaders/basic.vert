#version 140

in vec4 position;
in vec2 textureCoord;

out vec2 v_textureCoord;

void main() {
	gl_Position = position;
	v_textureCoord = textureCoord;
}