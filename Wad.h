/*
 * Wad.h
 *
 *  Created on: Mar 20, 2019
 *      Author: zacharyfrederick
 */

#ifndef WAD_H_
#define WAD_H_

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

using namespace std;

struct wad_header {
	string magic;
	uint32_t num_descriptors;
	uint32_t desc_offset;
	};

struct descriptor_struct {
	uint32_t offset;
	uint32_t length;
	string name;
};


class Wad{
public:
	struct wad_header header;
	std::vector<struct descriptor_struct> container;
	void read_header(uint8_t *data, struct wad_header &header);
	void read_descriptor(uint8_t *data, struct descriptor_struct &descriptor, uint32_t offset);
	void read_wad_file(string filename);
	void print_file_system();
	bool is_marker_element(string name);
	bool hasEnding(string const &fullString,string const &ending);
	~Wad();

private:
	uint8_t *data;
};



#endif /* WAD_H_ */
