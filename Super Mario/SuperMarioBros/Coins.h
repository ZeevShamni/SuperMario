#pragma once
#include "ObjectTaken.h"
#include "Macro.h"

class Coins : public ObjectTaken
{
public:
	Coins(const sf::IntRect & rect);
	~Coins();
};

