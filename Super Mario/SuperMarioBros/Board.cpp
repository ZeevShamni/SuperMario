#include "Board.h"
#include "Mario.h"
#include "Turtle.h"
#include "Brick.h"
#include "Pipe.h"
#include "Coins.h"
#include "Flag.h"
#include <fstream>
#include <thread>



Board::Board(std::ifstream & file, sf::RenderWindow & window, std::shared_ptr<ToolBar> toolBar)
	:m_begin(MAX_WIDTH_BOARD / 2), m_end(MAX_WIDTH_BOARD),
	m_toolBar(toolBar)
{
	getLevel(file);
	restartLevel(window);
}

Board::~Board()
{
}

bool Board::moveMario(sf::RenderWindow & window, const Direction & direction)
{
	for (auto &player : m_players)
	{
		if (player->takeCoins(m_takens))
		{
			m_toolBar->updateCoins();
			Sound::play(Music::sound2);
		}

		if (player->checkStep(m_enemies, m_takens, m_statics, m_players, direction))
		{
			player->updatePositionForCollide(direction);
			moveCenterView(direction);

			checkIfSomeoneDead(window);

			return true;
		}
	}
	drow(window);
	return false;
}

void Board::moveEnemies(sf::RenderWindow & window)
{
	for (auto & enemie : m_enemies)
	{
		if (enemie->checkStep(m_enemies, m_takens, m_statics, m_players, Direction::left))
		{
			enemie->step();
		}
		else
		{
			enemie->updateDirection();
		}
	}
}

void Board::drow(sf::RenderWindow & window) const
{
	window.clear();

	window.setView(m_viewBacgroond);
	window.draw(m_rectView);

	for (auto & taken : m_takens)
	{
		taken->drow(window);
	}

	for (auto & statics : m_statics)
	{
		statics->drow(window);
	}

	window.setView(m_enemiesView);
	for (auto & enemie : m_enemies)
	{
		enemie->drow(window);
	}

	window.setView(m_marioView);
	m_toolBar->drow(window);
	for (auto & player : m_players)
	{
		player->drow(window);
	}

	window.display();
}

bool Board::checkIfEndLevel() const
{
	for (auto & player : m_players)
	{
		if (player->getOnFlag())
			return true;
	}
	return false;
}

void Board::putPlayerInPlace(const sf::IntRect & place, sf::RenderWindow & window) const
{
	for (size_t i = 0; i < MAX_WIDTH_BOARD / 4; i += Step)
	{
		for (auto & player : m_players)
		{
			player->step(Direction::right);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(15));
		drow(window);
	}
}

