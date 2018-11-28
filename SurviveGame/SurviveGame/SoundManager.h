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

		SoundManager()
		{
			result = FMOD::System_Create(&system);
			if (result != FMOD_OK)
			{
				std::cout << "FMOD::System_Create() fail" << std::endl;
				exit(-1);
			}
			result = system->getVersion(&version);
			if (result != FMOD_OK)
			{
				std::cout << "system->getVersion() fail" << std::endl;
				exit(-1);
			}
			result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
			if (result != FMOD_OK)
			{
				std::cout << "system->init() fail" << std::endl;
				exit(-1);
			}
		}

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

		void initSound(const std::string& filename, const std::string& soundName, const bool& loop)
		{
			soundMap[soundName] = nullptr;
			auto& soundPtr = soundMap[soundName];
			
			const int loopFlag = loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;

			const std::string folder(".\\Sounds\\");
			result = system->createSound((folder + filename).c_str(), loopFlag, 0, &soundPtr);
			if (result != FMOD_OK)
			{
				std::cout << "system->createSound() fail" << std::endl;
				std::cout << (folder + filename).c_str() << std::endl;
				exit(-1);
			}
		}
		void playSound(const std::string& soundName)
		{
			if (soundMap.count(soundName) <= 0)
			{
				std::cout << soundName << "isn't initialized." << std::endl;
				exit(-1);
			}
			
			const auto& soundPtr = soundMap[soundName];
			auto& channelPtr = channelMap[soundPtr];

			bool isPlaying = false;
			result = channelPtr->isPlaying(&isPlaying);
			if (isPlaying)
				return;

			result = system->playSound(soundPtr, 0, false, &channelPtr);
			if (result != FMOD_OK)
			{
				std::cout << "system->playSound() fail" << std::endl;
				exit(-1);
			}
		}
		void stopSound(const std::string& soundName)
		{
			if (soundMap.count(soundName) <= 0)
			{
				std::cout << soundName << "isn't initialized." << std::endl;
				exit(-1);
			}

			const auto& soundPtr = soundMap[soundName];
			auto& channelPtr = channelMap[soundPtr];

			bool isPlaying = false;
			result = channelPtr->isPlaying(&isPlaying);
			if (!isPlaying)
				return;

			result = channelPtr->stop();
			if (result != FMOD_OK)
			{
				std::cout << soundName << "channelPtr->stop() fail" << std::endl;
				exit(-1);
			}
		}

		void stopAndPlaySound(const std::string soundName)
		{
			if (soundMap.count(soundName) <= 0)
			{
				std::cout << soundName << "isn't initialized." << std::endl;
				exit(-1);
			}

			const auto& soundPtr = soundMap[soundName];
			auto& channelPtr = channelMap[soundPtr];

			bool isPlaying = false;
			result = channelPtr->isPlaying(&isPlaying);
			if (isPlaying)
				stopSound(soundName);

			result = system->playSound(soundPtr, 0, false, &channelPtr);
			if (result != FMOD_OK)
			{
				std::cout << "system->playSound() fail" << std::endl;
				exit(-1);
			}
		}
	};
}