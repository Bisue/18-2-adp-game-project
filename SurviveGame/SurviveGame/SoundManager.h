#pragma once
#include "fmod.hpp"
#include <iostream>
#include <map>
#include <string>

namespace jm
{
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
		static SoundManager* getInstance()
		{
			if (instance == nullptr)
			{
				instance = new SoundManager();
			}
			return instance;
		}

		~SoundManager()
		{
			system->release();
		}

		void initSound(const std::string& filename, const std::string& soundName, const bool& loop);
		void playSound(const std::string& soundName);
		void stopSound(const std::string& soundName);
		void stopAndPlaySound(const std::string soundName); // 재생중이면 멈추고 다시재생
	};
	using SM = SoundManager;
}