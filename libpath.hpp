/**
 * @file libpathbasic.h
 * @brief 最短パス生成のテンプレートクラス
 */

#pragma once

#include <utility>
#include <memory>

#include "../libmouse/Path.h"
#include "../libmouse/Map.h"

class DerivingPath{
private:
	
public:
	int getPath(std::vector<Motion>& path, const Map& map, const std::pair<uint32_t, uint32_t>& pair);

	~DerivingPath();
};

