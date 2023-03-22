#include "pch.h"
#include "Board.h"
#include "Pieces.h"

//test
int Pieces::tempvar = 0;
//

//initialize static variables
bool Pieces::m_isMoving;
bool Pieces::m_mousePressed;
bool Pieces::m_initBoard;
//int Pieces::m_blkIndex = 0;
//int Pieces::m_whtIndex = 0;
Pieces::color Pieces::m_turn;
sf::VertexArray Pieces::m_activeTile(sf::Quads, 4);
std::vector<Pieces::BoardPieces> Pieces::m_whtPieceVec;
std::vector<Pieces::BoardPieces> Pieces::m_blkPieceVec;
//


void Pieces::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = &m_texture;
	//target.draw() here
	target.draw(m_activeTile);
	for (size_t i = 0; i < m_pieceCount; ++i)
	{
		target.draw(m_blkPieceVec[i].pieceVx, &m_texture);
		target.draw(m_whtPieceVec[i].pieceVx, &m_texture);
	}
}

//constructor - set how many pieces and set them on their position
Pieces::Pieces(const std::string& textureDir, int pieceCount, Board& board) :
	m_pieceCount{ pieceCount }, m_board{ board }
{
	if (!m_texture.loadFromFile(textureDir))
	{
		//error
	}
}

void Pieces::setInitialPos(int pieceCount)
{
	//initialize static variables
	m_isMoving = false;
	m_mousePressed = false;
	m_initBoard = false;
	//int Pieces::m_blkIndex = 0;
	//int Pieces::m_whtIndex = 0;
	m_turn = Pieces::color::white;

	m_blkPieceVec.resize(pieceCount);
	m_whtPieceVec.resize(pieceCount);

	//using m_activeTilesArr that was setup on board.cpp
	/*
	* for Black Pieces
	*/
	for (size_t i = 0; i < m_blkPieceVec.size(); ++i)
	{
		//for playing the game again
		m_blkPieceVec[i].pieceVx.resize(4);
		m_whtPieceVec[i].pieceVx.resize(4);

		/*
		* This loop is for setting the verteces
		* of the pieces
		* 1 loop = 4 vertex set / 4 texcoor set
		*/
		m_blkPieceVec[i].pieceNo = i + 1;
		int j{ 0 };
		{
			//set position on game screen
			m_blkPieceVec[i].pieceVx[j].position = m_board.m_activeTilesArr[i][0].position;
			//get texture coordinates from img file
			m_blkPieceVec[i].pieceVx[j].texCoords = sf::Vector2f(0.0f, 0.0f);
			++j;
			m_blkPieceVec[i].pieceVx[j].position = m_board.m_activeTilesArr[i][1].position;
			m_blkPieceVec[i].pieceVx[j].texCoords = sf::Vector2f(32.0f, 0.0f);
			++j;
			m_blkPieceVec[i].pieceVx[j].position = m_board.m_activeTilesArr[i][2].position;
			m_blkPieceVec[i].pieceVx[j].texCoords = sf::Vector2f(32.0f, 32.0f);
			++j;
			m_blkPieceVec[i].pieceVx[j].position = m_board.m_activeTilesArr[i][3].position;
			m_blkPieceVec[i].pieceVx[j].texCoords = sf::Vector2f(0.0f, 32.0f);
		}
	}

	/*
	* For White Pieces
	*/
	for (int k = 0, m = (m_board.m_activeTilesArr.size()-1); k < m_whtPieceVec.size(); ++k, --m)
	{
		/*
		* This loop is for setting the verteces
		* of the pieces
		* 1 loop = 4 vertex set / 4 texcoor set
		*/
		m_whtPieceVec[k].pieceNo = k + 1;
		int l{ 0 };
		{
			m_whtPieceVec[k].pieceVx[l].position = m_board.m_activeTilesArr[m][0].position;
			m_whtPieceVec[k].pieceVx[l].texCoords = sf::Vector2f(0.0f, 32.0f);
			++l;		  
			m_whtPieceVec[k].pieceVx[l].position = m_board.m_activeTilesArr[m][1].position;
			m_whtPieceVec[k].pieceVx[l].texCoords = sf::Vector2f(32.0f, 32.0f);
			++l;		  
			m_whtPieceVec[k].pieceVx[l].position = m_board.m_activeTilesArr[m][2].position;
			m_whtPieceVec[k].pieceVx[l].texCoords = sf::Vector2f(32.0f, 64.0f);
			++l;		  
			m_whtPieceVec[k].pieceVx[l].position = m_board.m_activeTilesArr[m][3].position;
			m_whtPieceVec[k].pieceVx[l].texCoords = sf::Vector2f(0.0f, 64.0f);
		}
	}
}


