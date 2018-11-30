#pragma once
#include "fmod.hpp"
#include <iostream>
#include <map>
#include <string>

namespace jm
{
	//singleton
	class SoundManager
	{
	private:
		static SoundManager* instance;

		FMOD::System* system = nullptr;
		std::map<std::string, FMOD::Sound*> soundMap;
		std::map<FMOD::Sound*, FMOD::Channel*> channelMap;

		FMOD_RESULT result;
		unsigned int version;
		void* extradriverdata = nullptr;

		SoundManager();

	public:
		static SoundManager* getInstance();

		~SoundManager();

		void initSound(const std::string& filename, const std::string& soundName, const bool& loop);
		void playSound(const std::string& soundName);
		void stopSound(const std::string& soundName);
		void stopAndPlaySound(const std::string soundName); // ������̸� ���߰� �ٽ����
	};
	using SM = SoundManager;
}