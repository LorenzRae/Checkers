#pragma once


class TitleScreen
{
private:
	sf::Font m_font;
	sf::Text m_title;
	sf::Text m_play;
	sf::Text m_exit;

public:
	//constructor
	TitleScreen(const std::string& fontDir);

	void show(sf::RenderWindow& window, size_t windowHeight, size_t windowWidth);

	enum class Menus
	{
		Play,
		Exit,
		Standby
	};

	Menus getMenu(sf::RenderWindow& window);

private:
	struct menuOptions
	{
		Menus menu;
		sf::FloatRect localBound;
	};
	std::array<menuOptions, 2> m_menuArr;
};