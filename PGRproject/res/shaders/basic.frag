#version 140

in vec2 v_textureCoord;

uniform vec4 u_color;
uniform sampler2D u_texture;

out vec4 color;

void main() {
	vec4 textureColor = texture(u_texture, v_textureCoord);
	color = mix(u_color, textureColor, textureColor.a); 
}