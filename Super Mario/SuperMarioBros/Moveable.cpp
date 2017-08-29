#include "Moveable.h"
#include "CompPlayer.h"
#include "ObjectTaken.h"
#include "StaticObject.h"
#include "UserPlayer.h"
#include "Flag.h"


Moveable::Moveable(const std::string & texture, const sf::IntRect & rect, const sf::IntRect & collide, const Direction & d)
	: GameObject(texture, rect), 
	m_posForCollide(collide),
	m_direction(d),
	m_dead(false)
{
}

Moveable::~Moveable()
{
}

bool Moveable::checkStep(std::vector<std::unique_ptr<CompPlayer>> & m_enemies,
	std::vector<std::unique_ptr<ObjectTaken>> & m_takens,
	std::vector<std::unique_ptr<StaticObject>> & m_statics,
	std::vector <std::unique_ptr<UserPlayer>> & m_players, const Direction & direction)
{
	sf::IntRect rect = findWantedPlace(direction);

	for (auto & statics : m_statics)
	{
		sf::IntRect bounding = statics->getBounding();
		if (rect.intersects(bounding))
		{
			if (typeid(*statics) == typeid(Flag))
			{
				for (auto & player : m_players)
					player->setOnFlag(true);
			}
			return false;
		}
	}
	return true;
}

sf::IntRect Moveable::findWantedPlace(const Direction direction) const
{
	sf::IntRect rect = m_posForCollide;

	switch (direction)
	{
	case Direction::up:
		rect.top -= Step;
		break;

	case Direction::down:
		rect.top += Step;
		break;

	case Direction::left:
		rect.left -= Step;
		break;

	case Direction::right:
		rect.left += Step;
		break;
	}

	return rect;
}

void Moveable::updatePositionForCollide(const Direction & direction)
{
	sf::IntRect rect = findWantedPlace(direction);

	m_posForCollide = rect;
}

int Moveable::collide(std::vector<std::unique_ptr<CompPlayer>>& enemies,
		std::vector<std::unique_ptr<UserPlayer>>& players,
		const Direction & direction, bool & collideWithEnemie)
{
	sf::IntRect rect = findWantedPlace(direction);

	for (size_t i = 0; i < players.size(); i++)
	{
		if (m_posForCollide != players[i]->m_posForCollide) // not same player
			if (rect.intersects(players[i]->m_posForCollide))
			{
				collideWithEnemie = false;
				return i;
			}
	}

	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (m_posForCollide != enemies[i]->m_posForCollide) // not same enemie
			if (rect.intersects(enemies[i]->m_posForCollide))
				return i;
	}

	return -1;
}

bool Moveable::getDead() const
{
	return m_dead;
}

void Moveable::setDead(const bool & b)
{
	m_dead = b;
}
