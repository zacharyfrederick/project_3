/*
 * FuseManager.cpp
 *
 *  Created on: Mar 28, 2019
 *      Author: zacharyfrederick
 */

#include "FuseManager.h"

FuseManager::FuseManager() {
	// TODO Auto-generated constructor stub

}

FuseManager::~FuseManager() {
	// TODO Auto-generated destructor stub
}

bool FuseManager::copy_data(uint8_t* raw_data, int size) {
	this->data = new uint8_t[size];

	for(int i=0; i < size; i++) {
		//FuseManager::data[i] = raw_data[i];
	}

	return true;
}
