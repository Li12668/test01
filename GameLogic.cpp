#include"GameLogic.h"
#include<algorithm>

bool GameLogic::loadLevel(const std::string& path) {
	if (!m_level.loadFromFile(path))
		return false;
	resetLevel();
	return true;
}
void GameLogic::resetLevel() {
	m_playerPos = m_level.playerStart;
	m_boxPositions = m_level.boxStarts;
	m_steps = 0;
	m_history.clear();
}
bool GameLogic::movePlayer(int dx, int dy) {
	Position newPos = { m_playerPos.x + dx,m_playerPos.y + dy };
	if (m_level.isWall(newPos))
		return false;
	int boxIdx = findBoxAt(newPos);
	if (boxIdx != -1) {
		Position newBoxPos = { newPos.x + dx, newPos.y + dy };
		if (m_level.isWall(newBoxPos))
			return false;
		if (findBoxAt(newBoxPos) != -1)
			return false;
		m_history.push_back({ m_playerPos, m_boxPositions, m_steps });

		// 移动箱子
		m_boxPositions[boxIdx] = newBoxPos;
		// 移动玩家
		m_playerPos = newPos;
		m_steps++;
		return true;
	}
	m_history.push_back({ m_playerPos, m_boxPositions, m_steps });
	m_playerPos = newPos;
	m_steps++;
	return true;
}
bool GameLogic::undo() {
	if (m_history.empty())
		return false;
	State prev = m_history.back();
	m_history.pop_back();
	m_playerPos = prev.player;
	m_boxPositions = prev.boxes;
	m_steps = prev.steps;
	return true;
}
const Level& GameLogic::getLevel() const {
	return m_level;
}
Position GameLogic::getPlayerPos() const {
	return m_playerPos;
}
const std::vector<Position>& GameLogic::getBoxPositions() const {
	return m_boxPositions;
}
int GameLogic::getSteps() const {
	return m_steps;
}
bool GameLogic::isWin() const {
	for (const auto& target : m_level.targets) {
		bool boxOnTarget = std::any_of(m_boxPositions.begin(), m_boxPositions.end(), [&](const Position& box) {
			return box == target;
			});
		if (!boxOnTarget) return false;
	}
	return true;
}
int GameLogic::findBoxAt(Position p) const {
	for (size_t i = 0; i < m_boxPositions.size(); ++i) {
		if (m_boxPositions[i] == p) {
			return static_cast<int>(i);
		}
	}
	return -1;
}
bool GameLogic::isBoxOnTarget(Position boxPos) const {
	if (findBoxAt(boxPos) == -1) return false;
	return m_level.isTarget(boxPos);
}