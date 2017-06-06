#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

#include "RAW.h"

//init with default values

void RAW::Initialize() {

	m_iWidth = 0;
	m_iHeight = 0;
	m_iMax_col_val = 255;

}

//create a PPM object

RAW::RAW() {
	Initialize();
}

//create a PPM object and fill it with data stored in fname 

RAW::RAW(const std::string &fname) {
	Initialize();
	Read(fname);
}

//create an "epmty" PPM image with a given width and height;the R,G,B arrays are filled with zeros

RAW::RAW(const unsigned int _width, const unsigned int _height) {

	Initialize();
	m_iWidth = _width;
	m_iHeight = _height;
	nr_lines = m_iHeight;
	nr_columns = m_iWidth;
	m_iSize = m_iWidth*m_iHeight;

	// fill r, g and b with 0
	x.resize(m_iSize);
	y.resize(m_iSize);
	z.resize(m_iSize);

}

//read the PPM image from fname

void RAW::Read(const std::string &fname) {
	std::ifstream inp(fname.c_str(), std::ios::in | std::ios::binary);
	if (inp.is_open()) {
		std::string line;
		std::getline(inp, line);
		if (line != "P6") {
			std::cout << "Error. Unrecognized file format." << std::endl;
			return;
		}
		std::getline(inp, line);
		while (line[0] == '#') {
			std::getline(inp, line);
		}
		std::stringstream dimensions(line);

		try {
			dimensions >> m_iWidth;
			dimensions >> m_iHeight;
			nr_lines = m_iHeight;
			nr_columns = m_iWidth;
		} catch (std::exception &e) {
			std::cout << "Header file format error. " << e.what() << std::endl;
			return;
		}

		std::getline(inp, line);
		std::stringstream max_val(line);
		try {
			max_val >> m_iMax_col_val;
		} catch (std::exception &e) {
			std::cout << "Header file format error. " << e.what() << std::endl;
			return;
		}

		m_iSize = m_iWidth*m_iHeight;

		x.reserve(m_iSize);
		y.reserve(m_iSize);
		z.reserve(m_iSize);

		char aux;
		for (unsigned int i = 0; i < m_iSize; ++i) {
			inp.read(&aux, 1);
			x[i] = (unsigned char)aux;
			inp.read(&aux, 1);
			y[i] = (unsigned char)aux;
			inp.read(&aux, 1);
			z[i] = (unsigned char)aux;
		}
	}
	else {
		std::cout << "Error. Unable to open " << fname << std::endl;
	}
	inp.close();
}

//write the PPM image in fname

void RAW::Write(const std::string &fname) {
	std::ofstream inp(fname.c_str(), std::ios::out | std::ios::binary);
	if (inp.is_open()) {

		inp << "P6\n";
		inp << m_iWidth;
		inp << " ";
		inp << m_iHeight << "\n";
		inp << m_iMax_col_val << "\n";

		char aux;
		for (unsigned int i = 0; i < m_iSize; ++i) {
			aux = (char)x[i];
			inp.write(&aux, 1);
			aux = (char)y[i];
			inp.write(&aux, 1);
			aux = (char)z[i];
			inp.write(&aux, 1);
		}
	}
	else {
		std::cout << "Error. Unable to open " << fname << std::endl;
	}
	inp.close();
}
