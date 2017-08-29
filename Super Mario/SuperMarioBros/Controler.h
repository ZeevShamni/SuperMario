#pragma once
#include "Board.h"
#include "Menu.h"
#include <fstream>



class Controler
{
public:
	Controler();
	~Controler();

	void run();
	
	void runLevel();

	void careEvent(const bool fromJump);

	void createView();


private:
	Sound m_sound;
	Menu m_menu;
	std::shared_ptr<ToolBar> m_toolBar;
	std::unique_ptr<Board> m_board;
	sf::RenderWindow m_window;
	std::ifstream m_file;
	unsigned int m_level;
	sf::Clock m_clock;
	sf::Time m_time;
	

	// private function
	void jump();

	void checkAll();
	
	bool clockTime();

	void takePlayerDown();

};
