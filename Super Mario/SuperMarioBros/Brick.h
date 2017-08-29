#pragma once
#include "StaticObject.h"
#include "Macro.h"

class Brick : public StaticObject
{
public:
	Brick(const sf::IntRect & rect);
	~Brick();
};
