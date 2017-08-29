#pragma once
#include "StaticObject.h"
#include "Macro.h"

class Pipe : public StaticObject

{
public:
	Pipe(const sf::IntRect & rect);
	~Pipe();
};

