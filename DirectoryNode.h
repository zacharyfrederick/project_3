/*
 * DirectoryNode.h
 *
 *  Created on: Mar 25, 2019
 *      Author: Zachary
 */

#ifndef DIRECTORYNODE_H_
#define DIRECTORYNODE_H_

#include "Node2.h"
#include <vector>
#include <string>
#include "Wad.h"

using namespace std;

class DirectoryNode: public Node2 {
public:
	DirectoryNode();
	virtual ~DirectoryNode();
	vector<Node2 *> getChildren();
	void addChild(Node2 *new_node);
	Node2 *getChild(int id);
	string get_name();
	uint32_t get_location();
	uint32_t get_offset();
	void set_descriptor(descriptor_struct descriptor);
	struct descriptor_struct descriptor;


public:
	vector<Node2*> children;
};

#endif /* DIRECTORYNODE_H_ */
