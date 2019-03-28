/*
 * FileNode.cpp
 *
 *  Created on: Mar 25, 2019
 *      Author: Zachary
 */

#include "FileNode.h"

FileNode::FileNode() {
	this->type = FILE_NODE;
}

FileNode::~FileNode() {
	// TODO Auto-generated destructor stub
}

string FileNode::get_name() {
	return descriptor.name;
}

uint32_t FileNode::get_location() {
	return descriptor.offset;
}

uint32_t FileNode::get_offset() {
	return descriptor.offset;
}

void FileNode::set_descriptor(struct descriptor_struct descriptor){
	this->descriptor = descriptor;
	//path = descriptor.name;
}

