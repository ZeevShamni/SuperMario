#pragma once
#include "GameObject.h"

class StaticObject : public GameObject
{
public:
	StaticObject(const std::string & texture, const sf::IntRect & rect);
	virtual ~StaticObject() = 0;
};

