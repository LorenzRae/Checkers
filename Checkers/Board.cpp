#include "pch.h"
#include "Board.h"

//init static variables

//

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_boardTile, states);
	target.draw(m_gameStatus);
	target.draw(m_retry);
}

Board::Board(int height, int width, int tileSize, const std::string& fontDir, int offsetX, int offsetY)
{
	//setup m_activeTilesArr size
	//to be used when placing pieces on the tiles
	m_activeTilesArr.resize((height * width) / 2);
	//setup m_boardTile vertex array
	m_boardTile.setPrimitiveType(sf::PrimitiveType::Quads);

	/*
	* 4 = vertex of 1 quad
	* height * width = total number of quads in the board
	* 4 * height * width = total number of verteces in the board
	*/
	m_boardTile.resize(4 * height * width);
	int vertexNumber{ 0 };
	int activeTileIt{ 0 };
	for (int j = 0; j < width; ++j)
	{
		for (int i = 0; i < height; ++i)
		{
			m_boardTile[vertexNumber].position = sf::Vector2f(static_cast<float>((i * tileSize) + offsetX), 
				static_cast<float>((j * tileSize) + offsetY));
			Board::colorBoard(i, j, vertexNumber, 1, activeTileIt);
			vertexNumber++;

			m_boardTile[vertexNumber].position = sf::Vector2f(static_cast<float>(((i + 1) * tileSize) + offsetX), 
				static_cast<float>((j * tileSize) + offsetY));
			Board::colorBoard(i, j, vertexNumber, 2, activeTileIt);
			vertexNumber++;

			m_boardTile[vertexNumber].position = sf::Vector2f(static_cast<float>(((i + 1) * tileSize) + offsetX), 
				static_cast<float>(((j + 1) * tileSize) + offsetY));
			Board::colorBoard(i, j, vertexNumber, 3, activeTileIt);
			vertexNumber++;

			m_boardTile[vertexNumber].position = sf::Vector2f(static_cast<float>((i * tileSize) + offsetX), 
				static_cast<float>(((j + 1) * tileSize) + offsetY));
			Board::colorBoard(i, j, vertexNumber, 4, activeTileIt);
			vertexNumber++;
		}
	}

	//for text field
	if (!m_font.loadFromFile(fontDir))
	{
		//show error
	}
	m_gameStatus.setFont(m_font);
	m_gameStatus.setString("Welcome to Checkers!");
	m_gameStatus.setCharacterSize(40);
	m_gameStatus.setPosition(660, 100);

	m_retry.setFont(m_font);
	m_retry.setFillColor(sf::Color::Black);
	m_retry.setString("Go to Homescreen");
	m_retry.setCharacterSize(40);
	m_retry.setPosition(660, 200);
}

void Board::colorBoard(size_t i, size_t j, int vertexNumber, int posNum, int& activeTileIt)
{
	//i x j = position of tile on height x width
	//color every other tile
	if ((i + j) % 2 == 0)
	{
		m_boardTile[vertexNumber].color = sf::Color::Color(0, 153, 51);

		switch (posNum)
		{
		case 1:
			m_activeTilesArr[activeTileIt].append(m_boardTile[vertexNumber].position);
			break;
		case 2:
			m_activeTilesArr[activeTileIt].append(m_boardTile[vertexNumber].position);
			break;
		case 3:
			m_activeTilesArr[activeTileIt].append(m_boardTile[vertexNumber].position);
			break;
		case 4:
			m_activeTilesArr[activeTileIt].append(m_boardTile[vertexNumber].position);
			activeTileIt++;
			break;
		default:
			break;
		}
	}
	else
	{
		m_boardTile[vertexNumber].color = sf::Color::White;
	}
}

//return true if user wants to play again
bool Board::showGameOver(sf::RenderWindow& window)
{
	m_gameStatus.setString("Game Over!");
	m_retry.setFillColor(sf::Color::White);
	sf::FloatRect m_retryRec(m_retry.getGlobalBounds());
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (m_retryRec.contains(static_cast<float>(sf::Mouse::getPosition(window).x),
			static_cast<float>(sf::Mouse::getPosition(window).y)))
		{
			std::cout << "retrying \n";
			return true;
		}
	}
	return false;
}

