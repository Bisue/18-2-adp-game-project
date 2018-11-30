#pragma once
#include "Game2D.h"

namespace jm
{
	class Alphabet
	{
	protected:
		vec2 position;
		RGB color;
		float size;
		
	public:
		//constructor
		Alphabet(const vec2& position, const RGB& color, const float size)
			: position(position), color(color), size(size)
		{ }

		//getter, setter
		vec2 getPos()
		{
			return position;
		}
		void setPos(const vec2& newPos)
		{
			position = newPos;
		}
		RGB getColor()
		{
			return color;
		}
		void setPos(const RGB& newColor)
		{
			color = newColor;
		}
		float getSize()
		{
			return size;
		}
		void setSize(const float& newSize)
		{
			size = newSize;
		}

		//render
		virtual void render() = 0;
	};
}