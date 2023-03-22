#pragma once
//sfml headers
//create the Game class
class Game
{
private:
	enum class GameState
	{
		Uninitialized,
		ShowingTitleMenu,
		Paused,
		Playing,
		Exiting
	};
	//member variables
	static GameState m_gameState;
	static sf::RenderWindow m_mainWindow;
	static const size_t m_windowHeight { 768 };
	static const size_t m_windowWidth { 1024 };

	//private methods
	static bool isExiting();
	//for title screen
	static void showTitleScreen();
	//for game screen
	static void showBoard();
	//main game loop
	static void gameLoop();

public:
	//public methods
	static void start();
};