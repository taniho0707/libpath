/**
 * @file libpathbasic2.cpp
 */
#include "libpath.h"


int Path::getPath(Pathdata& path, const Map& map, const std::pair<uint32_t, uint32_t>& pair){
	return 0;
}


extern "C" std::unique_ptr<Path> Create() {
	return std::unique_ptr<Path>(new Path);
}

