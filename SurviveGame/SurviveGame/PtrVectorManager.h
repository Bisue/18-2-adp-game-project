#pragma once
#include <vector>
#include <memory>

namespace jm
{
	template<class T>
	class PtrVectorManager
	{
	private:
		static PtrVectorManager<T>* instance;

	protected:
		std::vector<std::shared_ptr<T>> body;

	public:
		static PtrVectorManager<T>* getInstance()
		{
			if (instance == nullptr)
			{
				instance = new PtrVectorManager<T>();
			}
			return instance;
		}

		void add(T& element);
		void update();
	};
}