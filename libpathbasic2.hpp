/*
 * @file libpathbasic2.hpp
 * @brief Dijkstra Method
 */

#pragma once

#include <utility>
#include <memory>
#include <queue>

#ifdef DEBUG_PRINTF
#include <cstdio>
#endif

#include "../libmouse/Path.h"
#include "../libmouse/Map.h"
#include "../libmouse/SlalomParams.h"
#include "../libmouse/Walldata.h"
#include "../libmouse/Footmap.h"
#include "../libmouse/Graph.h"

class DerivingPathBasic2{
private:
	std::queue< std::pair<int8_t, int8_t> > que;

	int8_t goal_x;
	int8_t goal_y;

	int8_t start_x, start_y;
	MazeAngle start_angle;

	MazeAngle goal_angle;

	bool is_shortest_path;

	void renewFootmap();
	slalomparams::RunType getNextMotion(int8_t x, int8_t y, MazeAngle angle, Walldata walldata);

public:
	Footmap fm;
	Map map;

	void setStart(const int8_t x, const int8_t y, const MazeAngle angle);

	void setGoal(const int8_t x, const int8_t y);
	void setMap(const Map&);

	MazeAngle getGoalAngle();

	bool isShortestPath();

	Path getPath(PathType);


	int getPath(Path& path, const Map& map, const std::pair<uint32_t, uint32_t>& pair);

	DerivingPathBasic2();
	~DerivingPathBasic2();
};
