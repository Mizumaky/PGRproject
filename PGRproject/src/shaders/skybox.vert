#version 140

in vec2 screenCoord;

uniform mat4 inversePVmatrix;

out vec3 texCoord_v;

void main() {
	vec4 farPlaneCoord = vec4(screenCoord, 0.9999, 1.0);
	vec4 wordldViewCoord = inversePVmatrix * farPlaneCoord;
	texCoord_v = wordldViewCoord.xyz / wordldViewCoord.w;
	gl_Position = farPlaneCoord;
}
