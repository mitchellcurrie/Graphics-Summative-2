#pragma once

#include <vector>
#include <string>

class RAW {

public:

	std::vector<unsigned char> x;
	std::vector<unsigned char> y;
	std::vector<unsigned char> z;

	RAW();

	//create a RAW object and fill it with data stored in fname 
	RAW(const std::string &fname);

	//create an "epmty" RAW image with a given width and height;the R,G,B arrays are filled with zeros
	RAW(const unsigned int _width, const unsigned int _height);

	//read the PPM image from fname
	void Read(const std::string &fname);
	//write the PPM image in fname
	void Write(const std::string &fname);

private:

	void Initialize();

	unsigned int m_iHeight;
	unsigned int m_iWidth;
	unsigned int m_iMax_col_val;

	//total number of elements (pixels)
	unsigned int m_iSize;

	//info about the PPM file (height and width)
	unsigned int nr_lines;
	unsigned int nr_columns;

};