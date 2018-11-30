#pragma once
#include "Alphabet.h"

namespace jm
{
	class AlphaA : public Alphabet
	{
	public:
		//constructor
		AlphaA(const vec2& position, const RGB& color, const float size)
			: Alphabet(position, color, size)
		{ }

		//render
		void render() override
		{

		}
	};
}