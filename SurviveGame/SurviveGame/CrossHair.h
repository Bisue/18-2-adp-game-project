#pragma once
#include "Game2D.h"

namespace jm
{
	class CrossHair
	{
	private:
		vec2 mousePos;

	public:
		void updateMousePos(const vec2& pos)
		{
			mousePos = pos;
		}
		void render()
		{
			beginTransformation();
			{
				translate(mousePos);
				drawFilledCircle(Colors::green, 0.01f);
				drawWiredCircle(Colors::green, 0.04f);
			}
			endTransformation();
		}
	};
}