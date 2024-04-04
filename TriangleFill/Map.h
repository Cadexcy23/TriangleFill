#pragma once
#ifndef vector
#include <vector>
#endif
class Map {
public:
	//static std::vector< std::vector<int>> mapObjects;
	void loadMap();
	void draw();
	void controller();
};