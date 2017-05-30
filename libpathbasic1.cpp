/**
 * @file libpathbasic1.cpp
 */
#include "libpath.hpp"

using namespace std;

int DerivingPath::getPath(std::vector<Motion>& path, const Map& map, const std::pair<uint32_t, uint32_t>& pair){
	return 10;
}

DerivingPath::~DerivingPath(){}

extern "C" int CreateMyPath(std::vector<Motion>& path, const Map& map, const std::pair<uint32_t, uint32_t>& pair){
	DerivingPath newpath;
	return newpath.getPath(path, map, pair);
}
