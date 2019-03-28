/*
 * Wad.cpp
 *
 *  Created on: Mar 20, 2019
 *      Author: zacharyfrederick
 */



#include "Wad.h"
#include <fstream>
#include <iostream>

void Wad::read_header(uint8_t *data, struct wad_header &header) {
	for (int i=0; i<4; i++) {
		header.magic += data[i];
	}

	header.num_descriptors = (data[4]<<0) | (data[5]<<8) | (data[6]<<16) | (data[7]<<24);
	header.desc_offset = (data[8]<<0) | (data[9]<<8) | (data[10]<<16) | (data[11]<<24);

}

void Wad::read_descriptor(uint8_t *data, struct descriptor_struct &descriptor, uint32_t offset) {
	descriptor.offset = (data[0+offset]<<0) | (data[1+offset]<<8) | (data[2+offset]<<16) | (data[3+offset]<<24);
	descriptor.length = (data[4+offset]<<0) | (data[5+offset]<<8) | (data[6+offset]<<16) | (data[7+offset]<<24);
	for (int i=8; i < 16; i++) {
		descriptor.name += data[offset+i];
	}
}

void Wad::read_wad_file(string filename) {
	ifstream wadFile(filename, ios::binary | ios::ate);

	if (!wadFile.is_open()) {
		cout << "Error opening file\n";
	}

	streamsize size = wadFile.tellg();
	data = new uint8_t[size];
	wadFile.seekg(0, ios::beg);
	wadFile.read((char*) data, size);
	wadFile.close();

	read_header(data, header);

	for (int i=0; i < header.num_descriptors; i++) {
		struct descriptor_struct temp;
		read_descriptor(data, temp, header.desc_offset + (i*16));
		container.push_back(temp);
		cout << temp.name << "\n";
	}

	print_file_system();
}

void Wad::print_file_system() {
	string path = "/";
	int current_level=0;
	for (int i=0; i < header.num_descriptors;i++) {
		if (is_marker_element(container[i].name)) {
			cout << "Found one: " << container[i].name << "\n";
		}
	}
}


bool Wad::is_marker_element(string name) {


	if (name[0] == 'E' && name[2] == 'M') {
		return true;
	}

	return false;
}

Wad::~Wad(){
	if (data != nullptr) {
		delete[] data;
		data = nullptr;
	}
}
