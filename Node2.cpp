/*
 * Node2.cpp
 *
 *  Created on: Mar 25, 2019
 *      Author: Zachary
 */

#include "Node2.h"

int Node2::generateId() {
	static int current_id = -1;
	current_id++;
	return current_id;
}

Node2::Node2() {
	id = generateId();
}

Node2::~Node2() {
	// TODO Auto-generated destructor stub
}
