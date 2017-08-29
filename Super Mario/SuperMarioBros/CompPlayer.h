#pragma once
#include "Moveable.h"
#include "Macro.h"

class CompPlayer : public Moveable
{
public:
	CompPlayer(const std::string & texture, const sf::IntRect & rect);
	virtual ~CompPlayer();

	void step();

	virtual bool checkStep(std::vector <std::unique_ptr<CompPlayer>> & m_enemies,
		std::vector <std::unique_ptr<ObjectTaken>> & m_takens,
		std::vector <std::unique_ptr<StaticObject>> & m_statics,
		std::vector <std::unique_ptr<UserPlayer>> & m_players, const Direction & direction);

	virtual void updatePositionForCollide(const Direction & direction) override;

	void updateDirection();
};