#include "game.h"

//Private functions
void Game::initVariables()
{
	// Window Declaration
	this->window = nullptr;

	// Game logic
	this->endGame = false;
	this->dead = false;
	this->paused = false;
	this->menuIndexObject = 0;
	
	// Change Objects.
	this->points = 0;
	this->health = 10;
	this->maxEnemies = 5;
	this->enemySpawnTimerMax = 20.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->mouseHeld = false;

	// Background
	this->bgRed = 25;
	this->bgGreen = 25;
	this->bgBlue = 25;
}

void Game::initWindow()
{
	this->menuHeight = 800;
	this->menuWidth = 1400;

	this->videoMode.height = 1080;
	this->videoMode.width = 1920;

	this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close | sf::Style::Fullscreen);

	this->window->setFramerateLimit(144);
}

void Game::initFonts()
{
	if (!this->font.loadFromFile("Dosis-Light.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << "\n";
	}
}

void Game::initGameVaribles()
{

}

void Game::initMenu()
{
	this->menuBox.setPosition(static_cast<float>((this->videoMode.width / 2) - (this->menuWidth / 2)), static_cast<float>((this->videoMode.height / 2) - (this->menuHeight / 2)));
	this->menuBox.setSize(sf::Vector2f(static_cast<float>(this->menuWidth), static_cast<float>(this->menuHeight)));
	this->menuBox.setFillColor(sf::Color(150, 150, 150, 210));

	this->menuText[0].setFont(this->font);
	this->menuText[0].setCharacterSize(42);
	this->menuText[0].setFillColor(sf::Color(255,0,0));
	this->menuText[0].setString("NONE");

	this->menuText[1].setFont(this->font);
	this->menuText[1].setCharacterSize(42);
	this->menuText[1].setFillColor(sf::Color(255, 255, 255));
	this->menuText[1].setString("NONE");

	this->menuText[2].setFont(this->font);
	this->menuText[2].setCharacterSize(42);
	this->menuText[2].setFillColor(sf::Color(255, 255, 255));
	this->menuText[2].setString("NONE");

	this->menuText[3].setFont(this->font);
	this->menuText[3].setCharacterSize(42);
	this->menuText[3].setFillColor(sf::Color(255, 255, 255));
	this->menuText[3].setString("NONE");
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");
}

void Game::initEnemies()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setFillColor(sf::Color::Cyan);
}

//Constructors / Destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initMenu();
	this->initText();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
}

//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

void Game::restartGame()
{
	this->endGame = false;
	this->points = 0;
	this->health = 100;
	this->enemies.clear();
	this->bgRed = 25;
	this->bgGreen = 25;
	this->bgBlue = 25;
	this->paused = false;
}

//Functions
void Game::spawnEnemy()
{
	/*
		@return void

		Spawns enemies and sets their types and colors. Spawns them at random positions.
		-Sets a random type (diff).
		-Sets a random position.
		-Sets a random color.
		-Adds enemy to the vector.
	*/

	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);

	//Randomize enemy type
	int type = rand() % 5;

	switch (type)
	{
	case 0:
		this->enemy.setSize(sf::Vector2f(10.f, 10.f));
		this->enemy.setFillColor(sf::Color::Magenta);
		break;
	case 1:
		this->enemy.setSize(sf::Vector2f(30.f, 30.f));
		this->enemy.setFillColor(sf::Color::Blue);
		break;
	case 2:
		this->enemy.setSize(sf::Vector2f(50.f, 50.f));
		this->enemy.setFillColor(sf::Color::Cyan);
		break;
	case 3:
		this->enemy.setSize(sf::Vector2f(70.f, 70.f));
		this->enemy.setFillColor(sf::Color::Red);
		break;
	case 4:
		this->enemy.setSize(sf::Vector2f(100.f, 100.f));
		this->enemy.setFillColor(sf::Color::Green);
		break;
	default:
		this->enemy.setSize(sf::Vector2f(100.f, 100.f));
		this->enemy.setFillColor(sf::Color::Yellow);
		break;
	}

	//Spawn the enemy
	this->enemies.push_back(this->enemy);
}

void Game::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:

			// General Key Presses;
			// - Space, closes.
			// - Escape opens pause box.
			if (this->ev.key.code == sf::Keyboard::Space)
				this->window->close();
			if (this->ev.key.code == sf::Keyboard::Escape)
			{
				if (!paused)
				{
					this->bgRed = 50;
					this->bgGreen = 50;
					this->bgBlue = 50;
					this->paused = true;
				}
				else 
				{
					this->bgRed = 25;
					this->bgGreen = 25;
					this->bgBlue = 25;
					this->paused = false;
				}
			}

			// Key Presses only appropriate on pause.
			if (paused)
			{
				switch (this->ev.key.code)
				{
				case sf::Keyboard::Up:
					this->menuUp();
					break;
				case sf::Keyboard::Down:
					this->menuDown();
					break;
				case sf::Keyboard::Return:
					if (this->menuIndexObject == 0)
					{
						this->bgRed = 25;
						this->bgGreen = 25;
						this->bgBlue = 25;
						this->paused = false;
					}
					if (this->menuIndexObject == 1)
					{
						this->restartGame();
					}
					if (this->menuIndexObject == 2)
					{

					}
					if (this->menuIndexObject == 3)
					{
						this->endGame = true;
					}
				}
			}
			break;
		}
	}
}

