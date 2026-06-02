#pragma once
#include"Position.h"
#include"Level.h"
#include<vector>

class GameLogic {
public:
	bool loadLevel(const std::string& filepath);
	void resetLevel();
	bool movePlayer(int dx, int dy);
	bool undo();
	bool isBoxOnTarget(Position boxPos) const;
	const Level& getLevel() const;
	Position getPlayerPos() const;
	const std::vector<Position>& getBoxPositions() const;
	int getSteps() const;
	bool isWin() const;
private:
	Level m_level;
	Position m_playerPos;
	std::vector<Position> m_boxPositions;
	int m_steps = 0;
	// 撤回用
	struct State {
		Position player;
		std::vector<Position> boxes;
		int steps;
	};
	std::vector<State> m_history;

	// 辅助
	int findBoxAt(Position p) const;  // 返回箱子索引，没有返回 -1
};
