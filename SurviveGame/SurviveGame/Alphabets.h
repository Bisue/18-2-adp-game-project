#pragma once
#include "Alphabet.h"

namespace jm
{
	class AlphaA : public Alphabet
	{
	public:
		AlphaA(const vec2& position, const RGB& color, const float size = 0.5f)
			: Alphabet(position, color, size)
		{
			int text[5][5] = {
				{0,1,1,1,0},
				{1,0,0,0,1},
				{1,0,0,0,1},
				{1,1,1,1,1},
				{1,0,0,0,1}
			};
			setText(text);
		}
	};
	class AlphaB : public Alphabet
	{
	public:
		AlphaB(const vec2& position, const RGB& color, const float size = 0.5f)
			: Alphabet(position, color, size)
		{
			int text[5][5] = {
				{1,1,1,1,0},
				{1,0,0,0,1},
				{1,0,1,1,0},
				{1,0,0,0,1},
				{1,1,1,1,0}
			};
			setText(text);
		}
	};
	class AlphaC : public Alphabet
	{
	public:
		AlphaC(const vec2& position, const RGB& color, const float size = 0.5f)
			: Alphabet(position, color, size)
		{
			int text[5][5] = {
				{0,1,1,1,0},
				{1,0,0,0,1},
				{1,0,0,0,0},
				{1,0,0,0,1},
				{0,1,1,1,0}
			};
			setText(text);
		}
	};
	class AlphaD : public Alphabet
	{
	public:
		AlphaD(const vec2& position, const RGB& color, const float size = 0.5f)
			: Alphabet(position, color, size)
		{
			int text[5][5] = {
				{1,1,1,1,0},
				{1,0,0,0,1},
				{1,0,0,0,1},
				{1,0,0,0,1},
				{1,1,1,1,0}
			};
			setText(text);
		}
	};
	class AlphaE : public Alphabet
	{
	public:
		AlphaE(const vec2& position, const RGB& color, const float size = 0.5f)
			: Alphabet(position, color, size)
		{
			int text[5][5] = {
				{0,1,1,1,1},
				{1,0,0,0,0},
				{1,1,1,1,0},
				{1,0,0,0,0},
				{0,1,1,1,1}
			};
			setText(text);
		}
	};
	class AlphaF : public Alphabet
	{
	public:
		AlphaF(const vec2& position, const RGB& color, const float size = 0.5f)
			: Alphabet(position, color, size)
		{
			int text[5][5] = {
				{0,1,1,1,1},
				{1,0,0,0,0},
				{1,1,1,1,0},
				{1,0,0,0,0},
				{1,0,0,0,0}
			};
			setText(text);
		}
	};
	class AlphaG : public Alphabet
	{
	public:
		AlphaG(const vec2& position, const RGB& color, const float size = 0.5f)
			: Alphabet(position, color, size)
		{
			int text[5][5] = {
				{0,1,1,1,1},
				{1,0,0,0,0},
				{1,0,0,1,1},
				{1,0,0,0,1},
				{0,1,1,1,0}
			};
			setText(text);
		}
	};
	class AlphaH : public Alphabet
	{
	public:
		AlphaH(const vec2& position, const RGB& color, const float size = 0.5f)
			: Alphabet(position, color, size)
		{
			int text[5][5] = {
				{1,0,0,0,1},
				{1,0,0,0,1},
				{1,1,1,1,1},
				{1,0,0,0,1},
				{1,0,0,0,1}
			};
			setText(text);
		}
	};
	class AlphaI : public Alphabet
	{
	public:
		AlphaI(const vec2& position, const RGB& color, const float size = 0.5f)
			: Alphabet(position, color, size)
		{
			int text[5][5] = {
				{1,0,0,0,0},
				{1,0,0,0,0},
				{1,0,0,0,0},
				{1,0,0,0,0},
				{1,0,0,0,0}
			};
			setText(text);
		}
	};
	class AlphaJ : public Alphabet
	{
	public:
		AlphaJ(const vec2& position, const RGB& color, const float size = 0.5f)
			: Alphabet(position, color, size)
		{
			int text[5][5] = {
				{0,0,0,0,1},
				{0,0,0,0,1},
				{0,0,0,0,1},
				{1,0,0,0,1},
				{0,1,1,1,0}
			};
			setText(text);
		}
	};
	class AlphaK : public Alphabet
	{
	public:
		AlphaK(const vec2& position, const RGB& color, const float size = 0.5f)
			: Alphabet(position, color, size)
		{
			int text[5][5] = {
				{1,0,0,0,1},
				{1,0,0,1,0},
				{1,1,1,0,0},
				{1,0,0,1,0},
				{1,0,0,0,1}
			};
			setText(text);
		}
	};
	class AlphaL : public Alphabet
	{
	public:
		AlphaL(const vec2& position, const RGB& color, const float size = 0.5f)
			: Alphabet(position, color, size)
		{
			int text[5][5] = {
				{1,0,0,0,0},
				{1,0,0,0,0},
				{1,0,0,0,0},
				{1,0,0,0,0},
				{1,1,1,1,1}
			};
			setText(text);
		}
	};
	class AlphaM : public Alphabet
	{
	public:
		AlphaM(const vec2& position, const RGB& color, const float size = 0.5f)
			: Alphabet(position, color, size)
		{
			int text[5][5] = {
				{1,0,0,0,1},
				{1,1,0,1,1},
				{1,0,1,0,1},
				{1,0,0,0,1},
				{1,0,0,0,1}
			};
			setText(text);
		}
	};
	class AlphaN : public Alphabet
	{
	public:
		AlphaN(const vec2& position, const RGB& color, const float size = 0.5f)
			: Alphabet(position, color, size)
		{
			int text[5][5] = {
				{1,0,0,0,1},
				{1,1,0,0,1},
				{1,0,1,0,1},
				{1,0,0,1,1},
				{1,0,0,0,1}
			};
			setText(text);
		}
	};
	class AlphaO : public Alphabet
	{
	public:
		AlphaO(const vec2& position, const RGB& color, const float size = 0.5f)
			: Alphabet(position, color, size)
		{
			int text[5][5] = {
				{0,1,1,1,0},
				{1,0,0,0,1},
				{1,0,0,0,1},
				{1,0,0,0,1},
				{0,1,1,1,0}
			};
			setText(text);
		}
	};
	class AlphaP : public Alphabet
	{
	public:
		AlphaP(const vec2& position, const RGB& color, const float size = 0.5f)
			: Alphabet(position, color, size)
		{
			int text[5][5] = {
				{1,1,1,1,0},
				{1,0,0,0,1},
				{1,0,0,0,1},
				{1,1,1,1,0},
				{1,0,0,0,0}
			};
			setText(text);
		}
	};
	class AlphaQ : public Alphabet
	{
	public:
		AlphaQ(const vec2& position, const RGB& color, const float size = 0.5f)
			: Alphabet(position, color, size)
		{
			int text[5][5] = {
				{0,1,1,1,0},
				{1,0,0,0,1},
				{1,0,0,0,1},
				{1,0,0,1,1},
				{0,1,1,1,1}
			};
			setText(text);
		}
	};
	class AlphaR : public Alphabet
	{
	public:
		AlphaR(const vec2& position, const RGB& color, const float size = 0.5f)
			: Alphabet(position, color, size)
		{
			int text[5][5] = {
				{1,1,1,1,0},
				{1,0,0,0,1},
				{1,0,0,0,1},
				{1,1,1,1,0},
				{1,0,0,0,1}
			};
			setText(text);
		}
	};
	class AlphaS : public Alphabet
	{
	public:
		AlphaS(const vec2& position, const RGB& color, const float size = 0.5f)
			: Alphabet(position, color, size)
		{
			int text[5][5] = {
				{0,1,1,1,1},
				{1,0,0,0,0},
				{0,1,1,1,0},
				{0,0,0,0,1},
				{1,1,1,1,0}
			};
			setText(text);
		}
	};
	class AlphaT : public Alphabet
	{
	public:
		AlphaT(const vec2& position, const RGB& color, const float size = 0.5f)
			: Alphabet(position, color, size)
		{
			int text[5][5] = {
				{1,1,1,1,1},
				{0,0,1,0,0},
				{0,0,1,0,0},
				{0,0,1,0,0},
				{0,0,1,0,0}
			};
			setText(text);
		}
	};
	class AlphaU : public Alphabet
	{
	public:
		AlphaU(const vec2& position, const RGB& color, const float size = 0.5f)
			: Alphabet(position, color, size)
		{
			int text[5][5] = {
				{1,0,0,0,1},
				{1,0,0,0,1},
				{1,0,0,0,1},
				{1,0,0,0,1},
				{0,1,1,1,0}
			};
			setText(text);
		}
	};
	class AlphaV : public Alphabet
	{
	public:
		AlphaV(const vec2& position, const RGB& color, const float size = 0.5f)
			: Alphabet(position, color, size)
		{
			int text[5][5] = {
				{1,0,0,0,1},
				{1,0,0,0,1},
				{1,0,0,0,1},
				{0,1,0,1,0},
				{0,0,1,0,0}
			};
			setText(text);
		}
	};
	class AlphaW : public Alphabet
	{
	public:
		AlphaW(const vec2& position, const RGB& color, const float size = 0.5f)
			: Alphabet(position, color, size)
		{
			int text[5][5] = {
				{1,0,0,0,1},
				{1,0,0,0,1},
				{1,0,1,0,1},
				{1,0,1,0,1},
				{0,1,0,1,0}
			};
			setText(text);
		}
	};
	class AlphaX : public Alphabet
	{
	public:
		AlphaX(const vec2& position, const RGB& color, const float size = 0.5f)
			: Alphabet(position, color, size)
		{
			int text[5][5] = {
				{1,0,0,0,1},
				{0,1,0,1,0},
				{0,0,1,0,0},
				{0,1,0,1,0},
				{1,0,0,0,1}
			};
			setText(text);
		}
	};
	class AlphaY : public Alphabet
	{
	public:
		AlphaY(const vec2& position, const RGB& color, const float size = 0.5f)
			: Alphabet(position, color, size)
		{
			int text[5][5] = {
				{1,0,0,0,1},
				{1,0,0,0,1},
				{0,1,0,1,0},
				{0,0,1,0,0},
				{0,0,1,0,0}
			};
			setText(text);
		}
	};
	class AlphaZ : public Alphabet
	{
	public:
		AlphaZ(const vec2& position, const RGB& color, const float size = 0.5f)
			: Alphabet(position, color, size)
		{
			int text[5][5] = {
				{1,1,1,1,1},
				{0,0,0,1,0},
				{0,0,1,0,0},
				{0,1,0,0,0},
				{1,1,1,1,1}
			};
			setText(text);
		}
	};
}