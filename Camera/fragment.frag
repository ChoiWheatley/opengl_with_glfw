#version 410 core

out vec4 FragColor;
in vec3 ourColor;	
in vec2 TexCoord;		/*texture coordinate that interpolates the position from
						the texture image source.*/

uniform sampler2D texture1;	/*texture image source*/
uniform sampler2D texture2;

void main() {
	// `texture` function returns filtered color of the texture
	// at the interpolated texture coordinate.
	FragColor = mix(
		texture(texture1, TexCoord),
		texture(texture2, TexCoord),
		0.8
	);
}

