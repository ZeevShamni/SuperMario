#include "Menu.h"



Menu::Menu()
{

	m_textureBackground.loadFromFile(Mario2Path);
	m_texturePlay.loadFromFile(PlayPath);
	m_textureHelp.loadFromFile(HelpPath);
	m_textureExit.loadFromFile(ExitPath);
	m_textureInstructions.loadFromFile(InstructionsPath);
	m_textureBack.loadFromFile(BackPath);
	m_textureDisqua.loadFromFile(DisquaPath);
	m_textureOver.loadFromFile(OverPath);
	m_textureDone.loadFromFile(DonePath);
	m_textureThank.loadFromFile(ThankPath);

	//m_rectBackground.setFillColor(sf::Color::Green);
	m_rectBackground.setTexture(&m_textureBackground);
	m_rectPlay.setTexture(&m_texturePlay);
	m_rectHelp.setTexture(&m_textureHelp);
	m_rectExit.setTexture(&m_textureExit);
	m_rectInstructions.setTexture(&m_textureInstructions);
	m_rectBack.setTexture(&m_textureBack);
	m_rectDisqua.setTexture(&m_textureDisqua);
	m_rectOver.setTexture(&m_textureOver);
	m_rectDone.setTexture(&m_textureDone);
	m_rectThank.setTexture(&m_textureThank);

	m_rectBackground.setSize({ MAX_WIDTH_BOARD,
		MAX_HEIGHT_BOARD });
	m_rectPlay.setSize({ 150, 100 });
	m_rectHelp.setSize({ 150, 100 });
	m_rectExit.setSize({ 150, 100 });
	m_rectInstructions.setSize({ 400, 500 });
	m_rectBack.setSize({ 150, 100 });
	m_rectDisqua.setSize({ 200, 150 });
	m_rectOver.setSize({ 300, 200 });
	m_rectDone.setSize({ 200, 150 });
	m_rectThank.setSize({ 200, 150 });

	m_rectPlay.setPosition({ MAX_WIDTH_BOARD / 2 - 200, MAX_HEIGHT_BOARD / 3 - 200 });
	m_rectHelp.setPosition({ MAX_WIDTH_BOARD / 2 , MAX_HEIGHT_BOARD / 3 - 200 });
	m_rectExit.setPosition({ MAX_WIDTH_BOARD / 2 + 200 , MAX_HEIGHT_BOARD / 3 - 200 });
	m_rectInstructions.setPosition({ MAX_WIDTH_BOARD / 2 - 200, MAX_HEIGHT_BOARD / 3 - 100 });
	m_rectBack.setPosition({ MAX_WIDTH_BOARD / 2 - 370, MAX_HEIGHT_BOARD / 2 });
	m_rectDisqua.setPosition({ MAX_WIDTH_BOARD / 2 - 100, MAX_HEIGHT_BOARD / 2 });
	m_rectOver.setPosition({ MAX_WIDTH_BOARD / 2 - 150, MAX_HEIGHT_BOARD / 3 });
	m_rectDone.setPosition({ MAX_WIDTH_BOARD / 2 - 100, MAX_HEIGHT_BOARD / 3 });
	m_rectThank.setPosition({ MAX_WIDTH_BOARD / 2 - 100, MAX_HEIGHT_BOARD / 3 });
}


Menu::~Menu()
{
}

void Menu::startGame(sf::RenderWindow & window)
{
	bool again = true;
	while (again)
	{
		window.draw(m_rectBackground);
		window.draw(m_rectPlay);
		window.draw(m_rectHelp);
		window.draw(m_rectExit);
		window.display();
		careEvent(window, again);
	}
}

void Menu::disqualified(sf::RenderWindow & window)
{
	window.draw(m_rectDisqua);
	window.display();
	std::this_thread::sleep_for(std::chrono::milliseconds(2500));
}

void Menu::gameOver(sf::RenderWindow & window)
{
	window.draw(m_rectOver);
	window.display();
	std::this_thread::sleep_for(std::chrono::milliseconds(2500));
}

void Menu::wellDone(sf::RenderWindow & window)
{
	window.draw(m_rectDone);
	window.display();
	std::this_thread::sleep_for(std::chrono::milliseconds(2500));
}

void Menu::thanks(sf::RenderWindow & window)
{
	window.draw(m_rectThank);
	window.display();
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}

void Menu::careEvent(sf::RenderWindow& window, bool & again)
{

	again = false;
	bool b = true;
	while (window.isOpen() && b)
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(1);
			}
			if (event.type == sf::Event::MouseButtonPressed)
				mousePresse(window, b, again);
			//if (event.type == sf::Event::MouseMoved)
			//mouseMouved(window);

			// window.clear();

		}
	}
}


void Menu::mousePresse(sf::RenderWindow& window, bool & b, bool & again)
{
	sf::Vector2i mousePosition;
	mousePosition = sf::Mouse::getPosition(window);

	sf::IntRect rect(m_rectExit.getGlobalBounds());
	if (rect.contains(mousePosition))
		exit(1);

	rect.top = m_rectPlay.getGlobalBounds().top;
	rect.left = m_rectPlay.getGlobalBounds().left;

	if (rect.contains(mousePosition))
	{
		b = false;
		return;
	}

	rect.top = m_rectHelp.getGlobalBounds().top;
	rect.left = m_rectHelp.getGlobalBounds().left;

	if (rect.contains(mousePosition))
	{

		window.draw(m_rectBackground);
		window.draw(m_rectInstructions);
		window.draw(m_rectBack);
		window.display();

		while (window.isOpen() && b)
		{
			sf::Event event;

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
					exit(1);
				}
				if (event.type == sf::Event::MouseButtonPressed)
				{
					mousePosition = sf::Mouse::getPosition(window);
					rect.top = m_rectBack.getGlobalBounds().top;
					rect.left = m_rectBack.getGlobalBounds().left;
					if (rect.contains(mousePosition))
					{
						window.clear();
						b = false;
						again = true;
					}
				}

			}
		}

	}
}

