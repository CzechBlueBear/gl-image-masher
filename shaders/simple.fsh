// fragment shader

#version 130

in vec4 fragmentPosition;
in vec2 fragmentTextureCoordinates;
out vec4 fragmentColor;
uniform sampler2D s;

void main()
{
	fragmentColor = texture(s, vec2(fragmentTextureCoordinates));
}
