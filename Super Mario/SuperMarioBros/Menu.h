#pragma once

#include "GameObject.h"
#include "Macro.h"
#include <thread>

class Menu
{
public:
	Menu();
	~Menu();
	void startGame(sf::RenderWindow & window);

	void disqualified(sf::RenderWindow & window);

	void gameOver(sf::RenderWindow & window);

	void wellDone(sf::RenderWindow & window);

	void thanks(sf::RenderWindow & window);

private:
	void Menu::careEvent(sf::RenderWindow& window, bool & again);
	void Menu::mousePresse(sf::RenderWindow& window, bool & b, bool & again);
	sf::Texture m_textureBackground;
	sf::Texture m_texturePlay;
	sf::Texture m_textureHelp;
	sf::Texture m_textureExit;
	sf::Texture m_textureInstructions;
	sf::Texture m_textureBack;
	sf::Texture m_textureDisqua;
	sf::Texture m_textureOver;
	sf::Texture m_textureDone;
	sf::Texture m_textureThank;

	sf::RectangleShape m_rectBackground;
	sf::RectangleShape m_rectPlay;
	sf::RectangleShape m_rectHelp;
	sf::RectangleShape m_rectExit;
	sf::RectangleShape m_rectInstructions;
	sf::RectangleShape m_rectBack;
	sf::RectangleShape m_rectDisqua;
	sf::RectangleShape m_rectOver;
	sf::RectangleShape m_rectDone;
	sf::RectangleShape m_rectThank;
};

