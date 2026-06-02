#include"Render.h"
#include<cmath>

Render::Render(sf::RenderWindow& win) :window(win) {
	font.loadFromFile("JYRB.ttf");

	StepText.setFont(font);
	StepText.setCharacterSize(20);
	StepText.setFillColor(sf::Color::White);
	StepText.setPosition(10, 10);

	WinText.setFont(font);
	WinText.setCharacterSize(50);
	WinText.setFillColor(sf::Color::Yellow);
	WinText.setString("YOU WIN");

	sf::FloatRect r = WinText.getLocalBounds();
	WinText.setOrigin(r.left + r.width / 2.0f, r.top + r.height / 2.0f);
	WinText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

}

void Render::drawCurb(std::string curbType, double x, double y) {
	sf::RectangleShape rect(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	rect.setPosition(x, y);

	//根据curbType设置颜色
	
	//地板

	if (curbType == "Empty") {
		rect.setFillColor(sf::Color(50, 50, 50));
		window.draw(rect);
	}

	//墙壁

	if (curbType == "Wall") {
		rect.setFillColor(sf::Color(120, 120, 120));
		window.draw(rect);
	}

	if (curbType == "Target") {
		sf::RectangleShape target(sf::Vector2f(TILE_SIZE * 0.3f, TILE_SIZE * 0.3f));
		target.setFillColor(sf::Color::Red);
		target.setPosition(x + TILE_SIZE * 0.35f, y + TILE_SIZE * 0.35f);
		window.draw(target);
	}
}

void Render::drawBox(const vector<Position>& aim) {
	for (int i = 0; i < aim.size(); i++) {
		sf::RectangleShape rect(sf::Vector2f(TILE_SIZE, TILE_SIZE));
		rect.setPosition(aim[i].x, aim[i].y);
		rect.setSize(sf::Vector2f(TILE_SIZE * 0.8f, TILE_SIZE * 0.8f));
		rect.setPosition(aim[i].x + TILE_SIZE * 0.1f, aim[i].y + TILE_SIZE * 0.1f);
		rect.setFillColor(sf::Color(200, 150, 50));
		window.draw(rect);
	}
}

void Render::drawUI(int steps, bool gameWon) {
	StepText.setString("Steps: " + std::to_string(steps));
	window.draw(StepText);

	if (gameWon) {
		window.draw(WinText);
	}
}

void Render::render(const GameLogic& GL,const Level& level, int steps, bool gameWon) {
	window.clear(sf::Color::Black);

	for (int r = 0; r < level.getHeight(); ++r) {
		for (int c = 0; c < level.getWidth(); ++c) {
			double x = c * TILE_SIZE;
			double y = r * TILE_SIZE;
			Position p(x, y);
			std::string s = tileAt(Position p);
			drawCurb(s, x, y);
		}
	}


	drawBox(GL.getBoxPositions());


	sf::CircleShape player(TILE_SIZE / 2.0f - 4);
	player.setFillColor(sf::Color::Blue);
	player.setPosition(GL.playerStart.x,GL.playerStart.y + 4);
	window.draw(player);
}











bool Render::isOpen() const {
	return window.isOpen();
}

void Render::close() {
	window.close();
}
