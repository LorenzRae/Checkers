#pragma once

class Board : public sf::Drawable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	/*
	* the whole board is made up of 1 vertex array
	* this was made up of 1 quad per tile
	*/
	sf::VertexArray m_boardTile;
public:
	/*
	* Constructor - 
	* Create and position the board tiles
	* 
	* height, width = in tiles
	* tileSize = size of tiles in px (assuming square tile)
	* offsetX, offsetY = offset (in px) from the top left corner of the window
	*/
	Board(int height, int width, int tileSize, const std::string& fontDir, int offsetX = 0, int offsetY = 0);
public:
	//to be used on Pieces class
	//to setup initial position of pawns
	std::vector<sf::VertexArray> m_activeTilesArr;
	//show if game over
	bool showGameOver(sf::RenderWindow& window);
private:
	void colorBoard(size_t i, size_t j, int vertexNumber, int posNum, int& activeTileIt);
	sf::Font m_font;
	sf::Text m_gameStatus;
	sf::Text m_retry;
	static sf::FloatRect m_retryRec;
private:
	friend class Pieces;
};

/*
m_activeTilesArr index to position map
0	x	1	x	2	x	3	x
x	5	x	6	x	7	x	8
9	x	10	x	11	x	12	x
x	13	x	14	x	15	x	16
17	x	18	x	19	x	20	x
x	21	x	22	x	23	x	24
...
...					30	x	31
*/