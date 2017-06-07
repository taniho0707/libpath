/**
 * @file libpathbasic2.cpp
 */
#include "libpathbasic2.hpp"

using namespace std;

DerivingPathBasic2::DerivingPathBasic2(){
	fm.resetFootmap();
	map.format();
	setStart(0, 1, MazeAngle::NORTH);
	is_shortest_path = false;
}

void DerivingPathBasic2::setStart(const int8_t x, const int8_t y, const MazeAngle angle){
	start_x = x;
	start_y = y;
	start_angle = angle;
}

void DerivingPathBasic2::setGoal(const int8_t x, const int8_t y){
	goal_x = x;
	goal_y = y;
}

void DerivingPathBasic2::setMap(const Map& m){
	map.copyFrom(m);
}

bool DerivingPathBasic2::isShortestPath(){
	is_shortest_path = true;
	Path np = getPath(PathType::DIAGO);
	is_shortest_path = false;
	Path sp = getPath(PathType::DIAGO);
	if(sp == np && sp.getMotion(0).type != slalomparams::RunType::PIVOTTURN) return true;
	else return false;
}

void DerivingPathBasic2::renewFootmap(){
	std::pair<int8_t, int8_t> buf;
	std::pair<int8_t, int8_t> tmp;

	fm.resetFootmap();
	tmp.first = goal_x;
	tmp.second = goal_y;
	std::queue< std::pair<int8_t, int8_t> >().swap(que);
	que.push(tmp);
	fm.setFootmap(goal_x, goal_y, 0);

	while(!que.empty()){
		buf = que.front();
		que.pop();

		if((map.isExistWall(buf.first, buf.second, MazeAngle::NORTH) == false)
		   && (fm.getFootmap(buf.first, buf.second + 1, 0) == 1024)
		   && (is_shortest_path == true || map.hasWatched(buf.first, buf.second, MazeAngle::NORTH)))
		{
			tmp.first = buf.first;
			tmp.second = buf.second + 1;
			que.push(tmp);
			fm.setFootmap(buf.first, buf.second + 1, fm.getMinNextTo(buf.first, buf.second + 1, map.getKnownWalldata(buf.first, buf.second + 1)) + 1);
		}
		if((map.isExistWall(buf.first, buf.second, MazeAngle::EAST) == false)
		   && (fm.getFootmap(buf.first + 1, buf.second, 0) == 1024)
		   && (is_shortest_path == true || map.hasWatched(buf.first, buf.second, MazeAngle::EAST)))
		{
			tmp.first = buf.first + 1;
			tmp.second = buf.second;
			que.push(tmp);
			fm.setFootmap(buf.first + 1, buf.second, fm.getMinNextTo(buf.first + 1, buf.second, map.getKnownWalldata(buf.first + 1, buf.second)) + 1);
		}
		if((map.isExistWall(buf.first, buf.second, MazeAngle::SOUTH) == false)
		   && (fm.getFootmap(buf.first, buf.second - 1, 0) == 1024)
		   && (is_shortest_path == true || map.hasWatched(buf.first, buf.second, MazeAngle::SOUTH)))
		{
			tmp.first = buf.first;
			tmp.second = buf.second - 1;
			que.push(tmp);
			fm.setFootmap(buf.first, buf.second - 1, fm.getMinNextTo(buf.first, buf.second - 1, map.getKnownWalldata(buf.first, buf.second - 1)) + 1);
		}
		if((map.isExistWall(buf.first, buf.second, MazeAngle::WEST) == false)
		   && (fm.getFootmap(buf.first - 1, buf.second, 0) == 1024)
		   && (is_shortest_path == true || map.hasWatched(buf.first, buf.second, MazeAngle::WEST)))
		{
			tmp.first = buf.first - 1;
			tmp.second = buf.second;
			que.push(tmp);
			fm.setFootmap(buf.first - 1, buf.second, fm.getMinNextTo(buf.first - 1, buf.second, map.getKnownWalldata(buf.first - 1, buf.second)) + 1);
		}
	}
}

