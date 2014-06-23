// vertex shader

#version 130

in vec3 position;
in vec2 textureCoordinates;
out vec4 fragmentPosition;
out vec2 fragmentTextureCoordinates;

void main()
{
	gl_Position = fragmentPosition = vec4(position, 1.0);
	fragmentTextureCoordinates = textureCoordinates;
}
