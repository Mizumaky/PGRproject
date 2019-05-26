#version 140

in vec3 texCoord_v;

uniform samplerCube skyboxSampler;

out vec4 color_f;

void main() {
	color_f = texture(skyboxSampler, texCoord_v);
}