void Board::endLevel(sf::RenderWindow & window) const
{
	for (size_t i = BackgroundRectX - LetPixelsForFlag; i < BackgroundRectX + SizeOfObject; i += Step)
	{
		for (auto & player : m_players)
		{
			player->step(Direction::right);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		drow(window);
	}
}

bool Board::checkIfSomeoneDead(sf::RenderWindow & window)
{
	for (size_t i = 0; i < m_players.size(); i++)
		if (m_players[i]->getDead())
		{
			Sound::play(Music::sound6);
			killPlayer(i, window);
			m_toolBar->updateLifes(false);
			return true;
		}
	for (size_t i = 0; i < m_enemies.size(); i++)
		if (m_enemies[i]->getDead())
		{
			killEnemie(i);
			return false;
		}
	return false;
}

void Board::restartLevel(sf::RenderWindow & window)
{
	resetAllVectors();

	setView();

	createBoard(window);

	m_actualMarioPosition = MAX_WIDTH_BOARD / 4;
}

void Board::setView()
{
	m_textureView.loadFromFile(View1);
	m_rectView.setTexture(&m_textureView);
	m_rectView.setSize(sf::Vector2f(BackgroundRectX, BackgroundRectY));
	m_rectView.setPosition(sf::Vector2f(0, 0));

	m_viewBacgroond.setCenter(MAX_WIDTH_BOARD / 2, MAX_HEIGHT_BOARD / 2 + 2 * StepJump * Step);
	m_viewBacgroond.setSize(MAX_WIDTH_BOARD, MAX_HEIGHT_BOARD);

	m_enemiesView.setCenter(MAX_WIDTH_BOARD / 2, MAX_HEIGHT_BOARD / 2 + 2 * StepJump * Step);
	m_enemiesView.setSize(MAX_WIDTH_BOARD, MAX_HEIGHT_BOARD);

	m_marioView.setCenter(MAX_WIDTH_BOARD / 2, MAX_HEIGHT_BOARD / 2 + 2 * StepJump * Step);
	m_marioView.setSize(MAX_WIDTH_BOARD, MAX_HEIGHT_BOARD);
}

void Board::moveCenterView(const Direction & direction)
{
	sf::Vector2f v1 = m_enemiesView.getCenter();
	sf::Vector2f v2 = m_viewBacgroond.getCenter();

	switch (direction)
	{
	case Direction::up:
		m_enemiesView.setCenter(v1.x, v1.y - Step);
		m_viewBacgroond.setCenter(v2.x, v2.y - Step);
		break;

	case Direction::down:
		m_enemiesView.setCenter(v1.x, v1.y + Step);
		m_viewBacgroond.setCenter(v2.x, v2.y + Step);
		break;

	case Direction::right:
		if (m_end > m_viewBacgroond.getCenter().x && m_actualMarioPosition == StartMarioPosition)
		{
			m_enemiesView.setCenter(v1.x + Step, v1.y);
			m_viewBacgroond.setCenter(v2.x + Step, v2.y);
		}
		else
		{
			for (auto & player : m_players)
			{
				player->step(direction);
				m_actualMarioPosition += Step;
			}
		}
		break;

	case Direction::left:
		if (m_begin < m_viewBacgroond.getCenter().x &&
			m_actualMarioPosition == StartMarioPosition)
		{
			m_enemiesView.setCenter(v1.x - Step, v1.y);
			m_viewBacgroond.setCenter(v2.x - Step, v2.y);
		}
		else
		{
			for (auto & player : m_players)
			{
				player->step(direction);
				m_actualMarioPosition -= Step;
			}
		}
		break;
	}
}

void Board::getLevel(std::ifstream & file)
{
	m_levelInStr.clear();

	std::string line;
	while (getline(file, line))
	{
		if (line.compare("$$$") == 0)
			break;
		m_levelInStr.push_back(line);
	}
}

void Board::createBoard(sf::RenderWindow & window)
{
	// put the floor
	int i = 0;
	int stop = BackgroundRectX;

	while (true)
	{
		charToType('=', sf::Vector2i(i * SizeOfObject, MAX_HEIGHT_BOARD - LetPixelsUnderFloor
			- SizeOfObject), SizeOfObject);
		charToType('=', sf::Vector2i(i * SizeOfObject, MAX_HEIGHT_BOARD - LetPixelsUnderFloor
			- 2 * SizeOfObject), SizeOfObject);
		i++;
		stop -= SizeOfObject;
		if (stop <= 0)
			break;
	}

	// print all board
	// help for where start the board
	int help = MAX_HEIGHT_BOARD - LetPixelsUnderFloor - 2 * SizeOfObject - m_levelInStr.size() * SizeOfObject;

	for (int i = 0; i < m_levelInStr.size(); i++)
	{
		for (int j = 0; j < m_levelInStr[i].size(); j++)
		{
			charToType(m_levelInStr[i][j],
				sf::Vector2i(j * SizeOfObject, help + i * SizeOfObject), SizeOfObject);
		}
	}
	// put mario in his first place 
	charToType('M', sf::Vector2i(0, MAX_HEIGHT_BOARD - LetPixelsUnderFloor - 3 * SizeOfObject)
		, SizeOfObject);
	putPlayerInPlace(sf::IntRect(MAX_WIDTH_BOARD / 4, MAX_HEIGHT_BOARD -
		LetPixelsUnderFloor - 3 * SizeOfObject, SizeOfObject, SizeOfObject), window);

	// put flag in end of level
	charToType('F', sf::Vector2i(BackgroundRectX - LetPixelsForFlag, MAX_HEIGHT_BOARD - LetPixelsUnderFloor - 5 * SizeOfObject)
		, SizeOfObject);

	charToType('L', sf::Vector2i(SizeOfObject, MAX_HEIGHT_BOARD - LetPixelsUnderFloor - 5 * SizeOfObject)
		, SizeOfObject);
}

void Board::charToType(const char c, sf::Vector2i& pos, unsigned int size)
{
	switch (c)
	{
	case 'M': // mario
		m_players.push_back(std::make_unique<Mario>(sf::IntRect(pos.x, pos.y, size, size), sf::IntRect(MAX_WIDTH_BOARD / 4, pos.y, size, size)));
		break;

	case 'T': // enemie
		m_enemies.push_back(std::make_unique<Turtle>(sf::IntRect(pos.x, pos.y, size, size)));
		break;

	case 'F': // flag
		m_statics.push_back(std::make_unique<Flag>(sf::IntRect(pos.x, pos.y, size, size * 3)));
		break;

	case '=': // brick
		m_statics.push_back(std::make_unique<Brick>(sf::IntRect(pos.x, pos.y, size, size)));
		break;

	case 'P': // pipe
		m_statics.push_back(std::make_unique<Pipe>(sf::IntRect(pos.x, pos.y - 10, size, size + 10)));
		break;

	case '*': // coins
		m_takens.push_back(std::make_unique<Coins>(sf::IntRect(pos.x, pos.y, size, size)));
		break;

	case 'L': // bound left of level
		m_statics.push_back(std::make_unique<Brick>(sf::IntRect(-pos.x, pos.y, size, size * 3)));
		break;
	}
}

void Board::killPlayer(const int & index, sf::RenderWindow & window)
{
	// pul mario down
	for (size_t i = 0; i < (m_players[index]->getBounding().top - m_players[index]->getBounding().height) / Step; i += Step)
	{
		m_players[index]->step(Direction::down);
		std::this_thread::sleep_for(std::chrono::milliseconds(7));
		drow(window);
	}

	m_players.erase(m_players.begin() + index);
}

void Board::killEnemie(const int & index)
{
	m_enemies.erase(m_enemies.begin() + index);
	Sound::play(Music::sound4);
}

void Board::resetAllVectors()
{
	m_players.erase(m_players.begin(), m_players.end());
	m_enemies.erase(m_enemies.begin(), m_enemies.end());
	m_takens.erase(m_takens.begin(), m_takens.end());
	m_statics.erase(m_statics.begin(), m_statics.end());
}
