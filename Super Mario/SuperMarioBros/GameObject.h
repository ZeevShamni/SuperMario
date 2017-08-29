#pragma once
#ifdef _DEBUG
#pragma comment(lib, "sfml-main-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#elif defined(NDEBUG)
#pragma comment(lib, "sfml-main.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-audio.lib")
#else
#error "Unrecognized configuration!"
#endif

#include <SFML/Graphics.hpp>
#include "Macro.h"

class GameObject
{
public:
	GameObject(const std::string & texture, const sf::IntRect & rect);
	virtual ~GameObject() = 0;

	void drow(sf::RenderWindow& window);
	sf::IntRect getBounding() const;
	void setLeftBounding(const unsigned int left);
	void setBounding(const sf::IntRect & r);
	void changeDirection(const Direction & direction);


protected:
	sf::Texture m_texture;

private:
	sf::RectangleShape m_rect;
	sf::IntRect m_boundingRect;
};

