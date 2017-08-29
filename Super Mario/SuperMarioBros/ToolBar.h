#pragma once

#include "GameObject.h"
#include "Macro.h"

class ToolBar
{
public:
	ToolBar();
	~ToolBar();

	void drow(sf::RenderWindow & window) const;
	void updateCoins(); 
	void updateLifes(bool b);
	unsigned int getLife()const;


private:
	std::string ToolBar::getCoins();
	std::string ToolBar::getLifes();
	unsigned int m_coins;
	unsigned int m_lifes;
	sf::Font m_font;
	sf::Text m_textLifes;
	sf::Text m_textCoins;
	sf::Texture m_texture1;
	sf::Texture m_texture2;
	sf::RectangleShape m_rect1;
	sf::RectangleShape m_rect2;
};

