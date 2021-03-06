/*
 * Wad2.cpp
 *
 *  Created on: Mar 26, 2019
 *      Author: Zachary
 */

#include "Wad2.h"
#include "Wad.h"
#include <fstream>
#include <iostream>
#include <string>

Wad2::Wad2() {
	zion = new Zion();
}

Wad2::~Wad2() {
	if (raw_data != nullptr) {
		delete[] raw_data;
		raw_data = nullptr;
	}
}

bool Wad2::read_header() {
	for (int i=0; i<4; i++) { header.magic += raw_data[i]; }

	header.num_descriptors 	= (raw_data[4]<<0) | (raw_data[5]<<8) | (raw_data[6]<<16) 	| (raw_data[7]<<24);
	header.desc_offset		= (raw_data[8]<<0) | (raw_data[9]<<8) | (raw_data[10]<<16) 	| (raw_data[11]<<24);

	return true;
}

bool Wad2::read_descriptor(struct descriptor_struct &descriptor, uint32_t offset) {
	descriptor.offset = (raw_data[0+offset]<<0) | (raw_data[1+offset]<<8) | (raw_data[2+offset]<<16) | (raw_data[3+offset]<<24);
	descriptor.length = (raw_data[4+offset]<<0) | (raw_data[5+offset]<<8) | (raw_data[6+offset]<<16) | (raw_data[7+offset]<<24);

	for (int i=8; i < 16; i++) { descriptor.name += raw_data[offset+i]; }

	trim_descr_name(descriptor);
	return true;
}

char* Wad2::getMagic() {
	char magic[5];
	for (int i =0; i < 4; i++) { magic[i]=header.magic[i]; }
	magic[4] = 0;
	return magic;
}

bool Wad2::isContent(const string& path) {
	return zion->is_content(path);
}

bool Wad2::isDirectory(const string& path) {
	return zion->is_directory(path);
}

int Wad2::getSize(const string& path) {
	return zion->get_size(path);
}

int Wad2::getContents(const string& path, char* buffer, int length, int offset) {
	return zion->get_contents(path, buffer, length, offset);
}

int Wad2::getDirectory(const string& path, vector<string>* directory) {
	return zion->get_directory(path, directory);
}

bool Wad2::build_file_system(string filename) {
	int error = read_raw_wad(filename);

	if (error != -1) {
		read_header();

		for (int i=0; i < header.num_descriptors; i++) {
			struct descriptor_struct temp;
			read_descriptor(temp, header.desc_offset + (i*16));
			descriptor_table.push_back(temp);
		}

		zion->create_file_sys(descriptor_table, raw_data);
	} else {
		cout << "Error loading the file using fstream\n";
	}

	return true;
}

int Wad2::read_raw_wad(const string &path) {
	ifstream wadFile(path, ios::binary | ios::ate);

	if (!wadFile.is_open()) {
		cout << "Error opening file\n";
		return -1;
	}

	streamsize size = wadFile.tellg();
	raw_data = new uint8_t[size];

	wadFile.seekg(0, ios::beg);
	wadFile.read((char*) raw_data, size);
	wadFile.close();

	return size;
}

void Wad2::trim_descr_name(struct descriptor_struct& descr) {
	string temp;

	for (int i=0; i < descr.name.length(); i++) {
		if (descr.name.at(i) != 0) {
			temp += descr.name.at(i);
		}
	}

	descr.name = temp;
}

Wad2* Wad2::loadWad(const string &path) {
	Wad2 wad;
	wad.build_file_system(path);
	return &wad;
}
