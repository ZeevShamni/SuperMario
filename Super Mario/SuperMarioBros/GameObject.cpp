#include "GameObject.h"



GameObject::GameObject(const std::string & texture, const sf::IntRect & rect)
	: m_boundingRect(rect)
{
	m_rect.setPosition(rect.left, rect.top);
	m_rect.setSize(sf::Vector2f(m_boundingRect.width, m_boundingRect.height));

	m_texture.loadFromFile(texture);
	m_rect.setTexture(&m_texture);
}


GameObject::~GameObject()
{
}

void GameObject::drow(sf::RenderWindow & window)
{
	window.draw(m_rect);
}

sf::IntRect GameObject::getBounding() const
{
	return m_boundingRect;
}

void GameObject::setLeftBounding(const unsigned int left)
{
	m_boundingRect.left = left;

	sf::Vector2f pos = m_rect.getPosition();
	pos.x = left;
	m_rect.setPosition(pos);
}

void GameObject::setBounding(const sf::IntRect & r)
{
	m_boundingRect = r;

	m_rect.setPosition(r.left, r.top);
}

void GameObject::changeDirection(const Direction & direction)
{
	m_rect.scale(sf::Vector2f(-1, 1));

	if (direction == Direction::left)
	{
		m_rect.setPosition(m_rect.getPosition().x - SizeOfObject, m_rect.getPosition().y);
		m_boundingRect.left -= SizeOfObject;
	}

	if (direction == Direction::right)
	{
		m_rect.setPosition(m_rect.getPosition().x + SizeOfObject, m_rect.getPosition().y);
		m_boundingRect.left += SizeOfObject;
	}
}

