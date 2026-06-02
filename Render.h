#pragma once

#include<SFML/Graphics.hpp>
#include<string>
#include"GameLogic.h"



class Render {
private:
	sf::RenderWindow& window;    //界面窗口
	sf::Font font;      //字体
	sf::Text StepText;       //步数文本
	sf::Text WinText;        //胜利文本

	static const int TILE_SIZE = 64;

	void drawBox(const vector<Position>& aim);
	void drawCurb(std::string curbType, double x, double y);    //绘制元素
	void drawUI(int steps, bool gameWon);        //绘制UI界面
public:
	explicit Render(sf::RenderWindow& window);      //构造函数
	void render(const Level& level, int steps, bool gameWon);    //渲染函数
	bool isOpen() const;        //暴露窗口状态
	void close();
	sf::RenderWindow& getWindow() { return window; }        //暴露窗口引用
};