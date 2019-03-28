/*
 * FuseManager.h
 *
 *  Created on: Mar 28, 2019
 *      Author: zacharyfrederick
 */

#ifndef FUSEMANAGER_H_
#define FUSEMANAGER_H_

#include <cstdint>

using namespace std;
class FuseManager {
public:
	FuseManager();
	virtual ~FuseManager();
	static uint8_t *data;
	bool copy_data(uint8_t *raw_data, int size);

};

#endif /* FUSEMANAGER_H_ */
