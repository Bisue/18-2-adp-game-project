#include "SurviveGame.h"

namespace jm
{
}

int main(void)
{
	std::cout << "[조작키]" << std::endl;
	std::cout << "W, A, S, D: 이동" << std::endl;
	std::cout << "1, 2, 3: 무기교체(아이템을 먹어서 Unlock)" << std::endl;
	std::cout << "마우스/마우스 왼쪽클릭: 조준/발사" << std::endl;

	jm::SurviveGame().run();

	return 0;
}