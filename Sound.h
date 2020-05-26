#pragma once

#include <fmod.hpp>
#include <iostream>
#include <freeglut.h>

class CSound
{
public:
	CSound(const CHAR* _fileLocation, FMOD::System* _audioSystem, bool _bLoops = false);
	~CSound();

	void PlaySound();

private:
	FMOD::System* audioSystem;
	FMOD::Sound* Sound;

};

