/**
 * @file libpathbasic1.cpp
 */
#include "libpathbasic.hpp"

using namespace std;

int Path::getPath(Pathdata& path, const Map& map, const std::pair<uint32_t, uint32_t>& pair){
	return 10;
}

Path::~Path(){}

extern "C" Path* CreateMyPath(){
	return new Path;
}
