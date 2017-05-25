/**
 * @file libpathbasic.h
 * @brief 最短パス生成のテンプレートクラス
 */

#pragma once

#include <utility>
#include <memory>

#include "../libmouse/Pathdata.h"
#include "../libmouse/Map.h"

class Path{
private:
	
public:
	int getPath(Pathdata& path, const Map& map, const std::pair<uint32_t, uint32_t>& pair);

	~Path();
};

typedef Path* create_p();

