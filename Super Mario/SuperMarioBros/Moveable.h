#pragma once
#include "GameObject.h"
#include "Macro.h"
#include <memory>
class CompPlayer;
class ObjectTaken;
class StaticObject;
class UserPlayer;



class Moveable : public GameObject
{
public:
	Moveable(const std::string & texture, const sf::IntRect & rect, const sf::IntRect & collide, const Direction & d);

	virtual ~Moveable() = 0;

	virtual bool checkStep(std::vector <std::unique_ptr<CompPlayer>> & m_enemies,
		std::vector <std::unique_ptr<ObjectTaken>> & m_takens,
		std::vector <std::unique_ptr<StaticObject>> & m_statics,
		std::vector <std::unique_ptr<UserPlayer>> & m_players, const Direction & direction);

	sf::IntRect findWantedPlace(const Direction direction) const;

	virtual void updatePositionForCollide(const Direction & direction);

	int collide(std::vector<std::unique_ptr<CompPlayer>>& enemies,
		std::vector<std::unique_ptr<UserPlayer>>& players,
		const Direction & direction, bool & collideWithEnemie);

	bool getDead() const;
	void setDead(const bool & b);

protected:
	sf::IntRect m_posForCollide;
	Direction m_direction;
	bool m_dead; // know if this player dead
};

