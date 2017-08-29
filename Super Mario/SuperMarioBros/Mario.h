#pragma once
#include "UserPlayer.h"
#include "Macro.h"


class Mario : public UserPlayer
{
public:
	Mario(const sf::IntRect & rect, const sf::IntRect & collide);
	~Mario();
};

