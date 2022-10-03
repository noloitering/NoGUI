#pragma once

#include <memory>
#include <math.h>
//#include <variant>
//#include <vector>

namespace NoGUI
{
	enum class Wrap {NONE = 0, DOWN = 1, UP = -1, AROUND = 2};
	enum class XAlign {LEFT = -1, CENTER = 0, RIGHT = 1};
	enum class YAlign {TOP = -1, CENTER = 0, BOTTOM = 1};
	
	struct Align
	{
		XAlign x = XAlign::CENTER;
		YAlign y = YAlign::CENTER;
		Align(const XAlign& xalign=XAlign::CENTER, const YAlign& yalign=YAlign::CENTER)
			: x(xalign), y(yalign) {}
		Align(int xint, int yint=-1)
		{
			if ( xint < 0 )
			{
				x = XAlign::LEFT;
			}
			else if ( xint > 0 )
			{
				x = XAlign::RIGHT;
			}
			
			if ( yint < 0 )
			{
				y = YAlign::TOP;
			}
			else if ( yint > 0 )
			{
				y = YAlign::BOTTOM;
			}
		}
	};
	
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
		std::shared_ptr< Fill > fill;
		int thick = 1;
		Wrap border = Wrap::UP; // down = outline into the element, UP = outline outwards from the element, AROUND = outline about center of the element
		Outline(std::shared_ptr< Fill > col, int width=1, const Wrap& style=Wrap::AROUND)
			: fill(col), thick(width), border(style) {}
	};
	
	struct Shadow
	{
		std::shared_ptr< Fill > fill;
		Vector2 offset = {0, 0};
		Shadow(std::shared_ptr< Fill > col, const Vector2& pos)
			: fill(col), offset(pos) {}
	};
	
	struct nShape
	{
		int n = 4;
		std::shared_ptr< Fill > fill;
		std::shared_ptr< Outline > outline;
		nShape(int sides=4, std::shared_ptr< Fill > col=nullptr, std::shared_ptr< Outline > out=nullptr)
			: n(sides), fill(col), outline(out)
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
		Vector2 position;
		Vector2 radius;
		Align origin;
		float angle = 0;
		Transform(const Vector2& p, const Vector2& radi, const Align& a, float r=0)
			: position(p), radius(radi), origin(a), angle(r) {}
		
		Vector2 pos() const
		{
	
			return position;
		}
		
		Vector2 pos(const Align& originPoint) const
		{
			Vector2 ret = position;
			int xdes = static_cast< int >(originPoint.x);
			int ydes = static_cast< int >(originPoint.y);
			
			Vector2 dest = {xdes * radius.x, ydes * radius.y};
			Vector2 curr = offset();
			
			ret.x += dest.x - curr.x;
			ret.y += dest.y - curr.y;

			return ret;
		}
		
		Vector2 size() const
		{
	
			return radius;
		}
		
		Align originPoint() const
		{
	
			return origin;
		}
		
		Vector2 offset() const
		{
			int xint = static_cast< int >(origin.x);
			int yint = static_cast< int >(origin.y);
			
			return {xint * radius.x, yint * radius.y};
		}
		
		float rotation() const
		{
	
			return angle;
		}
		
		Vector2 translate(float x, float y)
		{
			position.x += x;
			position.y += y;
			
			return position;
		}
		
		Vector2 translate(const Vector2 inc)
		{
			position.x += inc.x;
			position.y += inc.y;
			
			return position;
		}
		
		Vector2 repos(Vector2 newPos)
		{
			position = newPos;
	
			return position;
		}
		
		Vector2 repos(Vector2 newPos, const Align& originPoint, bool update=false)
		{
			if ( update )
			{
				origin = originPoint;
			}
			else
			{
				Vector2 translate = pos(originPoint);
				translate.x -= position.x;
				translate.y -= position.y;
				newPos.x -= translate.x;
				newPos.y -= translate.y;
			}
	
			repos(newPos);
	
			return position;
		}
		
		void resize(const Vector2& size)
		{
			radius = size;
		}
		
		void rotate(float degrees, const Align& originPoint, bool update=false)
		{
			if ( origin.x == originPoint.x &&  origin.y == originPoint.y )
			{
				angle += degrees;
			}
			else if ( update )
			{
				origin = originPoint;
				angle += degrees;
			}
			else
			{
				rotate(degrees, pos(originPoint));
			}
		}
		
		void rotate(float degrees, const Vector2& originPoint)
		{
			angle += degrees;
			Vector2 newPos = {position.x - originPoint.x, position.y - originPoint.y};
			Vector2 posInc;
			// calculate values
			float sinRotation = sinf(degrees*DEG2RAD);
			float cosRotation = cosf(degrees*DEG2RAD);
		
			posInc.x = newPos.x * cosRotation - newPos.y * sinRotation;
			posInc.y = newPos.x * sinRotation + newPos.y * cosRotation;				
			// translate back
			position.x = posInc.x + originPoint.x;
			position.y = posInc.y + originPoint.y;
		}
		
		void reorient(float degrees, const Align& originPoint, bool update=false)
		{
			if ( origin.x == originPoint.x && origin.y == originPoint.y )
			{
				angle = degrees;
			}
			else if ( update )
			{
				origin = originPoint;
				angle = degrees;
			}
			else
			{
				reorient(degrees, pos(originPoint));
			}
		}
		
		void reorient(float degrees, const Vector2& originPoint)
		{
			angle = degrees;
			Vector2 temp = {position.x - originPoint.x, position.y - originPoint.y};
			float currAngle;
			if ( temp.x == 0 ) // avoid division by zero
			{
				if ( temp.y < 0)
				{
					currAngle = 270;
				}
				else
				{
					currAngle = 90;
				}
			}
			else if ( temp.y == 0 ) // still avoiding division by zero
			{
				if ( temp.x < 0)
				{
					currAngle = 180;
				}
				else
				{
					currAngle = 0;
				}
			}
			else
			{
				currAngle = asin(temp.y / temp.x) * RAD2DEG;
			}
	
			float theta = degrees - currAngle;
			Vector2 posInc;
			float sinRotation = sinf(theta*DEG2RAD);
			float cosRotation = cosf(theta*DEG2RAD);
	
			// rotation matrix
			posInc.x = temp.x * cosRotation - temp.y * sinRotation;
			posInc.y = temp.x * sinRotation + temp.y * cosRotation;			
			// translate back
			position.x += posInc.x;
			position.y += posInc.y;
		}
	};
}