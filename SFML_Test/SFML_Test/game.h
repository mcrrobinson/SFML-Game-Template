#pragma once

#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#define MENU_TEXT_OBJECTS 4

/*
	Class that acts as the game engine.
	Wrapper class.
*/

class Game
{
private:
	int bgRed;
	int bgGreen;
	int bgBlue;

	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resources
	sf::Font font;

	//Text
	sf::Text uiText;

	//Game logic
	bool endGame;
	bool paused;

	unsigned points;
	int health;
	unsigned int mFrame;
	unsigned int mFps;
	sf::Clock mClock;
	bool dead;

	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	int menuHeight;
	int menuWidth;

	int menuIndexObject;

	//Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	// Menu
	sf::RectangleShape menuBox;
	sf::Text menuText[MENU_TEXT_OBJECTS];

	//Private functions
	void initVariables();
	void initWindow();
	void initFonts();
	void initGameVaribles();
	void initMenu();
	void initText();
	void initEnemies();

public:

	//Constructors / Destructors
	Game();
	virtual ~Game();

	// Checks to see if running.
	const bool running() const;

	// Is the game over?
	const bool getEndGame() const;

	// Restrt the g.
	void restartGame();

	// Adds random enemy to enemies vector.
	void spawnEnemy();

	// Check for key presses.
	void pollEvents();

	// Get mouse position.
	void updateMousePositions();

	// Menu up and down arrows.
	void menuUp();
	void menuDown();

	// Update drawings.
	void updateMenu();
	unsigned int getFPS();
	void updateText();
	void updateEnemies();
	void update();

	// Render objects.
	void renderMenu(sf::RenderTarget& target);
	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void render();
};