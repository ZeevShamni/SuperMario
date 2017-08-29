#include "Sound.h"



Sound::Sound()
{
	m_audio1.loadFromFile(SoundPath1);
	m_audio2.loadFromFile(SoundPath2);
	m_audio3.loadFromFile(SoundPath3);
	m_audio4.loadFromFile(SoundPath4);
	m_audio5.loadFromFile(SoundPath5);
	m_audio6.loadFromFile(SoundPath6);
	
	m_sound1.setBuffer(m_audio1);
	m_sound1.setVolume(16);
	m_sound1.setLoop(true);
	m_sound2.setBuffer(m_audio2);
	m_sound3.setBuffer(m_audio3);
	m_sound3.setVolume(10);
	m_sound4.setBuffer(m_audio4);
	m_sound4.setVolume(15);
	m_sound5.setBuffer(m_audio5);
	m_sound5.setVolume(15);
	m_sound6.setBuffer(m_audio6);
	m_sound6.setVolume(50);
	m_sound6.setPlayingOffset(offset);
}


Sound::~Sound()
{
}

sf::Time Sound::offset(sf::seconds(1.5));
sf::Sound Sound::m_sound1;
sf::Sound Sound::m_sound2;
sf::Sound Sound::m_sound3;
sf::Sound Sound::m_sound4;
sf::Sound Sound::m_sound5;
sf::Sound Sound::m_sound6;


void Sound::play(Music sound)
{
	switch (sound)
	{

	case Music::sound1:
		m_sound1.play();
		break;

	case Music::sound2:
		m_sound2.play();
		break;

	case Music::sound3:
		m_sound3.play();
		break;

	case Music::sound4:
		m_sound4.play();
		break;

	case Music::sound5:
		m_sound5.play();
		break;

	case Music::sound6:
		m_sound6.play();
		break;
	}
}

void Sound::stop(Music sound)
{
	switch (sound)
	{

	case Music::sound1:
		m_sound1.stop();
		break;

	case Music::sound2:
		m_sound2.stop();
		break;

	case Music::sound3:
		m_sound3.stop();
		break;

	case Music::sound4:
		m_sound4.stop();
		break;

	case Music::sound5:
		m_sound5.stop();
		break;

	case Music::sound6:
		m_sound6.stop();
		m_sound6.setPlayingOffset(offset);
		break;
	}
}

