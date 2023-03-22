#include "pch.h"
#include "Game.h"
#include "TitleScreen.h"
#include "Board.h"
#include "Pieces.h"


//initialize static member variables
//set m_gameState to Uninitialized
Game::GameState Game::m_gameState = Game::GameState::Uninitialized;
sf::RenderWindow Game::m_mainWindow;


void Game::start(void)
{
	//return immediately if gamestate is already initialized
	//so Game::start() won't execute again if
	//it is already initialized
	if (m_gameState != GameState::Uninitialized)
		return;

	//create the main window
	m_mainWindow.create(sf::VideoMode(m_windowWidth, m_windowHeight), "Checkers");
	//set the gamestate to playing
	//since main window is initialized

	m_gameState = GameState::ShowingTitleMenu;

	//m_gameState = GameState::Playing;

	//main loop
	while (!isExiting())
	{
		//main game loop goes here
		Game::gameLoop();
	}
	
	m_mainWindow.close();
}

bool Game::isExiting()
{
	if (m_gameState == GameState::Exiting)
		return true;
	else
		return false;
}

void Game::showTitleScreen()
{
	TitleScreen titleScreen("../Resources/EBGaramond-Regular.ttf");
	titleScreen.show(m_mainWindow, m_windowHeight, m_windowWidth);
	TitleScreen::Menus currMenu{ titleScreen.getMenu(m_mainWindow) };
	switch (currMenu)
	{
	case TitleScreen::Menus::Play:
	{
		m_gameState = GameState::Playing;
		break;
	}
	case TitleScreen::Menus::Exit:
	{
		m_gameState = GameState::Exiting;
		break;
	}
	default:
		break;
	}
}

void Game::showBoard()
{
	Board gameBoard{ 8, 8, 80, "../Resources/EBGaramond-Regular.ttf"};
	Pieces pieces{ "../Resources/pieces.png", 12, gameBoard };
	//initialize initial position of board
	if (!pieces.m_initBoard)
	{
		pieces.setInitialPos(12);
		pieces.m_initBoard = true;
	}
	//main game loop
	if (!pieces.checkIfGameOver())
	{
		if (pieces.m_turn == Pieces::color::white)
		{
			if (!pieces.m_isMoving)
			{
				pieces.pickPieces(m_mainWindow, gameBoard);
			}
			else if (pieces.m_isMoving)
			{
				pieces.eatPiece(m_mainWindow, gameBoard);
				pieces.releasePieces(m_mainWindow, gameBoard);
			}
		}
		else if (pieces.m_turn == Pieces::color::black)
		{
			if (!pieces.m_isMoving)
			{
				pieces.pickPieces(m_mainWindow, gameBoard);
			}
			else if (pieces.m_isMoving)
			{
				pieces.eatPiece(m_mainWindow, gameBoard);
				pieces.releasePieces(m_mainWindow, gameBoard);
			}
		}
	}
	else
	{
		if (gameBoard.showGameOver(m_mainWindow))
		{
			pieces.m_initBoard = false;
			m_gameState = Game::GameState::ShowingTitleMenu;
		}
		std::cout << "game done\n";
	}
	m_mainWindow.clear();
	m_mainWindow.draw(gameBoard);
	m_mainWindow.draw(pieces);
	m_mainWindow.display();

	
}


void Game::gameLoop()
{
	sf::Event ev;

	while (m_mainWindow.isOpen())
	{
		while (m_mainWindow.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
			{
				m_gameState = GameState::Exiting;
				//remove this later when window.close is properly included
				m_mainWindow.close();
			}
			//check current mouse cursor coordinate
				//std::cout << sf::Mouse::getPosition(m_mainWindow).x << ", "
				//	<< sf::Mouse::getPosition(m_mainWindow).y << '\n';
		}

		//handle game state
		switch (m_gameState)
		{
		case Game::GameState::Uninitialized:
			break;
		case Game::GameState::ShowingTitleMenu:
			showTitleScreen();
			break;
		case Game::GameState::Paused:
			break;
		case Game::GameState::Playing:
			showBoard();
			break;
		case Game::GameState::Exiting:
			break;
		default:
			break;
		}

	}

}