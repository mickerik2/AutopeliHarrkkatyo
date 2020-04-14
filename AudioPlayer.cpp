#include "AudioPlayer.h"

AudioPlayer::AudioPlayer()
{
	if (!EngineBuffer.loadFromFile("engineloop.wav"))
	{
		//Error
	}
	if (!CrashBuffer.loadFromFile("crash.ogg"))
	{
		//Error
	}
	Crashsound.setBuffer(CrashBuffer);
	Carsound.setBuffer(EngineBuffer);
	Carsound.setLoop(true);
}

void AudioPlayer::playEngineSound()
{
	Carsound.play();
}

void AudioPlayer::stopAllInGameSounds()
{
	Carsound.stop();
}

void AudioPlayer::changePitch(float pitch)
{
	Carsound.setPitch(pitch);
}
void AudioPlayer::playCrashSound()
{
	Crashsound.play();
}