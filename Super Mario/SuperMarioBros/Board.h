#pragma once
#include "ToolBar.h"
#include "CompPlayer.h"
#include "UserPlayer.h"
#include "ObjectTaken.h"
#include "StaticObject.h"
#include "Macro.h"
#include "Sound.h"	
#include <vector>
#include <memory>

class Board
{
public:
	Board(std::ifstream & file, sf::RenderWindow & window, std::shared_ptr<ToolBar> toolBar);
	~Board();

	bool moveMario(sf::RenderWindow & window, const Direction & direction);

	void moveEnemies(sf::RenderWindow & window);

	void drow(sf::RenderWindow & window) const;

	bool checkIfEndLevel() const;

	void putPlayerInPlace(const sf::IntRect & place, sf::RenderWindow & window) const; // put mario in his place when level start
	void endLevel(sf::RenderWindow & window) const; // move mario to end level

	bool checkIfSomeoneDead(sf::RenderWindow & window);

	void restartLevel(sf::RenderWindow & window);

private:
	std::shared_ptr<ToolBar> m_toolBar;

	std::vector <std::unique_ptr<CompPlayer>> m_enemies;
	std::vector <std::unique_ptr<UserPlayer>> m_players;
	std::vector <std::unique_ptr<ObjectTaken>> m_takens;
	std::vector <std::unique_ptr<StaticObject>> m_statics;

	// view of picture
	sf::View m_viewBacgroond;
	sf::Texture m_textureView;
	sf::RectangleShape m_rectView;

	// view of all object
	sf::View m_enemiesView;

	// view of mario
	sf::View m_marioView;
	
	// begin, end coordinate of board  
	int m_begin; 
	int m_end;

	std::vector<std::string> m_levelInStr;

	// mario position (X) when view dont move
	int m_actualMarioPosition;



	// private function
	void setView();
	void moveCenterView(const Direction & direction);

	void getLevel(std::ifstream & file);
	void createBoard(sf::RenderWindow & window);
	void charToType(const char c, sf::Vector2i& pos, unsigned int size); // convert from char to correct class


	void killPlayer(const int & inde, sf::RenderWindow & window);
	void killEnemie(const int & index);
	
	void resetAllVectors();
};