void Pieces::pickPieces(sf::RenderWindow& window, Board& gameBoard)
{
	//check if lmb is pressed
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		//iterate over all pieces
		//and check which piece was clicked
		for (int i = 0; i < m_pieceCount; ++i)
		{
			//for white turn
			if (m_turn == Pieces::color::white)
			{
				sf::FloatRect bound = m_whtPieceVec[i].pieceVx.getBounds();
				if (bound.contains(static_cast<float>(sf::Mouse::getPosition(window).x),
					static_cast<float>(sf::Mouse::getPosition(window).y)) && m_mousePressed == false)
				{
					m_activeTile.clear();
					m_activeTile = m_whtPieceVec[i].pieceVx;
					for (int j = 0; j < 4; ++j)
					{
						m_activeTile[j].color = sf::Color::Color(200, 100, 10);
						m_isMoving = true;
						m_mousePressed = true;
					}

				}
			}
			//for black turn
			else if (m_turn == Pieces::color::black)
			{
				sf::FloatRect bound = m_blkPieceVec[i].pieceVx.getBounds();
				if (bound.contains(static_cast<float>(sf::Mouse::getPosition(window).x),
					static_cast<float>(sf::Mouse::getPosition(window).y)) && m_mousePressed == false)
				{
					m_activeTile.clear();
					m_activeTile = m_blkPieceVec[i].pieceVx;
					for (int j = 0; j < 4; ++j)
					{
						m_activeTile[j].color = sf::Color::Color(200, 100, 10);
						m_isMoving = true;
						m_mousePressed = true;
					}
				}
			}
		}
	}
}

void Pieces::releasePieces(sf::RenderWindow& window, Board& board)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
		//iterate over all tiles of board.m_activeTilesArr
		//and check which tile was clicked
		for (int i = 0; i < 32 ; ++i)
		{
			sf::Vector2f temp(80, 80);
			sf::FloatRect bound(board.m_activeTilesArr[i][0].position, temp);
			if (bound.contains(static_cast<float>(sf::Mouse::getPosition(window).x),
				static_cast<float>(sf::Mouse::getPosition(window).y)) && m_mousePressed == true)
			{
				//check which piece was previously picked
				for (int j = 0; j < 12; ++j)
				{
					//for white piece
					if (m_turn == Pieces::color::white)
					{
						if (m_activeTile.getBounds() == m_whtPieceVec[j].pieceVx.getBounds())
						{
							//move the piece to the new destination
							m_whtPieceVec[j].pieceVx[0].position = board.m_activeTilesArr[i][0].position;
							m_whtPieceVec[j].pieceVx[1].position = board.m_activeTilesArr[i][1].position;
							m_whtPieceVec[j].pieceVx[2].position = board.m_activeTilesArr[i][2].position;
							m_whtPieceVec[j].pieceVx[3].position = board.m_activeTilesArr[i][3].position;

							updateActiveTile();
							m_turn = Pieces::color::black;
						}
					}
					//for black piece
					else if (m_turn == Pieces::color::black)
					{
						if (m_activeTile.getBounds() == m_blkPieceVec[j].pieceVx.getBounds())
						{
							m_blkPieceVec[j].pieceVx[0].position = board.m_activeTilesArr[i][0].position;
							m_blkPieceVec[j].pieceVx[1].position = board.m_activeTilesArr[i][1].position;
							m_blkPieceVec[j].pieceVx[2].position = board.m_activeTilesArr[i][2].position;
							m_blkPieceVec[j].pieceVx[3].position = board.m_activeTilesArr[i][3].position;

							updateActiveTile();
							m_turn = Pieces::color::white;
						}
					}
				}
			}
		}
	}
}


void Pieces::updateActiveTile()
{
	m_activeTile[0].color = sf::Color::Color(0, 153, 51);
	m_activeTile[1].color = sf::Color::Color(0, 153, 51);
	m_activeTile[2].color = sf::Color::Color(0, 153, 51);
	m_activeTile[3].color = sf::Color::Color(0, 153, 51);

	m_isMoving = false;
	m_mousePressed = false;
}

void Pieces::eatPiece(sf::RenderWindow& window, Board& board)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
	{
		for (int i = 0; i < 32; ++i)
		{
			sf::Vector2f temp(80, 80);
			sf::FloatRect bound(board.m_activeTilesArr[i][0].position, temp);
			if (bound.contains(static_cast<float>(sf::Mouse::getPosition(window).x),
				static_cast<float>(sf::Mouse::getPosition(window).y)))
			{
				for (int j = 0; j < 12; ++j)
				{
					if (m_turn == Pieces::color::white)
					{
						if (m_blkPieceVec[j].pieceVx.getBounds() == board.m_activeTilesArr[i].getBounds())
						{
							m_blkPieceVec[j].pieceVx.clear();
							m_blkPieceVec[j].pieceNo = NULL;
						}
					}
					else if (m_turn == Pieces::color::black)
					{
						if (m_whtPieceVec[j].pieceVx.getBounds() == board.m_activeTilesArr[i].getBounds())
						{
							m_whtPieceVec[j].pieceVx.clear();
							m_whtPieceVec[j].pieceNo = NULL;
						}
					}
				}
			}
		}
	}
}

//return true if game over
bool Pieces::checkIfGameOver()
{
	//check if m_whtPieceVec[i].pieceNo are all NULL
	//if they are, that means all pieces are gone
	int sumWhite{ 0 };
	int sumBlack{ 0 };
	std::vector<bool> pieceStatus(12);
	for (int i = 0; i < 12; ++i)
	{
		pieceStatus[i] = false;
	}
	for (int i = 0; i < 12; ++i)
	{
		if (m_whtPieceVec[i].pieceNo == 0)
		{
			pieceStatus[i] = true;
		}
		if (m_blkPieceVec[i].pieceNo == 0)
		{
			pieceStatus[i] = true;
		}
		sumWhite += pieceStatus[i];
		sumBlack += pieceStatus[i];
	}
	if (sumWhite == 12 || sumBlack == 12)
	{
		return true;
	}
	else
	{
		return false;
	}
}
