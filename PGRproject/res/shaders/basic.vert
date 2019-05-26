#version 140

in vec4 position;
in vec2 textureCoord;

uniform mat4 u_MVP;

out vec2 v_textureCoord;

void main() {
	gl_Position = u_MVP * position;
	v_textureCoord = textureCoord;
}