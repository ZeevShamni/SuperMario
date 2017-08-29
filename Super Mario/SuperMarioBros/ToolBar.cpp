#include "ToolBar.h"
#include <sstream>


ToolBar::ToolBar()
	:m_lifes(2),
	m_coins(0)
{
	m_texture1.loadFromFile(MarioPath);
	m_texture2.loadFromFile(CoinsPath);
	
	m_rect1.setSize(sf::Vector2f(40, 40));
	m_rect1.setPosition(10, 130);
	m_rect1.setTexture(&m_texture1);
	m_rect2.setSize(sf::Vector2f(40, 40));
	m_rect2.setPosition(200, 130);
	m_rect2.setTexture(&m_texture2);
	m_font.loadFromFile(FontPath);
	m_textLifes.setFont(m_font);
	m_textLifes.setFillColor(sf::Color::Red);
	m_textLifes.setPosition({ 50, 130 });
	m_textLifes.setString(getLifes());
	m_textCoins.setFont(m_font);
	m_textCoins.setFillColor(sf::Color::Red);
	m_textCoins.setPosition({ 240, 130 });
	m_textCoins.setString(getCoins());
}


ToolBar::~ToolBar()
{
}

void ToolBar::drow(sf::RenderWindow & window) const
{

	window.draw(m_rect1);
	window.draw(m_textLifes);

	window.draw(m_rect2);
	window.draw(m_textCoins);
}


void ToolBar::updateCoins()
{
	m_coins++;
	if (m_coins == 10)
	{
		updateLifes(true);
		m_coins = 0;
	}
		m_textCoins.setString(getCoins());
}

void ToolBar::updateLifes(bool b)
{
	if (b)
		m_lifes++;
	else
		m_lifes--;
	m_textLifes.setString(getLifes());
}

unsigned int ToolBar::getLife() const
{
	return m_lifes;
}

std::string ToolBar::getCoins()
{
	std::stringstream ss;
	ss << " " << m_coins;
	return ss.str();
}

std::string ToolBar::getLifes()
{
	std::stringstream ss;
	ss << " " << m_lifes;
	return ss.str();
}
