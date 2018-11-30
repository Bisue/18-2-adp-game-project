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
		float cellSize;

		int canvas[5][5];
		vec2 cellPos[5][5];
		
	public:
		//constructor
		Alphabet(const vec2& position, const RGB& color, const float size = 0.5f)
			: position(position), color(color), size(size), cellSize((size / 5.0f)*0.9f)
		{
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					cellPos[i][j] = vec2(-(2 * cellSize) + (j*cellSize), +(2 * cellSize) - (i*cellSize));
				}
			}
		}

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

		//canvas setting
		void setText(int text[5][5])
		{
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					canvas[i][j] = text[i][j];
				}
			}
		}

		//render
		void render()
		{
			beginTransformation();
			translate(position);
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (canvas[i][j] == 1)
					{
						beginTransformation();
						{
							translate(cellPos[i][j]);
							drawFilledBox(color, cellSize, cellSize);
						}
						endTransformation();
					}
				}
			}
			endTransformation();
		}
	};
}