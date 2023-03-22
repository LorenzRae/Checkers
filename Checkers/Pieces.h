#pragma once

class Pieces : public sf::Drawable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	struct BoardPieces
	{
		int pieceNo{};
		sf::VertexArray pieceVx{ sf::PrimitiveType::Quads, static_cast<size_t>(4) };
	};

	enum class color
	{
		white,
		black
	};

private:
	sf::Texture m_texture;
	int m_pieceCount;
	Board m_board;
	void updateActiveTile();
	static std::vector<BoardPieces> m_blkPieceVec;
	static std::vector<BoardPieces> m_whtPieceVec;
	static sf::VertexArray m_activeTile;
	//test
	static int tempvar;
	//

public:
	Pieces(const std::string& textureDir, int pieceCount, Board& board);
	void pickPieces(sf::RenderWindow& window, Board& board);
	void releasePieces(sf::RenderWindow& window, Board& board);
	void eatPiece(sf::RenderWindow& window, Board& board);
	bool checkIfGameOver();
	void setInitialPos(int pieceCount);
	static color m_turn;
	static bool m_mousePressed;
	static bool m_isMoving;
	static bool m_initBoard;
	//for auto eat
	//static int m_whtIndex;
	//static int m_blkIndex;
public:
	friend class Board;
};

/*
m_activeTilesArr index to position map
0	x	1	x	2	x	3	x
x	4	x	5	x	6	x	7
8	x	9	x	10	x	11	x
x	12	x	13	x	14	x	15
16	x	17	x	18	x	19	x
x	20	x	21	x	22	x	23
...
...					30	x	31
*/