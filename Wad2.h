/*
 * Wad2.h
 *
 *  Created on: Mar 26, 2019
 *      Author: Zachary
 */

#ifndef WAD2_H_
#define WAD2_H_

#include "Wad.h"
#include "Zion.h"

#include <vector>
#include <string>

using namespace std;

class Wad2 {
public:
	Wad2();
	virtual ~Wad2();
	char* getMagic();
	bool isContent(const string &path);
	bool isDirectory(const string &path);
	int getSize(const string &path);
	int getContents(const string &path, char* buffer, int length, int offset=0);
	int getDirectory(const string &path, vector<string> *directory);
	bool build_file_system(string filename);
	bool detect_suffix(string base, string suffix);
	bool detect_map_marker(string name);
	bool is_dir_descriptor(string name);

private:
	vector<struct descriptor_struct> descriptor_table;
	struct wad_header header;
	Zion *zion = nullptr;
	uint8_t *raw_data = nullptr;
	bool read_header();
	bool read_descriptor(struct descriptor_struct &descriptor, uint32_t offset);
	int read_raw_wad(const string &path);
	uint32_t read_4_byte_int(uint32_t offset);
	string read_8_byte_str(uint32_t offset);
	void trim_descr_name(struct descriptor_struct &descr);



};

#endif /* WAD2_H_ */
