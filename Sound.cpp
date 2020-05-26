#include "Sound.h"



CSound::CSound(const CHAR* _fileLocation, FMOD::System* _audioSystem, bool _bLoops)
{
	audioSystem = _audioSystem;


	FMOD_MODE LoopType;
	if (_bLoops)
	{
		// Will Loop
		LoopType = FMOD_LOOP_NORMAL;
	}
	else
	{
		// Wont Loop
		LoopType = FMOD_DEFAULT;
	}


	FMOD_RESULT result;
	result = _audioSystem->createSound(
		_fileLocation,
		LoopType,
		0,
		&Sound);


	if (result != FMOD_OK)
	{
		std::cout << "Error - Loading sounds " << std::endl;
	}
}


CSound::~CSound()
{
	Sound->release();
}


void CSound::PlaySound()
{
	FMOD_RESULT result;

	result = audioSystem->playSound(Sound, 0, false, 0);

	if (result != FMOD_OK)
	{
		std::cout << "Error - Playing sounds" << std::endl;
	}
}