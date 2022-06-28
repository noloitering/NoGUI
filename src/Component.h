#pragma once

#include <memory>
#include <math.h>
//#include <variant>
//#include <vector>

namespace NoGUI
{
	enum class Wrap {NONE = 0, DOWN = 1, UP = -1, AROUND = 2};
	enum class Align {LEFT, CENTER, RIGHT, TOP, BOTTOM, BOTTOML, BOTTOMR};
	
	struct Fill
	{
		Color col;
		Color hoverCol;
		Fill(Color c, Color hc)
			: col(c), hoverCol(hc) {}
		Fill(Color c)
			: col(c), hoverCol(c) {}
	};
	
	struct Outline
	{
		Fill col;
		int thick = 1;
		Wrap border = Wrap::UP; // down = outline into the element, UP = outline outwards from the element, AROUND = outline about center of the element
	};
	
	struct Shadow
	{
		Fill col = {BLACK, BLACK};
		Vector2 offset = {0, 0};
	};
	
	struct Shape
	{
		int sides = 4;
		std::shared_ptr< Fill > fill;
		std::shared_ptr< Outline > outline;
	};
	
	struct Transform
	{
		Vector2 pos;
		Vector2 radius;
		Align origin = Align::CENTER;
		float angle = 0;
		Transform(const Vector2& position, const Vector2& radi, const Align& align=Align::CENTER, float rotation=0)
			: pos(position), radius(radi), origin(align), angle(rotation) {}
	};
}