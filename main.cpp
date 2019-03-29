/*
 * main.cpp
 *
 *  Created on: Mar 20, 2019
 *      Author: zacharyfrederick
 */



#include <iostream>
#include "Wad2.h"
#include "Zion.h"
#include <string>

using namespace std;

int main() {
	Wad2 wad;
	wad.build_file_system("C:\\Users\\Zachary\\eclipse-workspace\\git\\project_3\\DOOM1.WAD");
	getchar();
}
