#pragma once
#include <functional>
#include <vector>

namespace jm
{
	// [미사용]
	// 리턴값이 없고, 매개변수를 받지 않는
	// 콜백을 편하게 하기 위한 클래스
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