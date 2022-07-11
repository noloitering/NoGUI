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
		Fill(Color c=RAYWHITE)
			: col(c), hoverCol(c) {}
	};
	
	struct Outline
	{
		std::shared_ptr< Fill > col;
		int thick = 1;
		Wrap border = Wrap::UP; // down = outline into the element, UP = outline outwards from the element, AROUND = outline about center of the element
		Outline(std::shared_ptr< Fill > fill, int width=1, const Wrap& style=Wrap::UP)
			: col(fill), thick(width), border(style) {}
	};
	
	struct Shadow
	{
		std::shared_ptr< Fill > col;
		Vector2 offset = {0, 0};
		Shadow(std::shared_ptr< Fill > fill, const Vector2& pos)
			: col(fill), offset(pos) {}
	};
	
	struct Shape
	{
		int sides = 4;
		std::shared_ptr< Fill > fill;
		std::shared_ptr< Outline > outline;
		Shape(int n=4, std::shared_ptr< Fill > col=nullptr, std::shared_ptr< Outline > out=nullptr)
			: sides(n), fill(col), outline(out) 
			{
				if ( fill == nullptr )
				{
					fill = std::make_shared< Fill >();
				}
				if ( outline == nullptr )
				{
					outline = std::make_shared< Outline >(fill);
				}
			}
	};
	
	class Transform
	{
	public:
		Vector2 pos;
		Vector2 radius;
		Align origin = Align::CENTER;
		float angle = 0;
		Transform(const Vector2& position, const Vector2& radi, const Align& align=Align::CENTER, float rotation=0)
			: pos(position), radius(radi), origin(align), angle(rotation) {}
	};
}