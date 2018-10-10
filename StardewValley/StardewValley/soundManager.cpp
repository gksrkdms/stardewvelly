#include "stdafx.h"
#include "soundManager.h"


soundManager::soundManager()
	:m_system(NULL)
	,m_sound(NULL)
	,m_channel(NULL)
{
}


soundManager::~soundManager()
{
}

HRESULT soundManager::init()
{
	// 사운드 시스템 생성
	System_Create(&m_system);

	// 채널 수 설정
	m_system->init(TOTAL_SOUND_BUFFER, FMOD_INIT_NORMAL, 0);
	//FMOD_INIT_NORMAL : 옵션

	// 사운드, 채널 동적할당
	m_sound = new Sound*[TOTAL_SOUND_BUFFER];
	m_channel = new Channel*[TOTAL_SOUND_BUFFER];
	
	// 크기만큼 밀어줌 *TOTAL_SOUND_BUFFER
	memset(m_sound, 0, sizeof(Sound*)*TOTAL_SOUND_BUFFER);
	memset(m_channel, 0, sizeof(Channel*)*TOTAL_SOUND_BUFFER);
	
	return S_OK;
}

void soundManager::release()
{
	m_system->release();
	
}

void soundManager::update()
{
	m_system->update();

}

void soundManager::addSound(string soundName, bool isBGM, bool isLoop)
{
	if (isLoop)
	{
		if (isBGM)
		{
			m_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &m_sound[m_mapSounds.size()]);
		}

		else
		{
			m_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &m_sound[m_mapSounds.size()]);
		}
	}

	else
	{
		m_system->createStream(soundName.c_str(), FMOD_DEFAULT, 0, &m_sound[m_mapSounds.size()]);
	}

	// 맵 값 담음
	//m_sound[m_mapSounds.size()] 다음 인덱스에 값을 넣는 형태로 구성
	m_mapSounds.insert(make_pair(soundName, &m_sound[m_mapSounds.size()]));
	
}

void soundManager::play(string soundName, float volume)
{
	int index = 0;

	for (auto p : m_mapSounds)
	{
		if (p.first == soundName)
		{
			m_system->playSound(FMOD_CHANNEL_FREE, m_sound[index], false, &m_channel[index]);
			//false : pause가 가능한지 안한지

			m_channel[index]->setVolume(volume);
			break;
		}
		index++;
	}
}

void soundManager::stop(string soundName)
{
	int index = 0;

	for (auto p : m_mapSounds)
	{
		if (p.first == soundName)
		{
			m_channel[index]->stop();
			break;
		}
		index++;
	}
}

void soundManager::pause(string soundName)
{
	int index = 0;

	for (auto p : m_mapSounds)
	{
		if (p.first == soundName)
		{
			m_channel[index]->setPaused(true);
			break;
		}
		index++;
	}
}

void soundManager::resume(string soundName)
{
	int index = 0;

	for (auto p : m_mapSounds)
	{
		if (p.first == soundName)
		{
			m_channel[index]->setPaused(false);
			break;
		}
		index++;
	}
}

bool soundManager::isPlaying(string soundName)
{
	bool isPlay = false;
	int index = 0;

	for (auto p : m_mapSounds)
	{
		if (p.first == soundName)
		{
			m_channel[index]->isPlaying(&isPlay);
			break;
		}
		index++;
	}

	return isPlay;
}

bool soundManager::isPause(string soundName)
{
	bool isPause = false;
	int index = 0;

	for (auto p : m_mapSounds)
	{
		if (p.first == soundName)
		{
			m_channel[index]->getPaused(&isPause);
			break;
		}
		index++;
	}

	return isPause;
}
