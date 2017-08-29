#pragma once
#include "StaticObject.h"

class ObjectTaken : public StaticObject
{
public:
	ObjectTaken(const std::string & texture, const sf::IntRect & rect);
	virtual ~ObjectTaken();

	void take() {} // not implemented
};

