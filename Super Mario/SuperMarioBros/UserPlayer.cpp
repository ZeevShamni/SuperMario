#include "UserPlayer.h"
#include "Board.h"


UserPlayer::UserPlayer(const std::string & texture, const sf::IntRect & rect, const sf::IntRect & collide)
	: Moveable(texture, rect, collide, Direction::right),
	m_onFlag(false)
{
}

UserPlayer::~UserPlayer()
{
}

void UserPlayer::step(const Direction & direction)
{
	sf::IntRect rect = getBounding();

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
	//updatePositionForCollide(direction);
	setBounding(rect);
}

bool UserPlayer::checkStep(std::vector<std::unique_ptr<CompPlayer>>& m_enemies,
	std::vector<std::unique_ptr<ObjectTaken>>& m_takens, std::vector<std::unique_ptr<StaticObject>>& m_statics,
	std::vector<std::unique_ptr<UserPlayer>>& m_players, const Direction & direction)
{
	// if need to change direction and not move
	if ((direction == Direction::left || direction == Direction::right) && m_direction != direction)
	{
		updateDirection(direction);
		return false;
	}

	if (Moveable::checkStep(m_enemies, m_takens, m_statics, m_players, direction))
	{
		if (direction == Direction::left || direction == Direction::right)
		{
			bool collideWithEnemie = true;
			int help = collide(m_enemies, m_players, direction, collideWithEnemie);
			if (help == -1) // not collide
			{
				return true;
			}
			else
			{
				m_players[0]->setDead(true);
				return false;
			}
		}

		if (direction == Direction::down)
		{
			bool collideWithEnemie = true;
			int help = collide(m_enemies, m_players, direction, collideWithEnemie);
			if (help != -1) // collide
			{
				m_enemies[help]->setDead(true);
			}
			return true;
		}

		if (direction == Direction::up)
		{
			return true;
		}
	}
	return false;
}

bool UserPlayer::takeCoins(std::vector<std::unique_ptr<ObjectTaken>>& takens) const
{
	for (size_t i = 0; i < takens.size(); i++)
	{
		if (m_posForCollide.intersects(takens[i]->getBounding()))
		{
			takens.erase(takens.begin() + i);
			return true;
		}
	}
	return false;
}

void UserPlayer::updateDirection(const Direction & direction)
{
	if (direction != m_direction)
	{
		changeDirection(m_direction);
		m_direction = direction;
	}
}

void UserPlayer::setOnFlag(const bool & b)
{
	m_onFlag = b;
}

bool UserPlayer::getOnFlag() const
{
	return m_onFlag;
}
