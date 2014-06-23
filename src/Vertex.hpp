#ifndef VERTEX_HPP
#define VERTEX_HPP

class SimpleTexturedVertex {
public:

	/** Position of the vertex. */
	float position[3];

	/** Coordinates of the point in the texture to be mapped to this vertex. */
	float textureCoordinates[2];
};

#endif
