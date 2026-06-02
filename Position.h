#pragma once
struct Position {
	int x;
	int y;
	bool operator==(const Position& a)const {
		return x == a.x && y == a.y;
	}
};