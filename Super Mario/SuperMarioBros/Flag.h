#pragma once
#include "StaticObject.h"
#include "Macro.h"

class Flag : public StaticObject
{
public:
	Flag(const sf::IntRect & rect);
	~Flag();
};

