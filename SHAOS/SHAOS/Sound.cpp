#include "pch.h"
#include "sound.h"
#pragma comment(lib,"FMOD/lib/fmod64_vc.lib")

CSound::CSound()
{
}

CSound::~CSound()
{
}

void CSound::SoundSystem()
{
	FMOD_System_Create(&pSystem);

	FMOD_System_Init(pSystem, 10, FMOD_INIT_NORMAL,nullptr);

	FMOD_System_CreateSound(pSystem, "Sound/Title_BGM.mp3", FMOD_LOOP_NORMAL, nullptr, &pSound[0]);//
	FMOD_System_CreateSound(pSystem, "Sound/Game_BGM.wav", FMOD_LOOP_NORMAL, nullptr, &pSound[1]);//
	FMOD_System_CreateSound(pSystem, "Sound/basic_Attack.wav", FMOD_LOOP_OFF, nullptr, &pSound[2]);
	FMOD_System_CreateSound(pSystem, "Sound/return_Sound.wav", FMOD_LOOP_OFF, nullptr, &pSound[3]);
	FMOD_System_CreateSound(pSystem, "Sound/cooltime_Zero.mp3", FMOD_LOOP_OFF, nullptr, &pSound[4]);
	FMOD_System_CreateSound(pSystem, "Sound/Lose_BGM.mp3", FMOD_LOOP_OFF, nullptr, &pSound[5]);//
	FMOD_System_CreateSound(pSystem, "Sound/Win_BGM.mp3", FMOD_LOOP_OFF, nullptr, &pSound[6]);//
	//FMOD_System_CreateSound(pSystem, "Sound\°­°ø°Ý.wav", FMOD_LOOP_NORMAL, nullptr, &pSound[7]);
}

void CSound::MyPlaySound(int nsound, int nchannel)
{
	FMOD_System_PlaySound(pSystem, pSound[nsound], nullptr, 0, &pChannel[nchannel]);
}

void CSound::SoundStop(int nchannel)
{
	FMOD_Channel_Stop(pChannel[nchannel]);
}

void CSound::SoundRelease()
{
	FMOD_System_Release(pSystem);
}
