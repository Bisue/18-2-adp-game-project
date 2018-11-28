#pragma once
#include "GameObject.h"

namespace jm
{
	class Item : public GameObject
	{
	private:
		RGB color;

		float rotateFloat = 0.0f;

	public:
		Item(const vec2 position, const float radius = 0.1f)
			: GameObject(position, radius), color(255, 102, 0)
		{

		}

		void update()
		{
			rotateFloat = DELTATIME;
		}

		void render() const override
		{
			beginTransformation();
			{
				translate(position);
				rotate(rotateFloat*60.0f);
				drawFilledPentagon(color, bodyRadius);
			}
			endTransformation();
		}
	};
}