#include "pch.h"
#include "TitleScreen.h"

TitleScreen::TitleScreen(const std::string& fontDir)
{
	if (!m_font.loadFromFile(fontDir))
	{
		//error
	}

	m_title.setFont(m_font);
	m_play.setFont(m_font);
	m_exit.setFont(m_font);

	m_title.setString("CHECKERS");
	m_play.setString("Play Game");
	m_exit.setString("Exit");

	m_title.setCharacterSize(80);
	m_play.setCharacterSize(40);
	m_exit.setCharacterSize(40);
}

void TitleScreen::show(sf::RenderWindow& window, size_t windowHeight, size_t windowWidth)
{
	//set position for CHECKERS title text
	sf::FloatRect titleRect = m_title.getLocalBounds();
	m_title.setOrigin(titleRect.left + titleRect.width / 2.0f,
		titleRect.top + titleRect.height / 2.0f);
	m_title.setPosition(sf::Vector2f((windowWidth / 2.0f),
		(windowHeight / 2.25f)));
	

	//set position for Play Game text
	//with TITLE as the ref position
	sf::FloatRect playRect = m_play.getLocalBounds();
	m_play.setOrigin(playRect.left + playRect.width / 2.0f,
		playRect.top);
	//adjust 1.0f to adjust space between
	/*
	*	TITLE
	* Play game
	*
	*/
	m_play.setPosition(sf::Vector2f(m_title.getPosition().x,
		m_title.getPosition().y + titleRect.height / 1.0f));
	//the ff code is used for getMenu()
	m_menuArr[0].menu = Menus::Play;
	m_menuArr[0].localBound = { m_play.getPosition().x - (playRect.width / 2.0f),
		m_play.getPosition().y,
		playRect.width,
		playRect.height };


	//set position for Exit text
	sf::FloatRect exitRect = m_exit.getLocalBounds();
	m_exit.setOrigin(exitRect.left + exitRect.width / 2.0f,
		exitRect.top + exitRect.height / 2.0f);
	m_exit.setPosition(sf::Vector2f(m_play.getPosition().x,
		m_title.getPosition().y + titleRect.height / 0.45f));
	//the ff code is used for getMenu()
	m_menuArr[1].menu = Menus::Exit;
	m_menuArr[1].localBound = { m_exit.getPosition().x - (exitRect.width / 2.0f),
		m_exit.getPosition().y,
		exitRect.width,
		exitRect.height };

	window.clear();
	window.draw(m_title);
	if (m_menuArr[0].localBound.contains(sf::Mouse::getPosition(window).x,
		sf::Mouse::getPosition(window).y))
	{
		m_play.setFillColor(sf::Color::Red);
		window.draw(m_play);
	}
	else
	{
		m_play.setFillColor(sf::Color::White);
		window.draw(m_play);
	}
	if (m_menuArr[1].localBound.contains(sf::Mouse::getPosition(window).x,
		sf::Mouse::getPosition(window).y))
	{
		m_exit.setFillColor(sf::Color::Red);
		window.draw(m_exit);
	}
	else
	{
		m_exit.setFillColor(sf::Color::White);
		window.draw(m_exit);
	}
	window.display();
}

TitleScreen::Menus TitleScreen::getMenu(sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (m_menuArr[0].localBound.contains(sf::Mouse::getPosition(window).x,
			sf::Mouse::getPosition(window).y))
		{
			return Menus::Play;
		}
		else if (m_menuArr[1].localBound.contains(sf::Mouse::getPosition(window).x,
			sf::Mouse::getPosition(window).y))
		{
			return Menus::Exit;
		}
		else
			return Menus::Standby;	
	}
	return Menus::Standby;
}
