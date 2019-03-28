/*
 * FileNode.h
 *
 *  Created on: Mar 25, 2019
 *      Author: Zachary
 */

#ifndef FILENODE_H_
#define FILENODE_H_

#include "Node2.h"
#include "Wad.h"

class FileNode: public Node2 {
public:
	FileNode();
	virtual ~FileNode();
	struct descriptor_struct descriptor;
	string get_name();
	uint32_t get_location();
	uint32_t get_offset();
	void set_descriptor(descriptor_struct descriptor);
};

#endif /* FILENODE_H_ */
