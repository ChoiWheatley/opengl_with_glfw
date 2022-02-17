// we are just gonna forward vertex data to shader's output
#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 model, world, view, projection;

void main() {
	/*passing processed vector into `gl_Position`*/
	gl_Position = projection * view * world * model * vec4(aPos, 1.0);		
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}

