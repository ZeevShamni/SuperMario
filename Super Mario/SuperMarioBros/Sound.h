#pragma once
#include"GameObject.h"
#include<SFML\Audio.hpp>


class Sound
{
public:
	Sound();
	~Sound();

	static void play(Music sound);
	static void stop(Music sound);

private:
	sf::SoundBuffer m_audio1; // back ground
	sf::SoundBuffer m_audio2; // coins
	sf::SoundBuffer m_audio3; // jump
	sf::SoundBuffer m_audio4; // kill enemie
	sf::SoundBuffer m_audio5; // applise
	sf::SoundBuffer m_audio6; // kill mario

	static sf::Time offset;
	static sf::Sound m_sound1;
	static sf::Sound m_sound2;
	static sf::Sound m_sound3;
	static sf::Sound m_sound4;
	static sf::Sound m_sound5;
    static sf::Sound m_sound6;
};
