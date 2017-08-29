#pragma once
#include "Moveable.h"
class UserPlayer : public Moveable
{
public:
	UserPlayer(const std::string & texture, const sf::IntRect & rect, const sf::IntRect & collide);
	virtual ~UserPlayer() = 0;

	void step(const Direction & direction);

	virtual bool checkStep(std::vector<std::unique_ptr<CompPlayer>>& m_enemies,
		std::vector<std::unique_ptr<ObjectTaken>>& m_takens,
		std::vector<std::unique_ptr<StaticObject>>& m_statics,
		std::vector <std::unique_ptr<UserPlayer>> & m_players, const Direction & direction) override;

	bool takeCoins(std::vector<std::unique_ptr<ObjectTaken>>& takens) const;

	void updateDirection(const Direction & direction);

	void setOnFlag(const bool & b);
	bool getOnFlag() const;

private:
	bool m_onFlag;
};

