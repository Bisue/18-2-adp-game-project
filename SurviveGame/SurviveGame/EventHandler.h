#pragma once
#include <functional>
#include <vector>

namespace jm
{
	class EventHandler
	{
	private:
		std::vector<std::function<void(void)>> callBacks;

	public:
		//todo: delete function
		void add(std::function<void(void)>& function) //use lambda []() { ...functions... }
		{
			callBacks.push_back(function);
		}
		void invokeAll()
		{
			for (int i = 0; i < callBacks.size(); i++)
			{
				callBacks[i]();
			}
		}
		EventHandler& operator+=(std::function<void(void)> lambda)
		{
			add(lambda);
			return *this;
		}
	};
}