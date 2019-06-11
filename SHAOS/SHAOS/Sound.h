#pragma once

#include "FMOD\include\fmod.hpp" 

using namespace FMOD;

class CSound {
	FMOD_SYSTEM* pSystem;
	FMOD_SOUND* pSound[10];
	FMOD_CHANNEL* pChannel[10];
public:
	CSound();
	~CSound();
	void SoundSystem();
	void MyPlaySound(int nsound, int nchannel);
	void SoundStop(int nchannel);
	void SoundRelease();
};

