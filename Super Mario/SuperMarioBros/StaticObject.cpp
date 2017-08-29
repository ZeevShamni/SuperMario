#include "StaticObject.h"



StaticObject::StaticObject(const std::string & texture, const sf::IntRect & rect)
	:GameObject(texture, rect)
{
}


StaticObject::~StaticObject()
{
}
