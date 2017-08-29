#include "CompPlayer.h"
#include "Board.h"


CompPlayer::CompPlayer(const std::string & texture, const sf::IntRect & rect)
	:Moveable(texture, rect, rect, Direction::left)
{
}

CompPlayer::~CompPlayer()
{
}

void CompPlayer::step()
{
	if (m_direction == Direction::left)
	{
		setLeftBounding(getBounding().left - StepEnemies);
	}
	else
	{
		setLeftBounding(getBounding().left + StepEnemies);
	}
}

bool CompPlayer::checkStep(std::vector<std::unique_ptr<CompPlayer>>& m_enemies,
	std::vector<std::unique_ptr<ObjectTaken>>& m_takens,
	std::vector<std::unique_ptr<StaticObject>>& m_statics,
	std::vector<std::unique_ptr<UserPlayer>>& m_players, const Direction & direction)
{
	if (Moveable::checkStep(m_enemies, m_takens, m_statics, m_players, m_direction))
	{
		bool collideWithEnemie = true;
		int help = collide(m_enemies, m_players, m_direction, collideWithEnemie);
		if (help == -1) // not collide
		{
			updatePositionForCollide(direction);
		}
		else
		{
			if (!collideWithEnemie)
				m_players[help]->setDead(true);
			else
				updateDirection();
		}
		return true;
	}
	return false;
}

void CompPlayer::updatePositionForCollide(const Direction & direction)
{
	Moveable::updatePositionForCollide(m_direction);
}

void CompPlayer::updateDirection()
{
	if (m_direction == Direction::left)
	{
		changeDirection(Direction::right);
		m_direction = Direction::right;
	}
	else
	{
		changeDirection(Direction::left);
		m_direction = Direction::left;
	}
}
