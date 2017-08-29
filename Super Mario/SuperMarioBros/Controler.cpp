#include "Controler.h"
#include <iostream>
#include <thread>

Controler::Controler()
	: m_file(Levels),
	m_window(sf::VideoMode(MAX_WIDTH_BOARD, MAX_HEIGHT_BOARD), "Mario", 5),
	m_level(1),
	m_time(sf::seconds(MoveEnemies))
{
	m_clock.restart();
}

Controler::~Controler()
{
}

void Controler::run()
{
	Sound::play(Music::sound1);
	
	m_toolBar = std::make_shared<ToolBar>();

	m_menu.startGame(m_window);

	while (!m_file.eof())
	{
		m_board = std::make_unique<Board>(m_file, m_window, m_toolBar);

		runLevel();
		m_board->endLevel(m_window);

		m_level++;
	}

	m_menu.thanks(m_window);
}

void Controler::runLevel()
{
	while (!m_board->checkIfEndLevel())
	{
		if (m_board->checkIfSomeoneDead(m_window))
		{
			if (m_toolBar->getLife() == -1)
			{
				m_menu.gameOver(m_window);
				exit(1);
			}
			m_menu.disqualified(m_window);
			m_board->restartLevel(m_window);
			Sound::stop(Music::sound6);

		}

		checkAll();
		
		m_window.clear();
		m_board->drow(m_window);
	}


	Sound::play(Music::sound5);
	m_menu.wellDone(m_window);
	Sound::stop(Music::sound5);
}

void Controler::careEvent(const bool fromJump)
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			exit(EXIT_SUCCESS);

		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				if (!fromJump)
					jump();
				break;

			case sf::Keyboard::Down:
				if (fromJump)
					m_board->moveMario(m_window, Direction::down);
				break;

			case sf::Keyboard::Left:
				m_board->moveMario(m_window, Direction::left);
				if (!fromJump)
					takePlayerDown();
				break;

			case sf::Keyboard::Right:
				m_board->moveMario(m_window, Direction::right);
				if (!fromJump)
					takePlayerDown();
				break;

			default:
				throw(std::invalid_argument("Invalid key"));
				break;
			}
			break;

		default:
			break;
		}
	}
}

void Controler::createView()
{
	sf::Vector2f centerOfView(MAX_WIDTH_BOARD / 4, MAX_WIDTH_BOARD / 2);

	sf::View view(centerOfView, sf::Vector2f(MAX_WIDTH_BOARD / 2, MAX_WIDTH_BOARD));

}

void Controler::jump()
{
	Sound::play(Music::sound3);

	for (size_t i = 0; i < StepJump; i++)
	{
		m_board->moveMario(m_window, Direction::up);
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
		try
		{
			careEvent(true);
		}

		catch (std::invalid_argument & e)
		{
		}

		if (clockTime())
			m_board->moveEnemies(m_window);

		m_window.clear();
		m_board->drow(m_window);
	}
	takePlayerDown();
}

void Controler::checkAll()
{
	try
	{
		careEvent(false);
	}

	catch (std::invalid_argument & e)
	{
	}

	if(clockTime())
		m_board->moveEnemies(m_window);
}

bool Controler::clockTime()
{
	if (m_clock.getElapsedTime() >= m_time)
	{
		m_clock.restart();
		return true;
	}
	else
		return false;
}

void Controler::takePlayerDown()
{
	// take mario down
	while (true)
	{

		if (!m_board->moveMario(m_window, Direction::down))
			break;
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		try
		{
			careEvent(true);
		}

		catch (std::invalid_argument & e)
		{
		}

		if (clockTime())
			m_board->moveEnemies(m_window);

		m_window.clear();
		m_board->drow(m_window);
	}
}
