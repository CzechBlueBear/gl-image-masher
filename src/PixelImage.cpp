#include <cstdio>
#include <cstring>
#include <iostream>
#include <libpng/png.h>
#include <tiffio.h>
#include <GL/gl.h>
#include "PixelImage.hpp"

PixelImage::PixelImage()
	: width(0), height(0), bytesPerLine(0), format(Format::EMPTY), data(nullptr)
{
}

PixelImage::PixelImage(const std::string &path)
	: PixelImage()
{
	if (path.rfind(".png") == path.size() - 4) {
		loadPng(path);
	}
	else if (path.rfind(".tiff") == path.size() - 5) {
		loadTiff(path);
	}
	else {
        std::cerr << "unrecognized file extension: " << path << std::endl;
	}
}

PixelImage::~PixelImage()
{
	delete[] data;
}

void PixelImage::clear()
{
	delete[] data;
	width = 0;
	height = 0;
	bytesPerLine = 0;
	data = nullptr;
}

void PixelImage::reset(int width, int height)
{
    clear();
    this->width = width;
    this->height = height;
    this->bytesPerLine = width*4;
    this->data = new uint8_t[width*4*height];
}

bool PixelImage::loadPng(const std::string &path)
{
	// This code is based on snippet by David Grayson:
	// http://stackoverflow.com/questions/11296644/loading-png-textures-to-opengl-with-libpng-only

	clear();

    png_byte header[8];

    FILE *fp = fopen(path.c_str(), "rb");
    if (!fp) {
        std::cerr << "error opening file for reading: " << path << std::endl;
    	return false;
    }

    // read the header
    fread(header, 1, 8, fp);

    if (png_sig_cmp(header, 0, 8)) {
        std::cerr << "missing or incorrect PNG header: " << path << std::endl;
        return false;
    }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
    	nullptr, nullptr, nullptr);
    if (!png_ptr) {
        std::cerr << "png_create_read_struct() failed (damaged PNG file?): " << path << std::endl;
        return false;
    }

    // create png info struct
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        std::cerr << "png_create_info_struct() failed (damaged PNG file?): " << path << std::endl;
        return false;
    }

    // create png info struct
    png_infop end_info = png_create_info_struct(png_ptr);
    if (!end_info) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        std::cerr << "png_create_info_struct() failed (damaged PNG file?): " << path << std::endl;
        return false;
    }

    // establish error escape point
    if (setjmp(png_jmpbuf(png_ptr))) {

        // this code will be executed when PNG parsing fails
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        std::cerr << "error in PNG file format (damaged file?): " << path << std::endl;
        return false;
    }

    // init png reading
    png_init_io(png_ptr, fp);

    // let libpng know you already read the first 8 bytes
    png_set_sig_bytes(png_ptr, 8);

    // read all the info up to the image data
    png_read_info(png_ptr, info_ptr);

    // variables to pass to get info
    int bit_depth, colorType;
    png_uint_32 tempWidth, tempHeight;

    // get info about png
    png_get_IHDR(png_ptr, info_ptr, &tempWidth, &tempHeight, &bit_depth, &colorType,
        nullptr, nullptr, nullptr);
    width = tempWidth;
    height = tempHeight;

    if (width <= 0 || height <= 0) {
        std::cerr << "invalid PNG header data (width/height < 0): " << path << std::endl;
        return false;
    }
    if (bit_depth != 8) {
        std::cerr << "unsupported bit depth: " << path << std::endl;
        return false;
    }

    switch (colorType) {
    	case PNG_COLOR_TYPE_RGB:
    		format = Format::RGB;
    		break;

    	case PNG_COLOR_TYPE_RGBA:
    		format = Format::RGBA;
    		break;

    	default:
            std::cerr << "unsupported pixel format: " << path << std::endl;
            return false;
    }

    // Update the png info struct.
    png_read_update_info(png_ptr, info_ptr);

    // Row size in bytes.
    int fileBytesPerLine = png_get_rowbytes(png_ptr, info_ptr);

    // glTexImage2d requires rows to be 4-byte aligned
    bytesPerLine = fileBytesPerLine + 3 - ((fileBytesPerLine-1) % 4);

    // Allocate the image_data as a big block, to be given to opengl
    data = new uint8_t[bytesPerLine * height * sizeof(png_byte)+15];

    // row_pointers is for pointing to image_data for reading the png with libpng
    png_bytep *row_pointers = new png_bytep[height];

    // Set the individual row_pointers to point at the correct offsets
    // in the data block.
    // The natural order of lines in file is reversed so we get the bottommost
    // line first, which is what we need for loading textures.
    int i;
    for (i = 0; i < height; i++) {
        row_pointers[height - 1 - i] = data + i * bytesPerLine;
    }

    // read the png into image_data through row_pointers
    png_read_image(png_ptr, row_pointers);

    // clean up
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    delete[] row_pointers;
    fclose(fp);

    return true;
}

