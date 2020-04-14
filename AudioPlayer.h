#pragma once
#include <SFML/Audio.hpp>


class AudioPlayer
{
public:
	void playEngineSound();
	void playCrashSound();

	void stopAllInGameSounds();
	void changePitch(float pitch);
	AudioPlayer();

private:
	sf::SoundBuffer EngineBuffer;
	sf::SoundBuffer CrashBuffer;

	sf::Sound Carsound;
	sf::Sound Crashsound;

};