slalomparams::RunType DerivingPathBasic2::getNextMotion(int8_t x, int8_t y, MazeAngle angle, Walldata walldata){
	Walldata wd = walldata;
	if(!is_shortest_path){
		if(!map.hasWatched(x, y, MazeAngle::NORTH)) wd.addWall(MouseAngle::FRONT);
		if(!map.hasWatched(x, y, MazeAngle::EAST)) wd.addWall(MouseAngle::RIGHT);
		if(!map.hasWatched(x, y, MazeAngle::SOUTH)) wd.addWall(MouseAngle::BACK);
		if(!map.hasWatched(x, y, MazeAngle::WEST)) wd.addWall(MouseAngle::LEFT);
	}
	uint16_t min = fm.getMinNextTo(x, y, wd);
	min = fm.getFootmap(x, y, 1024) - 1;
	if(angle == MazeAngle::NORTH){
		if(fm.getFootmap(x, y+1, 1024) == min && wd.isExistWall(MouseAngle::FRONT)==false) return slalomparams::RunType::TRAPACCEL;
		else if(fm.getFootmap(x+1, y, 1024) == min && wd.isExistWall(MouseAngle::RIGHT)==false) return slalomparams::RunType::SLALOM90SML_RIGHT;
		else if(fm.getFootmap(x-1, y, 1024) == min && wd.isExistWall(MouseAngle::LEFT)==false) return slalomparams::RunType::SLALOM90SML_LEFT;
		else return slalomparams::RunType::PIVOTTURN;
	} else if(angle == MazeAngle::EAST){
		if(fm.getFootmap(x+1, y, 1024) == min && wd.isExistWall(MouseAngle::RIGHT)==false) return slalomparams::RunType::TRAPACCEL;
		else if(fm.getFootmap(x, y-1, 1024) == min && wd.isExistWall(MouseAngle::BACK)==false) return slalomparams::RunType::SLALOM90SML_RIGHT;
		else if(fm.getFootmap(x, y+1, 1024) == min && wd.isExistWall(MouseAngle::FRONT)==false) return slalomparams::RunType::SLALOM90SML_LEFT;
		else return slalomparams::RunType::PIVOTTURN;
	} else if(angle == MazeAngle::SOUTH){
		if(fm.getFootmap(x, y-1, 1024) == min && wd.isExistWall(MouseAngle::BACK)==false) return slalomparams::RunType::TRAPACCEL;
		else if(fm.getFootmap(x-1, y, 1024) == min && wd.isExistWall(MouseAngle::LEFT)==false) return slalomparams::RunType::SLALOM90SML_RIGHT;
		else if(fm.getFootmap(x+1, y, 1024) == min && wd.isExistWall(MouseAngle::RIGHT)==false) return slalomparams::RunType::SLALOM90SML_LEFT;
		else return slalomparams::RunType::PIVOTTURN;
	} else if(angle == MazeAngle::WEST){
		if(fm.getFootmap(x-1, y, 1024) == min && wd.isExistWall(MouseAngle::LEFT)==false) return slalomparams::RunType::TRAPACCEL;
		else if(fm.getFootmap(x, y+1, 1024) == min && wd.isExistWall(MouseAngle::FRONT)==false) return slalomparams::RunType::SLALOM90SML_RIGHT;
		else if(fm.getFootmap(x, y-1, 1024) == min && wd.isExistWall(MouseAngle::BACK)==false) return slalomparams::RunType::SLALOM90SML_LEFT;
		else return slalomparams::RunType::PIVOTTURN;
	}
}


MazeAngle DerivingPathBasic2::getGoalAngle(){
	return goal_angle;
}

Path DerivingPathBasic2::getPath(PathType pathtype){
	Position pos;
	Path p(pathtype);
	Motion m;
	slalomparams::RunType type;

	pos.setPosition(start_x, start_y, start_angle);
	m = (struct Motion){slalomparams::RunType::TRAPACCEL, 1};
	p.putMotion(m);
	renewFootmap();

	if(fm.getFootmap(start_x, start_y, 1024) > 1024){
		p.format();
		return p;
	}

	while(true){
		type = getNextMotion(pos.getPositionX(), pos.getPositionY(), pos.getAngle(), map.getWalldata(pos.getPositionX(), pos.getPositionY()));
		m = (struct Motion){type, 1};
		p.putMotion(m);
		pos.setNextPosition(type);
		if(pos.getPositionX() == goal_x && pos.getPositionY() == goal_y){
			goal_angle = pos.getAngle();
			break;
		}
	}
	m = (struct Motion){slalomparams::RunType::TRAPACCEL, 2};
	p.putMotion(m);
	m = (struct Motion){slalomparams::RunType::PIVOTTURN, 1};
	p.putMotion(m);

	return p;
}



int DerivingPathBasic2::getPath(Path& path, const Map& map, const std::pair<uint32_t, uint32_t>& pair){
	setGoal(pair.first, pair.second);
	setMap(map);
	path = getPath(PathType::DIAGO);
	return 0;
}

DerivingPathBasic2::~DerivingPathBasic2(){}

extern "C" int CreateMyPath(Path& path, const Map& map, const std::pair<uint32_t, uint32_t>& pair){
	DerivingPathBasic2 newpath;
	return newpath.getPath(path, map, pair);
}