bool PixelImage::loadTiff(const std::string &path)
{
	clear();

	TIFF *tif = TIFFOpen(path.c_str(), "r");
	if (!tif) {
        std::cerr << "could not open file for reading: " << path << std::endl;
        return false;
    }

	uint32_t tifWidth = 0;
	uint32_t tifHeight = 0;
	TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &tifWidth);
	TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &tifHeight);
	if (tifWidth <= 0 || tifHeight <= 0) {
		TIFFClose(tif);
        std::cerr << "invalid width/height in TIFF header: " << path << std::endl;
    }

	uint32_t pixelCount = tifWidth * tifHeight;
	uint32_t *pixels = new uint32_t[pixelCount];

	if (!TIFFReadRGBAImage(tif, tifWidth, tifHeight, pixels)) {
		TIFFClose(tif);
		delete[] pixels;
        std::cerr << "error reading TIFF pixel data: " << path << std::endl;
        return false;
	}

	TIFFClose(tif);

	width = tifWidth;
	height = tifHeight;

    // note that TIFF is naturally in bottom-to-up format
	data = reinterpret_cast<uint8_t*>(pixels);

	format = Format::RGBA;     // FIXME: is this endian-dependent or not?
    return true;
}

bool PixelImage::saveTiff(const std::string &path)
{
    TIFF *tif = TIFFOpen(path.c_str(), "w");
    if (!tif) {
        std::cerr << "could not open file for writing: " << path << std::endl;
        return false;
    }

    TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, width);
    TIFFSetField(tif, TIFFTAG_IMAGELENGTH, height);

    // bottom to top organization
    TIFFSetField(tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
    TIFFSetField(tif, TIFFTAG_COMPRESSION, COMPRESSION_NONE);

    // contiguous (not stripped, not tiled)
    TIFFSetField(tif, TIFFTAG_ROWSPERSTRIP, TIFFDefaultStripSize(tif, width*4));
    //TIFFSetField(tif, TIFFTAG_ROWSPERSTRIP, -1L);

    // RGB, 8 bits per component, each pixel stored as 3 consecutive values
    TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
    TIFFSetField(tif, TIFFTAG_FILLORDER, FILLORDER_MSB2LSB);
    TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
    TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 4);
    TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);
    TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);
    TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);
    TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);

    // resolution; FIXME: what is the correct resolution?
    TIFFSetField(tif, TIFFTAG_XRESOLUTION, 100.0);
    TIFFSetField(tif, TIFFTAG_YRESOLUTION, 100.0);
    TIFFSetField(tif, TIFFTAG_RESOLUTIONUNIT, RESUNIT_INCH);

    uint8_t *line;
    int i;
    for (i = 0, line = data; i < height; i++, line += bytesPerLine){
        TIFFWriteScanline(tif, line, i, 0);
    }

    TIFFClose(tif);
    return true;
}

void PixelImage::screenshot(int x, int y, int width, int height)
{
    clear();
    this->width = width;
    this->height = height;
    this->bytesPerLine = width*4;
    this->data = new uint8_t[width*4*height];
    glReadPixels(x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
}