void Game::updateMousePositions()
{
	/**
		@ return void

		Updates the mouse positions:
		- Mouse position relative to window (Vector2i)
	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::menuUp()
{
	if (this->menuIndexObject - 1 >= 0)
	{
		this->menuText[this->menuIndexObject].setFillColor(sf::Color(255,255,255));
		this->menuIndexObject--;
		this->menuText[this->menuIndexObject].setFillColor(sf::Color(255, 0, 0));
	}
}

void Game::menuDown()
{
	if (this->menuIndexObject + 1 < MENU_TEXT_OBJECTS)
	{
		this->menuText[this->menuIndexObject].setFillColor(sf::Color(255, 255, 255));
		this->menuIndexObject++;
		this->menuText[this->menuIndexObject].setFillColor(sf::Color(255, 0, 0));
	}
}

void Game::updateMenu()
{
	this->menuBox.setPosition(static_cast<float>((this->videoMode.width/2)-(this->menuWidth/2)), static_cast<float>((this->videoMode.height/2)-(this->menuHeight/2)));
	this->menuBox.setSize(sf::Vector2f(static_cast<float>(this->menuWidth), static_cast<float>(this->menuHeight)));
	this->menuBox.setFillColor(sf::Color(150,150,150,210));

	this->menuText[0].setFont(this->font);
	this->menuText[0].setString("Continue");
	this->menuText[0].setPosition(static_cast<float>((this->videoMode.width / 2)), static_cast<float>(((this->menuHeight) / MENU_TEXT_OBJECTS) * 1));

	this->menuText[1].setFont(this->font);
	this->menuText[1].setString("Restart");
	this->menuText[1].setPosition(static_cast<float>((this->videoMode.width / 2)), static_cast<float>(((this->menuHeight) / MENU_TEXT_OBJECTS) * 2));

	this->menuText[2].setFont(this->font);
	this->menuText[2].setString("Main Menu");
	this->menuText[2].setPosition(static_cast<float>((this->videoMode.width / 2)), static_cast<float>(((this->menuHeight) / MENU_TEXT_OBJECTS) * 3));

	this->menuText[3].setFont(this->font);
	this->menuText[3].setString("Exit");
	this->menuText[3].setPosition(static_cast<float>((this->videoMode.width / 2)), static_cast<float>(((this->menuHeight) / MENU_TEXT_OBJECTS) * 4));
}

unsigned int Game::getFPS()
{
	if (mClock.getElapsedTime().asSeconds() >= 1.f)
	{
		mFps = mFrame;
		mFrame = 0;
		mClock.restart();
	}
	++mFrame;
	return mFps;
}

void Game::updateText()
{
	std::stringstream ss;
	ss << "Points: " << this->points << "\n"
		<< "Health: " << this->health << "\n"
		<< "FPS: " << this->getFPS() << "\n"
		<< "Dead:" << this->dead;

	this->uiText.setString(ss.str());
}

void Game::updateEnemies()
{
	/**
		@return void

		Updates the enemy spawn timer and spawns enemies
		When the total amount of enemies is smaller than the maximum.
		Moves the enemies downwards.
		Removes the enemies at the edge of the screen. //TODO
	*/

	// Updating the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//Spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	// Moving and updating enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;

		this->enemies[i].move(0.f, 1.f);

		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
		}
	}

	// Check if clicked upon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					//Gain points
					if (this->enemies[i].getFillColor() == sf::Color::Magenta)
						this->points += 10;
					else if (this->enemies[i].getFillColor() == sf::Color::Blue)
						this->points += 7;
					else if (this->enemies[i].getFillColor() == sf::Color::Cyan)
						this->points += 5;
					else if (this->enemies[i].getFillColor() == sf::Color::Red)
						this->points += 3;
					else if (this->enemies[i].getFillColor() == sf::Color::Green)
						this->points += 1;

					//Delete the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
				}
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}
}

void Game::update()
{
	this->pollEvents();

	if (this->endGame == false)
	{
		this->updateMousePositions();
		this->updateText();
		if (!(this->dead || this->paused))
		{
			this->updateEnemies();
		}
		if (this->paused)
		{
			this->updateMenu();
		}
	}

	//End game condition
	if (this->health <= 0)
	{
		this->dead = true;
	}
}

void Game::renderMenu(sf::RenderTarget& target)
{
	target.draw(this->menuBox);
	for (size_t i = 0; i < MENU_TEXT_OBJECTS; i++)
	{
		target.draw(this->menuText[i]);
	}
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	//Rendering all the enemies
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}

void Game::render()
{
	/**
		@return void

		- clear old frame
		- render objects
		- display frame in window

		Renders the game objects.
	*/

	this->window->clear(sf::Color(this->bgRed,this->bgGreen,this->bgBlue));

	//Draw game objects
	if (!this->dead)
	{
		this->renderEnemies(*this->window);
	}
	if (this->paused)
	{
		this->renderMenu(*this->window);
	}
	this->renderText(*this->window);
	this->window->display();
}