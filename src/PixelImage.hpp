#ifndef PIXEL_IMAGE_HPP
#define PIXEL_IMAGE_HPP

#include <cstdint>
#include <string>

/**
 * An image represented by a rectangle of pixels, usable for texture loading.
 * @note The PixelImage implementation itself does not do any GL calls
 * so it is guaranteed to keep the GL state intact and can be used even
 * if GL state is not yet set up.
 */
class PixelImage
{
public:

	/**
	 * Format of pixels.
	 */
	enum class Format {

		/**
		 * Used for empty images.
		 */
		EMPTY = 0,

		/**
		 * Each pixel is stored as three consecutive bytes: red, green, blue,
		 * respectively. Pixels are stored without gaps (RGBRGBRGB...)
		 * but each *line* is padded at the end (if necessary) to a whole
		 * multiple of 4 bytes.
		 */
		RGB,

		/**
		 * Each pixel is stored as 4 consecutive bytes: red, green, blue,
		 * and alpha, respectively (intensity from 0 to 255). Pixels are stored
		 * without gaps (RGBARGBARGBA...).
		 */
		RGBA,
	};

	/**
	 * Constructor. The image is initially empty, with zero dimensions
	 * and no pixel data.
	 */
	PixelImage();

	/**
	 * Constructor. The image is loaded from the specified file.
	 * @throw FileLoadingError
	 */
	PixelImage(const std::string &path);

	~PixelImage();

	/**
	 * Returns the width of the image (zero for an empty image,
	 * otherwise always positive).
	 */
	int getWidth() const { return width; }

	/**
	 * Returns the height of the image (zero for an empty image,
	 * otherwise always positive).
	 */
	int getHeight() const { return height; }

	/**
	 * Returns the byte size of a single line of pixels in memory
	 * (as the image is rectangular, all lines have the same size).
	 * This is generally width*bytesPerPixel + optional padding.
	 */
	int getBytesPerLine() const { return bytesPerLine; }

	/**
	 * Returns the pixel format.
	 */
	Format getFormat() const { return format; }

	/**
	 * Returns a pointer to the start of the pixel data,
	 * i.e. to the leftmost pixel on the bottommost line.
	 */
	const void *getData() const { return data; }

	/**
	 * Clears the image, freeing the pixel data and resetting
	 * dimensions to zero. Any pointer returned earlier by getData()
	 * is invalidated.
	 */
	void clear();

	void reset(int width, int height);

	/**
	 * Clears the image and fills it with contents from the file,
	 * possibly adjusting the dimensions and format.
	 * The file is assumed to be a PNG image; loading fails if it is
	 * of a different type.
	 * @return True on success, false on failure.
	 */
	bool loadPng(const std::string &path);

	/**
	 * Clears the image and fills it with contents from the file,
	 * possibly adjusting the dimensions and format.
	 * The file is assumed to be a TIFF image; loading fails if it is
	 * of a different type.
	 * @return True on success, false on failure.
	 */
	bool loadTiff(const std::string &path);

	bool saveTiff(const std::string &path);

	/**
	 * Clears the image and fills it with contents of a rectangle
	 * copied from the screen.
	 */
	void screenshot(int x, int y, int width, int height);

protected:

	/**
	 * Width of the image (in pixels).
	 */
	int width;

	/**
	 * Height of the image (in pixels).
	 */
	int height;

	/**
	 * Number of bytes per line, including any padding.
	 */
	int bytesPerLine;

	/**
	 * Pixel format.
	 */
	Format format;

	/**
	 * Pointer to the start of the pixel data (the bottommost line),
	 * or nullptr if the image is empty.
	 *
	 * Pixels are stored line by line, in left-to right order.
	 * Lines are stored from bottom to top (note that this is the reverse
	 * of natural order of most image format but a natural format for OpenGL).
	 * Lines are padded (if necessary) to a size of multiple of 4 bytes
	 * (required for loading OpenGL textures).
	 */
	uint8_t *data;
};

#endif
