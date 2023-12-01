#include "GUI.h"

using namespace NoGUI;

void NoGUI::DrawEllipseFill(std::shared_ptr< Fill > fill, Vector2 center, Vector2 radius, Vector2 origin, float angle, bool hovered)
{
	if ( fill )
	{
		if ( hovered )
		{
			DrawEllipsePro(center, radius, origin, angle, fill->hoverCol);
		}
		else
		{
			DrawEllipsePro(center, radius, origin, angle, fill->col);
		}
	}
}	

void NoGUI::DrawEllipseFill(std::shared_ptr< Fill > fill, const Transform& transform, bool hovered)
{
	Vector2 shapeOrigin = {(float)static_cast< int >(transform.origin.x), (float)static_cast< int >(transform.origin.y)};
	shapeOrigin.x *= transform.radius.x;
	shapeOrigin.y *= transform.radius.y;
	DrawEllipseFill(fill, transform.pos(), transform.radius, shapeOrigin, transform.angle, hovered);
}

void NoGUI::DrawPixelFill(std::shared_ptr< Fill > fill, Vector2 pos, bool hovered)
{
	if ( fill )
	{
		if ( hovered )
		{
			DrawPixel(pos.x, pos.y, fill->hoverCol);
		}
		else
		{
			DrawPixel(pos.x, pos.y, fill->col);
		}
	}
}

void NoGUI::DrawPixelFill(std::shared_ptr< Fill > fill, const Transform& transform, bool hovered)
{
	DrawPixelFill(fill, transform.pos(), hovered);
}

void NoGUI::DrawLineFill(std::shared_ptr< Fill > fill, const Vector2& start, const Vector2& end, float thickness, bool hovered)
{
	if ( fill )
	{
		if ( hovered )
		{
			DrawLineEx(start, end, thickness, fill->hoverCol);
		}
		else
		{
			DrawLineEx(start, end, thickness, fill->col);
		}
	}
}

void NoGUI::DrawLineFill(std::shared_ptr< Fill > fill, const Transform& transform, bool hovered)
{
	Vector2 start;
	Vector2 end;
	Vector2 origin = {(float)static_cast< int >(transform.origin.x), (float)static_cast< int >(transform.origin.y)};
	origin.x *= transform.radius.x;
	origin.y *= transform.radius.y;
	Vector2 center = transform.pos();
	if ( transform.angle == 0.0f )
	{
		start = {center.x - transform.radius.x - origin.x, center.y - origin.y / 2};
		end = {center.x + transform.radius.x - origin.x, center.y - origin.y / 2};
	}
	else
	{
		float rads = transform.angle * DEG2RAD;
		// align to origin
		Vector2 leftPos = {-transform.radius.x - origin.x, -origin.y / 2};
		Vector2 rightPos = {transform.radius.x - origin.x, -origin.y / 2};
		// rotate
		start = Vector2Rotate(leftPos, rads);
		end = Vector2Rotate(rightPos, rads);
		// translate back
		start.x += center.x;
		start.y += center.y;
		end.x += center.x;
		end.y += center.y;
	}
	DrawLineFill(fill, start, end, transform.radius.y, hovered);
}

void NoGUI::DrawTriangleFill(std::shared_ptr< Fill > fill, const Vector2& v1, const Vector2& v2, const Vector2& v3, bool hovered)
{
	if ( fill )
	{
		if ( hovered )
		{
			DrawTriangle(v1, v2, v3, fill->hoverCol);
		}
		else
		{
			DrawTriangle(v1, v2, v3, fill->col);
		}
	}
}

void NoGUI::DrawTriangleFill(std::shared_ptr< Fill > fill, const Transform& transform, bool hovered)
{
	Vector2 v1;
	Vector2 v2;
	Vector2 v3;
	Vector2 origin = {(float)static_cast< int >(transform.origin.x), (float)static_cast< int >(transform.origin.y)};
	origin.x *= transform.radius.x;
	origin.y *= transform.radius.y;
	Vector2 center = transform.pos();
	if ( transform.angle == 0 )
	{
		v1 = {center.x - origin.x, center.y - origin.y - transform.radius.y};
		v2 = {center.x - origin.x - transform.radius.x, center.y - origin.y + transform.radius.y};
		v3 = {center.x - origin.x + transform.radius.x, center.y - origin.y + transform.radius.y};
	}
	else
	{
		float rads = transform.angle * DEG2RAD;
		// align to origin
		Vector2 o1 = {-origin.x, -origin.y - transform.radius.y};
		Vector2 o2 = {-origin.x - transform.radius.x, -origin.y + transform.radius.y};
		Vector2 o3 = {-origin.x + transform.radius.x, -origin.y + transform.radius.y};
		// rotate
		Vector2 v1Rotate = Vector2Rotate(o1, rads);
		Vector2 v2Rotate = Vector2Rotate(o2, rads);
		Vector2 v3Rotate = Vector2Rotate(o3, rads);
		// translate back
		v1 = {v1Rotate.x + center.x, v1Rotate.y + center.y};
		v2 = {v2Rotate.x + center.x, v2Rotate.y + center.y};
		v3 = {v3Rotate.x + center.x, v3Rotate.y + center.y};
	}
	DrawTriangleFill(fill, v1, v2, v3, hovered);
}

void NoGUI::DrawRectangleFill(std::shared_ptr< Fill > fill, const Rectangle& rect, const Vector2& origin, float angle, bool hovered)
{
	if ( fill )
	{
		if ( hovered )
		{
			DrawRectanglePro(rect, origin, angle, fill->hoverCol);
		}
		else
		{
			DrawRectanglePro(rect, origin, angle, fill->col);
		}
	}
}

void NoGUI::DrawRectangleFill(std::shared_ptr< Fill > fill, const Transform& transform, bool hovered)
{
	Vector2 origin = {(float)static_cast< int >(transform.origin.x), (float)static_cast< int >(transform.origin.y)};
	origin.x *= transform.radius.x;
	origin.y *= transform.radius.y;
	Vector2 center = transform.pos();
	Rectangle rect = {center.x, center.y, transform.radius.x * 2, transform.radius.y * 2};
	origin.x += transform.radius.x;
	origin.y += transform.radius.y;
	DrawRectangleFill(fill, rect, origin, transform.angle, hovered);
}

void NoGUI::DrawPolyFill(std::shared_ptr< Fill > fill, unsigned int n, const Vector2& center, const Vector2& radius, const Vector2& origin, float angle, bool hovered)
{
	if ( fill )
	{
		if ( hovered )
		{
			DrawPolyPro(center, n, radius, origin, angle, fill->hoverCol);
		}
		else
		{
			DrawPolyPro(center, n, radius, origin, angle, fill->col);
		}
	}
}

void NoGUI::DrawPolyFill(std::shared_ptr< Fill > fill, unsigned int n, const Transform& transform, bool hovered)
{
	Vector2 shapeOrigin = {(float)static_cast< int >(transform.origin.x), (float)static_cast< int >(transform.origin.y)};
	shapeOrigin.x *= transform.radius.x;
	shapeOrigin.y *= transform.radius.y;
	DrawPolyFill(fill, n, transform.pos(), transform.radius, shapeOrigin, transform.angle, hovered);
}

void NoGUI::DrawShapeFill(unsigned int n, std::shared_ptr< Fill > fill, Vector2 center, Vector2 radius, Vector2 origin, float angle, bool hovered)
{
	switch ( n )
	{
		case 0:
		{
			DrawEllipseFill(fill, center, radius, origin, angle, hovered);
			
			break;
		}
		
		case 1:
		{
			if ( fill )
			{
				DrawPixelFill(fill, Vector2Add(center, origin), hovered);
			}
			
			break;
		}
		
		case 2:
		{
			if ( fill )
			{
				Vector2 startPos;
				Vector2 endPos;
				if ( angle == 0.0f )
				{
					startPos = {center.x - radius.x - origin.x, center.y - origin.y / 2};
					endPos = {center.x + radius.x - origin.x, center.y - origin.y / 2};
				}
				else
				{
					float rads = angle * DEG2RAD;
					// align to origin
					Vector2 leftPos = {-radius.x - origin.x, -origin.y / 2};
					Vector2 rightPos = {radius.x - origin.x, -origin.y / 2};
					// rotate
					startPos = Vector2Rotate(leftPos, rads);
					endPos = Vector2Rotate(rightPos, rads);
					// translate back
					startPos.x += center.x;
					startPos.y += center.y;
					endPos.x += center.x;
					endPos.y += center.y;
				}
				DrawLineFill(fill, startPos, endPos, radius.y, hovered);
			}
			
			break;
		}
		
		case 3:
		{	
			if ( fill )
			{
				Vector2 v1;
				Vector2 v2;
				Vector2 v3;
				if ( angle == 0 )
				{
					v1 = {center.x - origin.x, center.y - origin.y - radius.y};
					v2 = {center.x - origin.x - radius.x, center.y - origin.y + radius.y};
					v3 = {center.x - origin.x + radius.x, center.y - origin.y + radius.y};
				}
				else
				{
					float rads = angle * DEG2RAD;
					// align to origin
					Vector2 o1 = {-origin.x, -origin.y - radius.y};
					Vector2 o2 = {-origin.x - radius.x, -origin.y + radius.y};
					Vector2 o3 = {-origin.x + radius.x, -origin.y + radius.y};
					// rotate
					Vector2 v1Rotate = Vector2Rotate(o1, rads);
					Vector2 v2Rotate = Vector2Rotate(o2, rads);
					Vector2 v3Rotate = Vector2Rotate(o3, rads);
					// translate back
					v1 = {v1Rotate.x + center.x, v1Rotate.y + center.y};
					v2 = {v2Rotate.x + center.x, v2Rotate.y + center.y};
					v3 = {v3Rotate.x + center.x, v3Rotate.y + center.y};
				}
				DrawTriangleFill(fill, v1, v2, v3, hovered);
			}
			
			break;
		}
		
		case 4:
		{
			if ( fill )
			{
				Rectangle rect = {center.x, center.y, radius.x * 2, radius.y * 2};
				origin.x += radius.x;
				origin.y += radius.y;
				DrawRectangleFill(fill, rect, origin, angle, hovered);
			}
			
			break;
		}
		
		default:
		{
			DrawPolyFill(fill, n, center, radius, origin, angle, hovered);
			
			break;
		}
	}
}

void NoGUI::DrawShapeFill(unsigned int n, std::shared_ptr< NoGUI::Fill > fill, const NoGUI::Transform& transform, bool hovered)
{
	Vector2 shapeOrigin = {(float)static_cast< int >(transform.origin.x), (float)static_cast< int >(transform.origin.y)};
	shapeOrigin.x *= transform.radius.x;
	shapeOrigin.y *= transform.radius.y;
	DrawShapeFill(n, fill, transform.pos(), transform.radius, shapeOrigin, transform.angle, hovered);
}

void NoGUI::DrawEllipseOutline(std::shared_ptr< Outline > outline, Vector2 center, Vector2 radius, Vector2 origin, float angle, bool hovered)
{
	if ( outline )
	{
		if ( outline->fill )
		{
			if ( hovered )
			{
				DrawEllipseLinesPro(center, radius, origin, angle, outline->thick, outline->fill->hoverCol);
			}
			else
			{
				DrawEllipseLinesPro(center, radius, origin, angle, outline->thick, outline->fill->col);
			}
		}
	}
}

void NoGUI::DrawEllipseOutline(std::shared_ptr< Outline > outline, const Transform& transform, bool hovered)
{
	Vector2 shapeOrigin = {(float)static_cast< int >(transform.origin.x), (float)static_cast< int >(transform.origin.y)};
	shapeOrigin.x *= transform.radius.x;
	shapeOrigin.y *= transform.radius.y;
	DrawEllipseOutline(outline, transform.pos(), transform.radius, shapeOrigin, transform.angle, hovered);
}

void NoGUI::DrawTriangleOutline(std::shared_ptr< Outline > outline, const Vector2& v1, const Vector2& v2, const Vector2& v3, bool hovered)
{
	if ( outline )
	{
		if ( outline->fill )
		{
			if ( hovered )
			{
				DrawTriangleLinesEx(v1, v2, v3, outline->thick, outline->fill->hoverCol);
			}
			else
			{
				DrawTriangleLinesEx(v1, v2, v3, outline->thick, outline->fill->col);
			}
		}
	}
}

void NoGUI::DrawTriangleOutline(std::shared_ptr< Outline > outline, const Transform& transform, bool hovered)
{
	Vector2 v1;
	Vector2 v2;
	Vector2 v3;
	Vector2 origin = {(float)static_cast< int >(transform.origin.x), (float)static_cast< int >(transform.origin.y)};
	origin.x *= transform.radius.x;
	origin.y *= transform.radius.y;
	Vector2 center = transform.pos();
	if ( transform.angle == 0 )
	{
		v1 = {center.x - origin.x, center.y - origin.y - transform.radius.y};
		v2 = {center.x - origin.x - transform.radius.x, center.y - origin.y + transform.radius.y};
		v3 = {center.x - origin.x + transform.radius.x, center.y - origin.y + transform.radius.y};
	}
	else
	{
		float rads = transform.angle * DEG2RAD;
		// align to origin
		Vector2 o1 = {-origin.x, -origin.y - transform.radius.y};
		Vector2 o2 = {-origin.x - transform.radius.x, -origin.y + transform.radius.y};
		Vector2 o3 = {-origin.x + transform.radius.x, -origin.y + transform.radius.y};
		// rotate
		Vector2 v1Rotate = Vector2Rotate(o1, rads);
		Vector2 v2Rotate = Vector2Rotate(o2, rads);
		Vector2 v3Rotate = Vector2Rotate(o3, rads);
		// translate back
		v1 = {v1Rotate.x + center.x, v1Rotate.y + center.y};
		v2 = {v2Rotate.x + center.x, v2Rotate.y + center.y};
		v3 = {v3Rotate.x + center.x, v3Rotate.y + center.y};
	}
	DrawTriangleOutline(outline, v1, v2, v3, hovered);
}

void NoGUI::DrawRectangleOutline(std::shared_ptr< Outline > outline, const Rectangle& rect, const Vector2& origin, float angle, bool hovered)
{
	if ( outline )
	{
		if ( outline->fill )
		{
			if ( hovered )
			{
				DrawRectangleLinesPro(rect, origin, angle, outline->thick, outline->fill->hoverCol);
			}
			else
			{
				DrawRectangleLinesPro(rect, origin, angle, outline->thick, outline->fill->col);
			}
		}
	}
}

void NoGUI::DrawRectangleOutline(std::shared_ptr< Outline > outline, const Transform& transform, bool hovered)
{
	Vector2 origin = {(float)static_cast< int >(transform.origin.x), (float)static_cast< int >(transform.origin.y)};
	origin.x *= transform.radius.x;
	origin.y *= transform.radius.y;
	Vector2 center = transform.pos();
	Rectangle rect = {center.x, center.y, transform.radius.x * 2, transform.radius.y * 2};
	origin.x += transform.radius.x;
	origin.y += transform.radius.y;
	DrawRectangleOutline(outline, rect, origin, transform.angle, hovered);
}

void NoGUI::DrawPolyOutline(std::shared_ptr< Outline > outline, unsigned int n, const Vector2& center, const Vector2& radius, const Vector2& origin, float angle, bool hovered)
{
	if ( outline )
	{
		if ( outline->fill )
		{
			if ( hovered )
			{
				DrawPolyLinesPro(center, n, radius, origin, angle, outline->thick, outline->fill->hoverCol);
			}
			else
			{
				DrawPolyLinesPro(center, n, radius, origin, angle, outline->thick, outline->fill->col);
			}
		}
	}
}
	
void NoGUI::DrawPolyOutline(std::shared_ptr< Outline > outline, unsigned int n, const Transform& transform, bool hovered)
{
	Vector2 shapeOrigin = {(float)static_cast< int >(transform.origin.x), (float)static_cast< int >(transform.origin.y)};
	shapeOrigin.x *= transform.radius.x;
	shapeOrigin.y *= transform.radius.y;
	DrawPolyOutline(outline, n, transform.pos(), transform.radius, shapeOrigin, transform.angle, hovered);
}

void NoGUI::DrawShapeOutline(unsigned int n, std::shared_ptr< Outline > outline, Vector2 center, Vector2 radius, Vector2 origin, float angle, bool hovered)
{
	switch (n)
	{
		case 0:
		{
			if ( outline->fill )
			{
				if ( hovered )
				{
					DrawEllipseLinesPro(center, radius, origin, angle, outline->thick, outline->fill->hoverCol);
				}
				else
				{
					DrawEllipseLinesPro(center, radius, origin, angle, outline->thick, outline->fill->col);
				}
			}
			
			break;
		}
		
		case 1:
		{
			// TODO: stuff here
			
			break;
		}
		
		case 2:
		{
			
			break;
		}
		
		case 3:
		{
			if ( outline->fill )
			{
				Vector2 v1;
				Vector2 v2;
				Vector2 v3;
				if ( angle == 0 )
				{
					v1 = {center.x - origin.x, center.y - origin.y - radius.y};
					v2 = {center.x - origin.x - radius.x, center.y - origin.y + radius.y};
					v3 = {center.x - origin.x + radius.x, center.y - origin.y + radius.y};
				}
				else
				{
					float rads = angle * DEG2RAD;
					// align to origin
					Vector2 o1 = {-origin.x, -origin.y - radius.y};
					Vector2 o2 = {-origin.x - radius.x, -origin.y + radius.y};
					Vector2 o3 = {-origin.x + radius.x, -origin.y + radius.y};
					// rotate
					Vector2 v1Rotate = Vector2Rotate(o1, rads);
					Vector2 v2Rotate = Vector2Rotate(o2, rads);
					Vector2 v3Rotate = Vector2Rotate(o3, rads);
					// translate back
					v1 = {v1Rotate.x + center.x, v1Rotate.y + center.y};
					v2 = {v2Rotate.x + center.x, v2Rotate.y + center.y};
					v3 = {v3Rotate.x + center.x, v3Rotate.y + center.y};
				}
				if ( hovered )
				{
					DrawTriangleLinesEx(v1, v2, v3, outline->thick, outline->fill->hoverCol);
				}
				else
				{
					DrawTriangleLinesEx(v1, v2, v3, outline->thick, outline->fill->col);
				}
			}
			
			break;
		}
		
		case 4:
		{	
			if ( outline->fill )
			{
				Rectangle rect = {center.x, center.y, radius.x * 2, radius.y * 2};
				origin.x += radius.x;
				origin.y += radius.y;
				if ( hovered )
				{
					DrawRectangleLinesPro(rect, origin, angle, outline->thick, outline->fill->hoverCol);
				}
				else
				{
					DrawRectangleLinesPro(rect, origin, angle, outline->thick, outline->fill->col);
				}
			}
			
			break;
		}
		
		default:
		{
			if ( outline->fill )
			{
				if ( hovered )
				{
					DrawPolyLinesPro(center, n, radius, origin, angle, outline->thick, outline->fill->hoverCol);
				}
				else
				{
					DrawPolyLinesPro(center, n, radius, origin, angle, outline->thick, outline->fill->col);
				}
			}
			
			break;
		}
	}
}

void NoGUI::DrawShapeOutline(unsigned int n, std::shared_ptr< Outline > outline, const Transform& transform, bool hovered)
{
	Vector2 shapeOrigin = {(float)static_cast< int >(transform.origin.x), (float)static_cast< int >(transform.origin.y)};
	shapeOrigin.x *= transform.radius.x;
	shapeOrigin.y *= transform.radius.y;
	DrawShapeOutline(n, outline, transform.pos(), transform.radius, shapeOrigin, transform.angle, hovered);
}

void NoGUI::DrawShape(const nShape& shape, Vector2 center, Vector2 radius, Vector2 origin, float angle, bool hovered)
{
	switch (shape.n)
	{
		case 0:
		{
			DrawEllipseFill(shape.fill, center, radius, origin, angle, hovered);
			DrawEllipseOutline(shape.outline, center, radius, origin, angle, hovered);
			
			break;
		}
		
		case 1:
		{
			DrawPixelFill(shape.fill, Vector2Add(center, origin), hovered);
			
			break;
		}
		
		case 2:
		{
			Vector2 startPos;
			Vector2 endPos;
			if ( angle == 0.0f )
			{
				startPos = {center.x - radius.x - origin.x, center.y - origin.y / 2};
				endPos = {center.x + radius.x - origin.x, center.y - origin.y / 2};
			}
			else
			{
				float rads = angle * DEG2RAD;
				// align to origin
				Vector2 leftPos = {-radius.x - origin.x, -origin.y / 2};
				Vector2 rightPos = {radius.x - origin.x, -origin.y / 2};
				// rotate
				startPos = Vector2Rotate(leftPos, rads);
				endPos = Vector2Rotate(rightPos, rads);
				// translate back
				startPos.x += center.x;
				startPos.y += center.y;
				endPos.x += center.x;
				endPos.y += center.y;
			}
			DrawLineFill(shape.fill, startPos, endPos, radius.y, hovered);
			
			break;
		}
		
		case 3:
		{
			Vector2 v1;
			Vector2 v2;
			Vector2 v3;
			if ( angle == 0 )
			{
				v1 = {center.x - origin.x, center.y - origin.y - radius.y};
				v2 = {center.x - origin.x - radius.x, center.y - origin.y + radius.y};
				v3 = {center.x - origin.x + radius.x, center.y - origin.y + radius.y};
			}
			else
			{
				float rads = angle * DEG2RAD;
				// align to origin
				Vector2 o1 = {-origin.x, -origin.y - radius.y};
				Vector2 o2 = {-origin.x - radius.x, -origin.y + radius.y};
				Vector2 o3 = {-origin.x + radius.x, -origin.y + radius.y};
				// rotate
				Vector2 v1Rotate = Vector2Rotate(o1, rads);
				Vector2 v2Rotate = Vector2Rotate(o2, rads);
				Vector2 v3Rotate = Vector2Rotate(o3, rads);
				// translate back
				v1 = {v1Rotate.x + center.x, v1Rotate.y + center.y};
				v2 = {v2Rotate.x + center.x, v2Rotate.y + center.y};
				v3 = {v3Rotate.x + center.x, v3Rotate.y + center.y};
			}
			DrawTriangleFill(shape.fill, v1, v2, v3, hovered);
			DrawTriangleOutline(shape.outline, v1, v2, v3, hovered);
			
			break;
		}
		
		case 4:
		{
			Rectangle rect = {center.x, center.y, radius.x * 2, radius.y * 2};
			origin.x += radius.x;
			origin.y += radius.y;
			DrawRectangleFill(shape.fill, rect, origin, angle, hovered);
			DrawRectangleOutline(shape.outline, rect, origin, angle, hovered);
			
			break;
		}
		
		default:
		{
			DrawPolyFill(shape.fill, shape.n, center, radius, origin, angle, hovered);
			DrawPolyOutline(shape.outline, shape.n, center, radius, origin, angle, hovered);
			
			break;
		}
	}
}

void NoGUI::DrawShape(const nShape& shape, const NoGUI::Transform& transform, bool hovered)
{
	Vector2 shapeOrigin = {(float)static_cast< int >(transform.origin.x), (float)static_cast< int >(transform.origin.y)};
	shapeOrigin.x *= transform.radius.x;
	shapeOrigin.y *= transform.radius.y;
	
	DrawShape(shape, transform.pos(), transform.radius, shapeOrigin, transform.rotation(), hovered);
}

void NoGUI::DrawScrollBars(std::shared_ptr< nShape > bar, std::shared_ptr< nShape > cursor, const Transform& transform, const Vector2& scrollPos, const Vector2& percentShown, float size)
{
	std::shared_ptr< NoGUI::Fill > defaultBarFill = std::make_shared< NoGUI::Fill >(LIGHTGRAY);
	std::shared_ptr< NoGUI::Fill > defaultCursorFill = std::make_shared< NoGUI::Fill >(BLUE);
	std::shared_ptr< NoGUI::Fill > defaultLinesFill = std::make_shared< NoGUI::Fill >(BLACK);
	std::shared_ptr< NoGUI::Outline > defaultLines = std::make_shared< NoGUI::Outline >(defaultLinesFill, 1);
	if ( bar == nullptr )
	{
		bar = std::make_shared< NoGUI::nShape >(4, defaultBarFill, defaultLines);
	}
	else
	{
		if ( bar->fill == nullptr )
		{
			bar->fill = defaultBarFill;
		}
		if ( bar->outline == nullptr )
		{
			bar->outline = defaultLines;	
		}
	}
	if ( cursor == nullptr )
	{
		cursor = std::make_shared< NoGUI::nShape >(4, defaultCursorFill, defaultLines);
	}
	else
	{
		if ( cursor->fill == nullptr )
		{
			cursor->fill = defaultCursorFill;
		}
		if ( cursor->outline == nullptr )
		{
			cursor->outline = defaultLines;	
		}
	}
	
	float sin = 0.0f;
	float cos = 1.0f;
	if ( transform.angle )
	{
		sin = sinf(transform.angle * DEG2RAD);
		cos = cosf(transform.angle * DEG2RAD);
	}
	if ( percentShown.y < 1.0f )
	{
		float percentCropped = 1.0f - percentShown.y;
		Vector2 scrollBarPos = transform.pos(NoGUI::Align(1, 0));
		scrollBarPos.x -= size * cos;
		scrollBarPos.y -= size * sin;
		Vector2 scrollCursorPos = {scrollBarPos.x, scrollBarPos.y};
		float scrollLength = (scrollPos.y - 0.5) * percentCropped * transform.size().y;
		scrollCursorPos.x -= scrollLength * sin;
		scrollCursorPos.y += scrollLength * cos;
		float scrollCursorSize = percentShown.y * transform.size().y;
		
		DrawShape(*(bar), scrollBarPos, (Vector2){size, transform.radius.y}, (Vector2){0, 0}, transform.angle);
		DrawShape(*(cursor), scrollCursorPos, (Vector2){size, scrollCursorSize / 2}, (Vector2){0, 0}, transform.angle);
	}
	if ( percentShown.x < 1.0f )
	{
		float percentCropped = 1.0f - percentShown.x;
		Vector2 scrollBarPos = transform.pos(NoGUI::Align(0, 1));
		scrollBarPos.y -= size * cos;
		scrollBarPos.x += size * sin;
		Vector2 scrollCursorPos = {scrollBarPos.x, scrollBarPos.y};
		float scrollLength = (scrollPos.x - 0.5) * percentCropped * transform.size().x;
		scrollCursorPos.x += scrollLength * cos;
		scrollCursorPos.y += scrollLength * sin;
		float scrollCursorSize = percentShown.x * transform.size().x;
		
		DrawShape(*(bar), scrollBarPos, (Vector2){transform.radius.x, size}, (Vector2){0, 0}, transform.angle);
		DrawShape(*(cursor), scrollCursorPos, (Vector2){scrollCursorSize / 2, size}, (Vector2){0, 0}, transform.angle);
	}
}

std::vector< std::tuple< const char*, float, unsigned int > > NoGUI::WrapText(const char* txt, const Font& font, float fontSize, float spacing, const NoGUI::Transform& area)
{
	float scaleFactor = fontSize / (float)font.baseSize; // for calculating char size
	int counter = 0;
	unsigned int charCount = 0;
	unsigned int lastWord = 0;
	unsigned int bi = 0; // buffer index
	float lineWidth = 0;
	
	// clear static buffer
	static char buffer[NoMAD::INBUFF] = { 0 };
	memset(buffer, 0, NoMAD::INBUFF);
	// initialize result
	std::vector< std::tuple< const char*, float, unsigned int > > lines;
	lines.push_back(std::make_tuple(buffer, lineWidth, charCount));
	
	if (txt != NULL)
    {
		counter = 1;
        for (size_t i = 0; bi < NoMAD::INBUFF; i++)
        {
			buffer[bi] = txt[i];
			if (buffer[bi] == '\0')
			{	
				
				break;
			}
			charCount++;
			int codepointByteCount = 0;
			int codepoint = GetCodepoint(&txt[i], &codepointByteCount);
			int index = GetGlyphIndex(font, codepoint);
			float glyphWidth = 0;
			
			if ((codepoint == ' ') || (codepoint == '\t') || (codepoint == '\n')) 
			{
				lastWord = bi;
			}
			
			if (codepoint != '\n')
			{
				glyphWidth = (font.glyphs[index].advanceX == 0) ? font.recs[index].width*scaleFactor : font.glyphs[index].advanceX*scaleFactor;
 				lineWidth += glyphWidth + spacing;
				
				if (lineWidth - spacing > area.width())
				{
					if ( buffer[lastWord] == ' ' || buffer[lastWord] == '\t' || buffer[lastWord] == '\n' )
					{
						// replace space char with terminating char
						buffer[lastWord] = '\0';
						// recalculate lineWidth and move index back
						while ( bi != lastWord )
						{
							lineWidth -= (glyphWidth + spacing);
							i--;
							bi--;
							charCount--;
							codepointByteCount = 0;
							codepoint = GetCodepoint(&txt[i], &codepointByteCount);
							index = GetGlyphIndex(font, codepoint);
							glyphWidth = (font.glyphs[index].advanceX == 0) ? font.recs[index].width*scaleFactor : font.glyphs[index].advanceX*scaleFactor;
						}
						charCount--;
						codepoint = GetCodepoint(&txt[i], &codepointByteCount);
						index = GetGlyphIndex(font, codepoint);
						glyphWidth = (font.glyphs[index].advanceX == 0) ? font.recs[index].width*scaleFactor : font.glyphs[index].advanceX*scaleFactor;
						lineWidth -= glyphWidth + spacing * 2;
						// input new line width
						std::get< float >(lines.at(counter - 1)) = lineWidth;
						// input new char count
						std::get< unsigned int >(lines.at(counter - 1)) = charCount;
						// add next line to result
						lineWidth = 0.0f;
						charCount = 0;
						lines.push_back(std::make_tuple(buffer + bi + 1, lineWidth, charCount));
					}
					else
					{
						// replace current char with terminating character
						buffer[bi] = '\0';
						lineWidth -= (glyphWidth + spacing * 2);
						charCount--;
						// input current line width
						std::get< float >(lines.at(counter - 1)) = lineWidth;
						// input current char count
						std::get< unsigned int >(lines.at(counter - 1)) = charCount;
						// add next line to result
						lines.push_back(std::make_tuple(buffer + bi + 1, 0.0f, 0));
						//  increment char position and swap back terminated character into the buffer
						if ( bi + 1 < NoMAD::INBUFF )
						{
							bi++; // WARNING: DANGEROUS OPERATION! CAN OVERFLOW PAST NoMAD::INBUFF
							buffer[bi] = txt[i];
							lineWidth = glyphWidth + spacing;
							charCount = 1;
						}
					}
					counter++;
				}
			}
			else
			{
				// replace newline char with terminating char 
				buffer[lastWord] = '\0';
				// input current line width
				std::get< float >(lines.at(counter - 1)) = lineWidth - spacing;
				// input current char count
				std::get< unsigned int >(lines.at(counter - 1)) = charCount - 1;
				// add next line to result and increment counter
				lineWidth = 0.0f;
				charCount = 0;
				lines.push_back(std::make_tuple(buffer + bi + 1, lineWidth, charCount));
				counter++;
			}
			bi++;
		}
		const char* lastLine = std::get< const char* >(lines.back());
		// TODO: the last line will be iterated 3 times here. This can be optimized
		std::get< float >(lines.back()) = MeasureTextEx(font, lastLine, fontSize, spacing).x;
		std::get< unsigned int >(lines.back()) = TextLength(lastLine);
	}
	
	return lines;
}

std::vector< std::tuple< const char*, float, unsigned int > > NoGUI::WrapText(const char* txt, const CText& fmt, const NoGUI::Transform& area)
{
	Font font = fmt.font ? *(fmt.font) : GetFontDefault();
	
	return WrapText(txt, font, fmt.size, fmt.spacing.x, area);
}

Vector2 NoGUI::AlignText(const NoGUI::Align& alignment, const NoGUI::Wrap& wrap, Vector2 lineSize, int lineNum, int numLines, float lineSpacing)
{
	Vector2 origin = {0, 0};
	switch ( alignment.x )
	{
		case NoGUI::XAlign::LEFT:
		{
			origin.x = 0.0f;
			
			break;
		}
		case NoGUI::XAlign::CENTER:
		{
			origin.x = lineSize.x / 2.0f;
			
			break;
		}
		
		case NoGUI::XAlign::RIGHT:
		{
			origin.x = lineSize.x;
			
			break;
		}
	}
	switch ( alignment.y )
	{
		case NoGUI::YAlign::TOP:
		{
			origin.y = 0 - (lineSize.y + lineSpacing) * lineNum * static_cast< int >(wrap);
			
			break;
		}
		
		case NoGUI::YAlign::CENTER:
		{
			if ( wrap == Wrap::UP )
			{
				// correct for first line, and then subtract subsequent lines
				float halfSize = lineSize.y / 2.0f;
				origin.y = halfSize - (halfSize + lineSpacing) * (numLines - 1) - (lineSize.y + lineSpacing) * lineNum * static_cast< int >(wrap);
			}
			else
			{
				// shift origin half of the total size of text
				origin.y = (lineSize.y * numLines + lineSpacing * (numLines - 1)) / 2 - (lineSize.y + lineSpacing) * lineNum * static_cast< int >(wrap);
			}
			
			break;
		}
		
		case NoGUI::YAlign::BOTTOM:
		{
			origin.y = lineSize.y * numLines - (lineSize.y + lineSpacing) * lineNum * static_cast< int >(wrap); // shift origin 1 line size above position
			
			break;
		}
	}
	
	return origin;
}

Vector2 NoGUI::AlignText(const NoGUI::CText& fmt, Vector2 lineSize, int lineNum, int numLines)
{
	
	return AlignText(fmt.align, fmt.wrap, lineSize, lineNum, numLines, fmt.spacing.y);
}

void NoGUI::collectInput(Element* elem)
{
	CInput& input = elem->components->getComponent< CInput >();
	char buffer[input.cap];
	TextCopy(buffer, elem->getInner());
	input.i = TextLength(buffer);
	if ( input.i < input.cap )
	{
		int key = GetCharPressed();
		while ( key > 0 )
		{
			// only allow good inputs
			if ( (key >= 32) && (key <= 125) && input.i < input.cap )
			{
				buffer[input.i] = (char)key;
				buffer[input.i + 1] = '\0';
				input.i++;
			}
			key = GetCharPressed();
		}
	}
	if ( IsKeyPressed(KEY_BACKSPACE) )
    {
		if ( input.i > 0 )
		{
			input.i--;
		}
		buffer[input.i] = '\0';
	}
	
	elem->setInner(buffer);
}

// TODO: optimize case 3, and 4. transform.pos() will call sinf and cosf each time. Find a better way to determine these points
bool NoGUI::CheckCollisionPointShape(Vector2 point, int sides, const NoGUI::Transform& area)
{
	bool collision = false;
	
	switch ( sides )
	{
		case 0:
		{
			Vector2 center = area.pos(NoGUI::Align(0, 0));
			if ( area.angle == 0 )
			{
				collision = CheckCollisionPointEllipse(point, center, area.radius);
			}
			else
			{
				float sin = sinf(area.angle * DEG2RAD);
				float cos = cosf(area.angle * DEG2RAD);
				float xval = (point.x - center.x) * cos + (point.y - center.y) * sin;
				xval = xval * xval * (area.radius.y * area.radius.y);
				float yval = (point.x - center.x) * sin - (point.y - center.y) * cos;
				yval = yval * yval * (area.radius.x * area.radius.x);

				collision = (xval + yval) <= ((area.radius.x * area.radius.x) * (area.radius.y * area.radius.y));
			}
			
			break;
		}
		
		case 1:
		{
			collision = point.x == area.position.x && point.y == area.position.y;
			
			break;
		}
		
		case 2:
		{
			Vector2 origin = {(float)static_cast< int >(area.origin.x), (float)static_cast< int >(area.origin.y)};
			float halfHeight = area.radius.y / 2;
			origin.x *= area.radius.x;
			origin.y *= halfHeight;
			
			if ( area.angle == 0 )
			{
				Vector2 startPos = {area.position.x - area.radius.x - origin.x, area.position.y - origin.y};
				Vector2 endPos = {area.position.x + area.radius.x - origin.x, area.position.y - origin.y};
				
				collision = CheckCollisionPointLine(point, startPos, endPos, halfHeight);
			}
			else // treat as rectangle
			{
				// align to origin
				Vector2 topLeft = {-area.radius.x - origin.x, -area.radius.y / 2 - origin.y};
				Vector2 bottomLeft = {-area.radius.x - origin.x, area.radius.y / 2 - origin.y};
				Vector2 bottomRight = {area.radius.x - origin.x, area.radius.y / 2 - origin.y};
				Vector2 topRight = {area.radius.x - origin.x, -area.radius.y / 2 - origin.y};
				// rotate
				float rads = area.angle * DEG2RAD;
				topLeft = Vector2Rotate(topLeft, rads);
				bottomLeft = Vector2Rotate(bottomLeft, rads);
				bottomRight = Vector2Rotate(bottomRight, rads);
				topRight = Vector2Rotate(topRight, rads);
				// translate back
				topLeft = Vector2Add(area.position, topLeft);
				bottomLeft = Vector2Add(area.position, bottomLeft);
				bottomRight = Vector2Add(area.position, bottomRight);
				topRight = Vector2Add(area.position, topRight);
				
				float isLeft1 = (bottomLeft.x - topLeft.x) * (point.y - topLeft.y) - (point.x - topLeft.x) * (bottomLeft.y - topLeft.y);
				float isLeft2 = (bottomRight.x - bottomLeft.x) * (point.y - bottomLeft.y) - (point.x - bottomLeft.x) * (bottomRight.y - bottomLeft.y);
				float isLeft3 = (topRight.x - bottomRight.x) * (point.y - bottomRight.y) - (point.x - bottomRight.x) * (topRight.y - bottomRight.y);
				float isLeft4 = (topLeft.x - topRight.x) * (point.y - topRight.y) - (point.x - topRight.x) * (topLeft.y - topRight.y);
		
				collision = isLeft1 < 0 && isLeft2 < 0 && isLeft3 < 0 && isLeft4 < 0;
			}
			
			break;
		}
		
		case 3:
		{
			Vector2 p1 = area.pos(NoGUI::Align(-1, 1));
			Vector2 p2 = area.pos(NoGUI::Align(0, -1));
			Vector2 p3 = area.pos(NoGUI::Align(1, 1));
			
			collision = CheckCollisionPointTriangle(point, p1, p2, p3);
			
			break;
		}
		
		case 4:
		{
			Vector2 topLeft = area.pos(NoGUI::Align(-1, -1));
			
			if ( area.angle == 0 )
			{
				Rectangle collider = {topLeft.x, topLeft.y, area.width(), area.height()};

				collision = CheckCollisionPointRec(point, collider);
			}
			else
			{
				Vector2 bottomLeft = area.pos(NoGUI::Align(-1, 1));
				Vector2 bottomRight = area.pos(NoGUI::Align(1, 1));
				Vector2 topRight = area.pos(NoGUI::Align(1, -1));
		
				float isLeft1 = (bottomLeft.x - topLeft.x) * (point.y - topLeft.y) - (point.x - topLeft.x) * (bottomLeft.y - topLeft.y);
				float isLeft2 = (bottomRight.x - bottomLeft.x) * (point.y - bottomLeft.y) - (point.x - bottomLeft.x) * (bottomRight.y - bottomLeft.y);
				float isLeft3 = (topRight.x - bottomRight.x) * (point.y - bottomRight.y) - (point.x - bottomRight.x) * (topRight.y - bottomRight.y);
				float isLeft4 = (topLeft.x - topRight.x) * (point.y - topRight.y) - (point.x - topRight.x) * (topLeft.y - topRight.y);
		
				collision = isLeft1 < 0 && isLeft2 < 0 && isLeft3 < 0 && isLeft4 < 0;
			}
			
			break;
		}
		
		default:
		{
			Vector2 center = area.pos(NoGUI::Align(0, 0));
			if ( area.angle == 0 )
			{
				collision = CheckCollisionPointEllipse(point, area.pos(NoGUI::Align(0, 0)), area.radius);
			}
			else
			{
				float sin = sinf(area.angle * DEG2RAD);
				float cos = cosf(area.angle * DEG2RAD);
				float xval = (point.x - center.x) * cos + (point.y - center.y) * sin;
				xval = xval * xval * (area.radius.y * area.radius.y);
				float yval = (point.x - center.x) * sin - (point.y - center.y) * cos;
				yval = yval * yval * (area.radius.x * area.radius.x);

				collision = (xval + yval) <= ((area.radius.x * area.radius.x) * (area.radius.y * area.radius.y));
			}
			
			break;
		}
	}
	
	return collision;
}

void NoGUI::DrawCText(const char* txt, CText& fmt, const NoGUI::Transform& transform)
{
	Font font = fmt.font ? *(fmt.font) : GetFontDefault();
	Color col = fmt.fill ? fmt.fill->col : WHITE;
	// text rotates around it's position, not the origin funny enough
	Vector2 pos = transform.pos(fmt.align);
	// adjust origin to reposition text while having each line rotate around the same point
	Vector2 origin = { 0 };
	int numLines = 0;
	const char **lines = TextSplit(txt, '\n', &numLines);
	for (int li=0; li < numLines; li++)
	{
		if ( fmt.align.y == YAlign::BOTTOM )
		{
			// hack to position only the first line to the bottom of the element, and allow the remaining lines to flow past the transform
			origin = AlignText(fmt.align, fmt.wrap, MeasureTextEx(font, lines[li], fmt.size, fmt.spacing.x), li, 1, fmt.spacing.y);
		}
		else
		{
			origin = AlignText(fmt.align, fmt.wrap, MeasureTextEx(font, lines[li], fmt.size, fmt.spacing.x), li, numLines, fmt.spacing.y);
		}
		DrawTextPro(font, lines[li], pos, origin, fmt.angle, fmt.size, fmt.spacing.x, col); // draw line
	}
}

void NoGUI::DrawCTextBoxWrapped(const char* txt, CTextBox& fmt, const NoGUI::Transform& transform)
{
	Font font = fmt.font ? *(fmt.font) : GetFontDefault();
	Color col = fmt.fill ? fmt.fill->col : WHITE;
	std::vector< std::tuple< const char*, float, unsigned int > > lines = WrapText(txt, font, fmt.size, fmt.spacing.x, transform);
	float scaleFactor = fmt.size / (float)font.baseSize; // for calculating char size
	float totalHeight = fmt.size * lines.size() + fmt.spacing.y * (lines.size() - 1);
	float maxScroll = totalHeight - transform.height();
	float lineOffset = 0.0f; // for partial lines when scrolling
	bool scrollBars = totalHeight > transform.height();
	unsigned int lineIndex = 0; // current line to draw
	int lineNum = 0; // number of lines drawn
	Vector2 charPos = transform.pos(fmt.align); // keep track of character positioning
	Vector2 charAlign = AlignText(fmt.align, NoGUI::Wrap::DOWN, (Vector2){std::get< float >(lines.front()), fmt.size}, lineNum, (int)lines.size(), fmt.spacing.y); // for aligning text
	charPos.x -= charAlign.x;
	if ( scrollBars ) // find which line to start on
	{
		charPos.y = transform.pos(NoGUI::Align(-1, -1)).y; // align to top
		if ( fmt.scrollAmount.y > maxScroll )
		{
			fmt.scrollAmount.y = maxScroll;
		}
		if ( fmt.scrollAmount.y < 0 )
		{
			fmt.scrollAmount.y = 0;
		}
		float scrollPos = 0;
		while ( scrollPos < fmt.scrollAmount.y ) // find which line to start on
		{
			scrollPos += fmt.size;
			if ( scrollPos >= fmt.scrollAmount.y )
			{
				
				break;
			}
			else
			{
				scrollPos += fmt.spacing.y;
			}
			lineIndex++;
		}
		lineOffset = fmt.scrollAmount.y - (lineIndex * fmt.size + lineIndex * (fmt.spacing.y - 1));
		lineOffset /= scaleFactor;
	}
	else
	{
		charPos.y -= charAlign.y; // align text
	}
	
	float txtHeight = 0.0f;
	while ( lineIndex < lines.size() )
	{
		const char* line = std::get< const char* >(lines.at(lineIndex));
		unsigned int lineLength = std::get< unsigned int >(lines.at(lineIndex)); 
		// align text
		charPos.x = transform.pos(fmt.align).x;
		charPos.x -= AlignText(fmt.align, NoGUI::Wrap::DOWN, (Vector2){std::get< float >(lines.at(lineIndex)), fmt.size}, lineNum, (int)lines.size()).x;
		// draw text
		for (unsigned int i=0; i < lineLength; i++)
		{
			int codepointByteCount = 0;
			int codepoint = GetCodepoint(&line[i], &codepointByteCount);
			int index = GetGlyphIndex(font, codepoint);
			float glyphWidth = (font.glyphs[index].advanceX == 0) ? font.recs[index].width*scaleFactor : font.glyphs[index].advanceX*scaleFactor;;
			
			if ((codepoint != ' ') && (codepoint != '\t'))
			{
				// Character destination rectangle on screen
				// NOTE: We consider glyphPadding on drawing
				Rectangle dstRec = { charPos.x + font.glyphs[index].offsetX*scaleFactor - (float)font.glyphPadding*scaleFactor,
                      charPos.y + font.glyphs[index].offsetY*scaleFactor - (float)font.glyphPadding*scaleFactor,
                      (font.recs[index].width + 2.0f*font.glyphPadding)*scaleFactor,
                      (font.recs[index].height + 2.0f*font.glyphPadding)*scaleFactor};

				// Character source rectangle from font texture atlas
				// NOTE: We consider chars padding when drawing, it could be required for outline/glow shader effects
				Rectangle srcRec = { font.recs[index].x - (float)font.glyphPadding, font.recs[index].y - (float)font.glyphPadding,
                         font.recs[index].width + 2.0f*font.glyphPadding, font.recs[index].height + 2.0f*font.glyphPadding };
				
				if ( lineOffset > 0.0f ) // top line offset
				{
					dstRec.height -= lineOffset*scaleFactor;
					
					srcRec.y += lineOffset;
					srcRec.height -= lineOffset;
				}
				else // bottom line offset
				{
					dstRec.height += lineOffset*scaleFactor;
					
					srcRec.height += lineOffset;
				}
				// Draw the character texture on the screen
				DrawTexturePro(font.texture, srcRec, dstRec, (Vector2){ 0, 0 }, 0.0f, col);
			}
			charPos.x += glyphWidth + fmt.spacing.x; // move to next character
		}
		txtHeight += fmt.size - lineOffset * scaleFactor;
		if ( txtHeight > transform.height() )
		{
			
			break;
		}
		else
		{
			txtHeight += fmt.spacing.y;
		}
		if ( txtHeight + fmt.size > transform.height() )
		{
			lineOffset = (txtHeight + fmt.size - transform.height()) / scaleFactor * -1;
		}
		else
		{
			charPos.y -= lineOffset*scaleFactor;
			lineOffset = 0.0f;
		}
		lineNum++;
		lineIndex++;
		charPos.y += fmt.size + fmt.spacing.y;
	}
	// draw scroll bars
	if ( scrollBars )
	{
		Vector2 scrollPercent = {1.0f, fmt.scrollAmount.y / maxScroll};
		Vector2 percentShown = {1.0f, transform.height() / totalHeight};
		DrawScrollBars(nullptr, nullptr, transform, scrollPercent, percentShown, 3);
	}
}

void NoGUI::DrawCTextBox(const char* txt, CTextBox& fmt, const NoGUI::Transform& transform)
{
	Font font = fmt.font ? *(fmt.font) : GetFontDefault();
	Color col = fmt.fill ? fmt.fill->col : WHITE;
	float scaleFactor = fmt.size / (float)font.baseSize; // for calculating char size
	int counter = 0;
	unsigned int charCount = 0;
	unsigned int lineIndex = 0;
	float lineWidth = 0;
	float maxWidth = 0.0f;
	
	// clear static buffer
	static char buffer[NoMAD::INBUFF] = { 0 };
	memset(buffer, 0, NoMAD::INBUFF);
	// initialize result
	std::vector< std::tuple< const char*, float, unsigned int > > lines;
	lines.push_back(std::make_tuple(buffer, lineWidth, charCount));
	
	if (txt != NULL)
    {
		counter = 1;
        for (size_t i = 0; i < NoMAD::INBUFF; i++)
        {
			buffer[i] = txt[i];
			if (buffer[i] == '\0')
			{	
				
				break;
			}
			charCount++;
			int codepointByteCount = 0;
			int codepoint = GetCodepoint(&txt[i], &codepointByteCount);
			int index = GetGlyphIndex(font, codepoint);
			float glyphWidth = 0;
			
			if (codepoint != '\n')
			{
				glyphWidth = (font.glyphs[index].advanceX == 0) ? font.recs[index].width*scaleFactor : font.glyphs[index].advanceX*scaleFactor;
 				lineWidth += glyphWidth + fmt.spacing.x;
			}
			else
			{
				// replace newline char with terminating char 
				buffer[i] = '\0';
				// input current line width
				lineWidth -= fmt.spacing.x;
				std::get< float >(lines.at(counter - 1)) = lineWidth;
				if ( lineWidth > maxWidth )
				{
					maxWidth = lineWidth;
				}
				// input current char count
				std::get< unsigned int >(lines.at(counter - 1)) = charCount -1;
				// add next line to result and increment counter
				lineWidth = 0.0f;
				charCount = 0;
				lines.push_back(std::make_tuple(buffer + i + 1, lineWidth, charCount));
				counter++;
			}
		}
		const char* lastLine = std::get< const char* >(lines.back());
		// TODO: the last line will be iterated 3 times here. This can be optimized
		float lineWidth = MeasureTextEx(font, lastLine, fmt.size, fmt.spacing.x).x;
		std::get< float >(lines.back()) = lineWidth;
		if ( lineWidth > maxWidth )
		{
			maxWidth = lineWidth;
		}
		std::get< unsigned int >(lines.back()) = TextLength(lastLine);
	}
	
	float totalHeight = fmt.size * lines.size() + fmt.spacing.y * (lines.size() - 1);
	float lineOffset = 0.0f;
	float charOffset = 0.0f;
	int lineNum = 0;
	Vector2 maxScroll = {maxWidth - transform.width(), totalHeight - transform.height()};
	Vector2 charPos = transform.pos(fmt.align);
	Vector2 charAlign = AlignText(fmt.align, NoGUI::Wrap::DOWN, (Vector2){std::get< float >(lines.at(lineIndex)), fmt.size}, lineNum, (int)lines.size());
	charPos.x -= charAlign.x;
	bool scrollBars = maxWidth > transform.width() || totalHeight > transform.height();
	if ( maxWidth > transform.width() )
	{
		if ( fmt.scrollAmount.x > maxScroll.x )
		{
			fmt.scrollAmount.x = maxScroll.x;
		}
		if ( fmt.scrollAmount.x < 0 )
		{
			fmt.scrollAmount.x = 0;
		}
	}
	
	if ( totalHeight > transform.height() ) // find which line to start on
	{
		charPos.y = transform.pos(NoGUI::Align(-1, -1)).y; // align to top
		if ( fmt.scrollAmount.y > maxScroll.y )
		{
			fmt.scrollAmount.y = maxScroll.y;
		}
		if ( fmt.scrollAmount.y < 0 )
		{
			fmt.scrollAmount.y = 0;
		}
		float scrollPos = 0;
		while ( scrollPos < fmt.scrollAmount.y ) // find which line to start on
		{
			scrollPos += fmt.size;
			if ( scrollPos >= fmt.scrollAmount.y )
			{
				
				break;
			}
			else
			{
				scrollPos += fmt.spacing.y;
			}
			lineIndex++;
		}
		lineOffset = fmt.scrollAmount.y - (lineIndex * fmt.size + lineIndex * (fmt.spacing.y - 1));
		lineOffset /= scaleFactor;
	}
	else
	{
		charPos.y -= charAlign.y; // align text
	}
	
	float txtHeight = 0.0f;
	while ( lineIndex < lines.size() )
	{
		const char* line = std::get< const char* >(lines.at(lineIndex));
		unsigned int lineLength = std::get< unsigned int >(lines.at(lineIndex));
		float scroll = fmt.scrollAmount.x;
		// align text
		charPos.x = transform.pos(fmt.align).x;
		charPos.x -= AlignText(fmt.align, NoGUI::Wrap::DOWN, (Vector2){std::get< float >(lines.at(lineIndex)), fmt.size}, lineNum, (int)lines.size()).x;
		for (unsigned int i=0; i < lineLength; i++)
		{
			int codepointByteCount = 0;
			int codepoint = GetCodepoint(&line[i], &codepointByteCount);
			int index = GetGlyphIndex(font, codepoint);
			float glyphWidth = (font.glyphs[index].advanceX == 0) ? font.recs[index].width*scaleFactor : font.glyphs[index].advanceX*scaleFactor;
			
			if ( scroll > 0 )
			{
				charPos.x -= scroll;
				scroll = 0;
			}
			
			if ((codepoint != ' ') && (codepoint != '\t'))
			{
				float diff = transform.pos(NoGUI::Align(-1, -1)).x - charPos.x;
				if ( diff > 0 )
				{
					lineWidth = 0;
					if ( diff < glyphWidth )
					{
						charOffset = diff / scaleFactor;
					}
					else
					{
						charPos.x += glyphWidth + fmt.spacing.x;
					
						continue;
					}
				}
				if ( charPos.x + glyphWidth > transform.pos(NoGUI::Align(1, -1)).x )
				{
					charOffset = (charPos.x + glyphWidth - transform.pos(NoGUI::Align(1, -1)).x) / scaleFactor * -1;
				}
				// Character destination rectangle on screen
				// NOTE: We consider glyphPadding on drawing
				Rectangle dstRec = { charPos.x + font.glyphs[index].offsetX*scaleFactor - (float)font.glyphPadding*scaleFactor,
                      charPos.y + font.glyphs[index].offsetY*scaleFactor - (float)font.glyphPadding*scaleFactor,
                      (font.recs[index].width + 2.0f*font.glyphPadding)*scaleFactor,
                      (font.recs[index].height + 2.0f*font.glyphPadding)*scaleFactor};

				// Character source rectangle from font texture atlas
				// NOTE: We consider chars padding when drawing, it could be required for outline/glow shader effects
				Rectangle srcRec = { font.recs[index].x - (float)font.glyphPadding, font.recs[index].y - (float)font.glyphPadding,
                         font.recs[index].width + 2.0f*font.glyphPadding, font.recs[index].height + 2.0f*font.glyphPadding };
				
				if ( charOffset > 0.0f ) // front/left char offset
				{
					dstRec.x += charOffset*scaleFactor;
					dstRec.width -= charOffset*scaleFactor;
					
					srcRec.x += charOffset;
					srcRec.width -= charOffset;
				}
				else // back/right char offset
				{
					dstRec.width += charOffset*scaleFactor;
					
					srcRec.width += charOffset;
				}
				if ( lineOffset > 0.0f ) // top line offset
				{
					dstRec.height -= lineOffset*scaleFactor;
					
					srcRec.y += lineOffset;
					srcRec.height -= lineOffset;
				}
				else // bottom line offset
				{
					dstRec.height += lineOffset*scaleFactor;
					
					srcRec.height += lineOffset;
				}
				
				DrawTexturePro(font.texture, srcRec, dstRec, (Vector2){ 0, 0 }, 0.0f, col);
				charOffset = 0;
			}
			charPos.x += glyphWidth + fmt.spacing.x; // move to next character
			if ( charPos.x >= transform.pos(NoGUI::Align(1, -1)).x)
			{
				
				break;
			}
		}
		txtHeight += fmt.size - lineOffset * scaleFactor;
		if ( txtHeight > transform.height() )
		{
		
			break;
		}
		else
		{
			txtHeight += fmt.spacing.y;
		}
		if ( txtHeight + fmt.size > transform.height() )
		{
			lineOffset = (txtHeight + fmt.size - transform.height()) / scaleFactor * -1;
		}
		else
		{
			charPos.y -= lineOffset*scaleFactor;
			lineOffset = 0.0f;
		}
		charPos.y += fmt.size + fmt.spacing.y;
		lineIndex++;
		lineNum++;
	}
	if ( scrollBars )
	{
		Vector2 scrollPercent = {fmt.scrollAmount.x / maxScroll.x, fmt.scrollAmount.y / maxScroll.y};
		Vector2 percentShown = {transform.width() / maxWidth, transform.height() / totalHeight};
		DrawScrollBars(nullptr, nullptr, transform, scrollPercent, percentShown, 3);
	}
}

void NoGUI::DrawCImageCropped(CImage& img, std::shared_ptr< nShape > shape, const NoGUI::Transform& transform)
{
	// calculate img dimensions	
	Vector2 imgSize = {img.img->width * img.scale.x, img.img->height * img.scale.y};
	Vector2 maxSize = imgSize;
	Vector2 displace = {transform.radius.x, transform.radius.y}; // displacement for positions array
	bool drawBars = false;
	float umod = 0; // texture x coordnite difference as a percentage / 2
	float vmod = 0; // texture y coordnite difference as a percentage / 2
	if ( maxSize.x > transform.width() )
	{
		maxSize.x = transform.width();
		umod = (imgSize.x - transform.width()) / imgSize.x / 2;
		drawBars = maxSize.y > transform.height();
	}
	if ( maxSize.y > transform.height() )
	{
		maxSize.y = transform.height();
		vmod = (imgSize.y - transform.height()) / imgSize.y / 2;
	}
	if ( imgSize.y < transform.height() || imgSize.x < transform.width() )
	{
		Vector2 elemScale = {transform.width() / img.img->width, transform.height() / img.img->height};
		// scale image such that no dimensions are smaller than element
		if ( elemScale.x > elemScale.y )
		{
			maxSize = {transform.width(), transform.height()};
			// difference between minimum scale and current scale as a percentage
			// if negative = img bigger than element
			// if positive = img smaller than element
			Vector2 scaleDiff = {(elemScale.x - img.scale.x) / elemScale.x, (elemScale.x - img.scale.y) / elemScale.x};
			if ( scaleDiff.x > 0 )
			{
				maxSize.x -= maxSize.x * scaleDiff.x;
			}
			else
			{
				// u, v mod stuff
			}
			if ( scaleDiff.y > 0 )
			{
				maxSize.y -= maxSize.y * scaleDiff.y;
			}
			else
			{
				// u, v mod stuff
			}
		}
		else
		{
			maxSize = {transform.width(), transform.height()};
			Vector2 scaleDiff = {(elemScale.y - img.scale.x) / elemScale.y, (elemScale.y - img.scale.y) / elemScale.y};
			if ( scaleDiff.x > 0 )
			{
				maxSize.x -= maxSize.x * scaleDiff.x;
				umod = (img.img->width * elemScale.y - maxSize.x) / (img.img->width * elemScale.y) / 2;
			}
			else
			{
				// u,v mod stuff
			}
			if ( scaleDiff.y > 0 )
			{
				maxSize.y -= maxSize.y * scaleDiff.y;
				vmod = (img.img->height * elemScale.y - maxSize.y) / (img.img->height * elemScale.y) / 2;
			}
			else
			{
				// u, v mod stuff
			}
		}
		// negative = flipped
		if ( img.scale.y < 0 )
		{
			if ( maxSize.y < transform.height() * -1 )
			{
				maxSize.y = transform.height() * -1;
				vmod = (imgSize.y + transform.height()) / imgSize.y / 2;
				drawBars = true;
			}
			else
			{
				vmod = (img.img->height * elemScale.y + maxSize.y) / (img.img->height * elemScale.y) / 2;
			}
		}
		if ( img.scale.x < 0 )
		{
			if ( maxSize.x < transform.height() * -1 )
			{
				maxSize.x = transform.width() * -1;
				umod = (imgSize.x + transform.width()) / imgSize.x / 2;
				drawBars = true;
			}
			else
			{
				umod = (img.img->width * elemScale.y + maxSize.x) / (img.img->width * elemScale.y) / 2;
			}
		}
		displace.y = maxSize.y / 2;
		displace.x = maxSize.x / 2;
	}
	// TODO: prolly a cleaner more efficent way of doing this
	if (img.scrollPos.x > 1)
	{
		img.scrollPos.x = 1;
	}
	if (img.scrollPos.x < 0)
	{
		img.scrollPos.x = 0;
	}
	if (img.scrollPos.y > 1)
	{
		img.scrollPos.y = 1;
	}
	if (img.scrollPos.y < 0)
	{
		img.scrollPos.y = 0;
	}
			
	switch (shape->n)
	{
		case 0:
		{
			int max = 37;
			float centralAngle = 0;
			Vector2 midPoint = {0.5f, 0.5f};
			if ( img.scrollable )
			{
				Vector2 translate = {(img.scrollPos.x - 0.5f) * (umod * 2), (img.scrollPos.y - 0.5f) * (vmod * 2)};
				midPoint.x += translate.x;
				midPoint.y += translate.y;
			}
			Vector2 texcoords[max] = { 0 };
			Vector2 points[max] = { 0 };
			for (int i=0; i < max; i++)
			{
				float sin = sinf(centralAngle * DEG2RAD);
				float cos = cosf(centralAngle * DEG2RAD);
				// calculate texture coordnites offset
				points[i].x = sin * 0.5f * maxSize.x;
				points[i].y = cos * 0.5f * maxSize.y;
				// calculate texture coordnites
				texcoords[i] = (Vector2){midPoint.x + sin * (0.5f - umod), midPoint.y + cos * (0.5f - vmod)};
						
				centralAngle += 10;
			}
			// create copy to rotate coordnites
			Vector2 positions[max] = { 0 };
			for (int i=0; i < max; i++) 
			{	
				positions[i] = Vector2Rotate(points[i], transform.angle*DEG2RAD);
			}
			
			DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), midPoint, positions, texcoords, max, shape->fill->col);
			if ( drawBars && img.scrollable )
			{
				Vector2 percentShown = {maxSize.x / imgSize.x, maxSize.y / imgSize.y};
				DrawScrollBars(nullptr, nullptr, transform, img.scrollPos, percentShown, 3);
			}
			
			break;
		}
		
		case 1:
		{

			break;
		}
		
		case 2:
		{

			break;
		}
		
		case 3:
		{
			int max = 4;
			float left = 0.0f + umod;
			float right = 1.0f - umod;
			float top = 0.0f + vmod;
			float bottom = 1.0f - vmod;
			Vector2 midPoint = {0.5f, 0.5f};
			if ( img.scrollable )
			{
				Vector2 translate = {(img.scrollPos.x - 0.5f) * (umod * 2), (img.scrollPos.y - 0.5f) * (vmod * 2)};
				left += translate.x;
				right += translate.x;
				top += translate.y;
				bottom += translate.y;
				midPoint.x += translate.x;
				midPoint.y += translate.y;
			}
			Vector2 texcoords[max] =
			{ 
				(Vector2){midPoint.x, top},
				(Vector2){left, bottom},
				(Vector2){right, bottom},
				(Vector2){midPoint.x, top},
			};
			Vector2 points[max] = 
			{
				(Vector2){0.0f, displace.y * -1},
				(Vector2){displace.x * -1, displace.y},
				(Vector2){displace.x, displace.y},
				(Vector2){0.0f, displace.y * -1},
			};
			Vector2 positions[max] = { 0 };
			for (int i = 0; i < max; i++)
			{	
				positions[i] = Vector2Rotate(points[i], transform.angle*DEG2RAD);
			}
			
			DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), midPoint, positions, texcoords, max, shape->fill->col);
			if ( drawBars && img.scrollable )
			{
				Vector2 percentShown = {maxSize.x / imgSize.x, maxSize.y / imgSize.y};
				DrawScrollBars(nullptr, nullptr, transform, img.scrollPos, percentShown, 3);
			}
			
			break;
		}
		
		case 4:
		{	
			int max = 5;
			float left = 0.0f + umod;
			float right = 1.0f - umod;
			float top = 0.0f + vmod;
			float bottom = 1.0f - vmod;
			Vector2 midPoint = {0.5f, 0.5f};
			if ( img.scrollable )
			{
				Vector2 translate = {(img.scrollPos.x - 0.5f) * (umod * 2), (img.scrollPos.y - 0.5f) * (vmod * 2)};
				left += translate.x;
				right += translate.x;
				top += translate.y;
				bottom += translate.y;
				midPoint.x += translate.x;
				midPoint.y += translate.y;
			}
			Vector2 texcoords[max] =
			{ 
				(Vector2){left, top},
				(Vector2){left, bottom},
				(Vector2){right, bottom},
				(Vector2){right, top},
				(Vector2){left, top}
			};
			Vector2 points[max] = 
			{
				(Vector2){displace.x * -1, displace.y * -1},
				(Vector2){displace.x * -1, displace.y},
				(Vector2){displace.x, displace.y},
				(Vector2){displace.x, displace.y * -1},
				(Vector2){displace.x * -1, displace.y * -1}
			};
			Vector2 positions[max] = { 0 };
			for (int i = 0; i < max; i++)
			{	
				positions[i] = Vector2Rotate(points[i], transform.angle*DEG2RAD);
			}
			
			DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), midPoint, positions, texcoords, max, shape->fill->col);
			if ( drawBars && img.scrollable )
			{
				Vector2 percentShown = {maxSize.x / imgSize.x, maxSize.y / imgSize.y};
				DrawScrollBars(nullptr, nullptr, transform, img.scrollPos, percentShown, 3);
			}
			
			break;
		}
		
		default:
		{
			int max = shape->n + 1;
			float centralAngle = 0;
			Vector2 midPoint = {0.5f, 0.5f};
			if ( img.scrollable )
			{
				Vector2 translate = {(img.scrollPos.x - 0.5f) * (umod * 2), (img.scrollPos.y - 0.5f) * (vmod * 2)};
				midPoint.x += translate.x;
				midPoint.y += translate.y;
			}
			Vector2 texcoords[max] = { 0 };
			Vector2 points[max] = { 0 };
			for (int i=0; i < max; i++)
			{
				float sin = sinf(centralAngle * DEG2RAD);
				float cos = cosf(centralAngle * DEG2RAD);
				// calculate texture coordnites offset
				points[i].x = sin * 0.5f * maxSize.x;
				points[i].y = cos * 0.5f * maxSize.y;
				// calculate texture coordnites
				texcoords[i] = (Vector2){midPoint.x + sin * (0.5f - umod), midPoint.y + cos * (0.5f - vmod)};
						
				centralAngle += 360.0f / (float)shape->n;
			}
			// create copy to rotate coordnites
			Vector2 positions[max] = { 0 };
			for (int i=0; i < max; i++) 
			{	
				positions[i] = Vector2Rotate(points[i], transform.angle*DEG2RAD);
			}
			
			DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), midPoint, positions, texcoords, max, shape->fill->col);
			if ( drawBars && img.scrollable )
			{
				Vector2 percentShown = {maxSize.x / imgSize.x, maxSize.y / imgSize.y};
				DrawScrollBars(nullptr, nullptr, transform, img.scrollPos, percentShown, 3);
			}

			break;
		}
	}
}

void NoGUI::DrawCImageFitted(CImage& img, std::shared_ptr< nShape > shape, const NoGUI::Transform& transform)
{
	// TODO: prolly a cleaner more efficent way of doing this
	if (img.scrollPos.x > 1)
	{
		img.scrollPos.x = 1;
	}
	if (img.scrollPos.x < 0)
	{
		img.scrollPos.x = 0;
	}
	if (img.scrollPos.y > 1)
	{
		img.scrollPos.y = 1;
	}
	if (img.scrollPos.y < 0)
	{
		img.scrollPos.y = 0;
	}
	switch (shape->n)
	{
		case 0:
		{
			int max = 37;
			Vector2 midPoint = {0.5f, 0.5f}; // midPoint of texture
			Vector2 rate = {0, 0}; // texture scaling factor
			Vector2 displace = transform.radius; // length of points
			if ( img.scale.x >= 1.0f )
			{
				rate.x = 1.0f - (1.0f / img.scale.x);
				if ( img.scrollable )
				{
					float translate = (img.scrollPos.x - 0.5f) * rate.x;
					midPoint.x += translate;
				}
			}
			else if ( img.scale.x >= -1.0f )
			{
				displace.x *= img.scale.x;
			}
			else
			{
				displace.x *= -1;
				rate.x = 1.0f + (1.0f / img.scale.x);
				if ( img.scrollable )
				{
					float translate = (img.scrollPos.x - 0.5f) * rate.x;
					midPoint.x -= translate;
				}
			}
			
			if ( img.scale.y >= 1.0f )
			{
				rate.y = 1.0f - (1.0f / img.scale.y);
				if ( img.scrollable )
				{
					float translate = (img.scrollPos.y - 0.5f) * rate.y;
					midPoint.y += translate;
				}
			}
			else if ( img.scale.x >= -1.0f )
			{
				displace.y *= img.scale.y;
			}
			else
			{
				displace.y *= -1;
				rate.y = 1.0f + (1.0f / img.scale.y);
				if ( img.scrollable )
				{
					float translate = (img.scrollPos.y - 0.5f) * rate.y;
					midPoint.y -= translate;
				}
			}
			float centralAngle = transform.angle;
			Vector2 texcoords[max] = { 0 };
			Vector2 points[max] = { 0 };
			for (int i=0; i < max; i++)
			{
				float sin = sinf(centralAngle * DEG2RAD);
				float cos = cosf(centralAngle * DEG2RAD);
				points[i].x = sin * displace.x;
				points[i].y = cos * displace.y;
				texcoords[i] = (Vector2){midPoint.x + sin * (0.5f - rate.x / 2), midPoint.y + cos * (0.5f - rate.y / 2)};
				centralAngle += 10;
			}
			Vector2 positions[max] = { 0 };
			for (int i=0; i < max; i++) 
			{	
				positions[i] = Vector2Rotate(points[i], transform.angle*DEG2RAD);
			}
			
			DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), midPoint, positions, texcoords, max, shape->fill->col);
			if ( img.scale.x > 1.001f || img.scale.y > 1.001f ) // stupid hack because of float precision
			{
				if ( img.scrollable )
				{
					Vector2 percentShown = {1.0f / img.scale.x, 1.0f / img.scale.y};
					DrawScrollBars(nullptr, nullptr, transform, img.scrollPos, percentShown, 3);
				}
			}
			else if ( img.scale.x < -1.001f || img.scale.y < -1.001f )
			{
				if ( img.scrollable )
				{
					Vector2 percentShown = {-1.0f / img.scale.x, -1.0f / img.scale.y};
					DrawScrollBars(nullptr, nullptr, transform, img.scrollPos, percentShown, 3);
				}
			}
			
			break;
		}
		
		case 1:
		{
			
			break;
		}
		
		case 2:
		{
			
			break;
		}

		case 3:
		{
			int max = 4;
			float left = 0.0f;
			float right = 1.0f;
			float top = 0.0f;
			float bottom = 1.0f;
			Vector2 displace = transform.radius;
			Vector2 midPoint = {0.5f, 0.5f};
			if ( img.scale.x >= 1.0f )
			{
				float rate = 1.0f - (1.0f / img.scale.x);
				left = rate / 2;
				right = 1 - left;
				if ( img.scrollable )
				{
					float translate = (img.scrollPos.x - 0.5f) * rate;
					left += translate;
					right += translate;
					midPoint.x += translate;
				}
			}
			else if ( img.scale.x >= -1.0f )
			{
				displace.x *= img.scale.x;
			}
			else
			{
				displace.x = transform.radius.x * -1;
				float rate = 1.0f + (1.0f / img.scale.x);
				left = rate / 2;
				right = 1 - left;
				if ( img.scrollable )
				{
					float translate = (img.scrollPos.x - 0.5f) * rate;
					left -= translate;
					right -= translate;
					midPoint.x -= translate;
				}
			}
			
			if ( img.scale.y >= 1.0f )
			{
				float rate = 1.0f - (1.0f / img.scale.y);
				top = rate / 2;
				bottom = 1 - top;
				if ( img.scrollable )
				{
					float translate = (img.scrollPos.y - 0.5f) * rate;
					top += translate;
					bottom += translate;
					midPoint.y += translate;
				}
			}
			else if ( img.scale.x >= -1.0f )
			{
				displace.y *= img.scale.y;
			}
			else
			{
				displace.y = transform.radius.y * -1;
				float rate = 1.0f + (1.0f / img.scale.y);
				top = rate / 2;
				bottom = 1 - top;
				if ( img.scrollable )
				{
					float translate = (img.scrollPos.y - 0.5f) * rate;
					top -= translate;
					bottom -= translate;
					midPoint.y -= translate;
				}
			}
			Vector2 texcoords[max] =
			{ 
				(Vector2){(left + right) / 2, top},
				(Vector2){left, bottom},
				(Vector2){right, bottom},
				(Vector2){(left + right) / 2, top}
			};
			Vector2 points[max] =
			{ 
				(Vector2){0, displace.y * -1},
				(Vector2){displace.x * -1, displace.y},
				(Vector2){displace.x, displace.y},
				(Vector2){0, displace.y * -1}
			};
					
			Vector2 positions[max] = { 0 };
			for (int i = 0; i < max; i++)
			{	
				positions[i] = Vector2Rotate(points[i], transform.angle*DEG2RAD);
			}
			
			DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), midPoint, positions, texcoords, max, shape->fill->col);
			if ( img.scale.x > 1.001f || img.scale.y > 1.001f || img.scale.x < -1.001f || img.scale.y < -1.001f ) // stupid hack because of float precision
			{
				if ( img.scrollable )
				{
					Vector2 percentShown = {right - left, bottom - top};
					DrawScrollBars(nullptr, nullptr, transform, img.scrollPos, percentShown, 3);
				}
			}
			
			break;
		}
		
		case 4:
		{
			int max = 5;
			float left = 0.0f;
			float right = 1.0f;
			float top = 0.0f;
			float bottom = 1.0f;
			Vector2 displace = transform.radius;
			Vector2 midPoint = {0.5f, 0.5f};
			if ( img.scale.x >= 1.0f )
			{
				float rate = 1.0f - (1.0f / img.scale.x);
				left = rate / 2;
				right = 1 - left;
				if ( img.scrollable )
				{
					float translate = (img.scrollPos.x - 0.5f) * rate;
					left += translate;
					right += translate;
					midPoint.x += translate;
				}
			}
			else if ( img.scale.x >= -1.0f )
			{
				displace.x *= img.scale.x;
			}
			else
			{
				displace.x = transform.radius.x * -1;
				float rate = 1.0f + (1.0f / img.scale.x);
				left = rate / 2;
				right = 1 - left;
				if ( img.scrollable )
				{
					float translate = (img.scrollPos.x - 0.5f) * rate;
					left -= translate;
					right -= translate;
					midPoint.x -= translate;
				}
			}
			
			if ( img.scale.y >= 1.0f )
			{
				float rate = 1.0f - (1.0f / img.scale.y);
				top = rate / 2;
				bottom = 1 - top;
				if ( img.scrollable )
				{
					float translate = (img.scrollPos.y - 0.5f) * rate;
					top += translate;
					bottom += translate;
					midPoint.y += translate;
				}
			}
			else if ( img.scale.x >= -1.0f )
			{
				displace.y *= img.scale.y;
			}
			else
			{
				displace.y = transform.radius.y * -1;
				float rate = 1.0f + (1.0f / img.scale.y);
				top = rate / 2;
				bottom = 1 - top;
				if ( img.scrollable )
				{
					float translate = (img.scrollPos.y - 0.5f) * rate;
					top -= translate;
					bottom -= translate;
					midPoint.y -= translate;
				}
			}
			Vector2 texcoords[max] =
			{ 
				(Vector2){left, top},
				(Vector2){left, bottom},
				(Vector2){right, bottom},
				(Vector2){right, top},
				(Vector2){left, top}
			};
			Vector2 points[max] = 
			{
				(Vector2){displace.x * -1, displace.y * -1},
				(Vector2){displace.x * -1, displace.y},
				(Vector2){displace.x, displace.y},
				(Vector2){displace.x, displace.y * -1},
				(Vector2){displace.x * -1, displace.y * -1}
			};
			Vector2 positions[max] = { 0 };
			for (int i = 0; i < max; i++)
			{	
				positions[i] = Vector2Rotate(points[i], transform.angle*DEG2RAD);
			}
			
			DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), midPoint, positions, texcoords, max, shape->fill->col);
			
			if ( img.scale.x > 1.001f || img.scale.y > 1.001f || img.scale.x < -1.001f || img.scale.y < -1.001f ) // stupid hack because of float precision
			{
				if ( img.scrollable )
				{
					Vector2 percentShown = {right - left, bottom - top};
					DrawScrollBars(nullptr, nullptr, transform, img.scrollPos, percentShown, 3);
				}
			}
			
			break;
		}
		
		default:
		{
			int max = shape->n + 1;
			Vector2 midPoint = {0.5f, 0.5f}; // midPoint of texture
			Vector2 rate = {0, 0}; // texture scaling factor
			Vector2 displace = transform.radius; // length of points
			if ( img.scale.x >= 1.0f )
			{
				rate.x = 1.0f - (1.0f / img.scale.x);
				if ( img.scrollable )
				{
					float translate = (img.scrollPos.x - 0.5f) * rate.x;
					midPoint.x += translate;
				}
			}
			else if ( img.scale.x >= -1.0f )
			{
				displace.x *= img.scale.x;
			}
			else
			{
				displace.x *= -1;
				rate.x = 1.0f + (1.0f / img.scale.x);
				if ( img.scrollable )
				{
					float translate = (img.scrollPos.x - 0.5f) * rate.x;
					midPoint.x -= translate;
				}
			}
			
			if ( img.scale.y >= 1.0f )
			{
				rate.y = 1.0f - (1.0f / img.scale.y);
				if ( img.scrollable )
				{
					float translate = (img.scrollPos.y - 0.5f) * rate.y;
					midPoint.y += translate;
				}
			}
			else if ( img.scale.x >= -1.0f )
			{
				displace.y *= img.scale.y;
			}
			else
			{
				displace.y *= -1;
				rate.y = 1.0f + (1.0f / img.scale.y);
				if ( img.scrollable )
				{
					float translate = (img.scrollPos.y - 0.5f) * rate.y;
					midPoint.y -= translate;
				}
			}
			float centralAngle = 0;
			Vector2 texcoords[max] = { 0 };
			Vector2 points[max] = { 0 };
			for (int i=0; i < max; i++)
			{
				float sin = sinf(centralAngle * DEG2RAD);
				float cos = cosf(centralAngle * DEG2RAD);
				points[i].x = sin * displace.x;
				points[i].y = cos * displace.y;
				texcoords[i] = (Vector2){midPoint.x + sin * (0.5f - rate.x / 2), midPoint.y + cos * (0.5f - rate.y / 2)};
				centralAngle += 360.0f / (float)shape->n;
			}
			Vector2 positions[max] = { 0 };
			for (int i = 0; i < max; i++)
			{	
				positions[i] = Vector2Rotate(points[i], transform.angle*DEG2RAD);
			}
			
			DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), midPoint, positions, texcoords, max, shape->fill->col);
			if ( img.scale.x > 1.001f || img.scale.y > 1.001f ) // stupid hack because of float precision
			{
				if ( img.scrollable )
				{
					Vector2 percentShown = {1.0f / img.scale.x, 1.0f / img.scale.y};
					DrawScrollBars(nullptr, nullptr, transform, img.scrollPos, percentShown, 3);
				}
			}
			if ( img.scale.x < -1.001f || img.scale.y < -1.001f )
			{
				if ( img.scrollable )
				{
					Vector2 percentShown = {-1.0f / img.scale.x, -1.0f / img.scale.y};
					DrawScrollBars(nullptr, nullptr, transform, img.scrollPos, percentShown, 3);
				}
			}
			
			break;
		}
	}
}

void NoGUI::DrawCImageShaped(CImage& img, const NoGUI::Transform& transform, std::shared_ptr< nShape > shape)
{
	// calculate image dimensions
	Vector2 imgSize = {img.img->width * img.scale.x, img.img->height * img.scale.y};
	switch ( shape->n )
	{
		case 0:
		{
			int max = 37;
			int centralAngle = 0;
			Vector2 texcoords[max] = { 0 };
			Vector2 points[max] = { 0 };
			for (int i=0; i < max; i++)
			{
				float sin = sinf(centralAngle * DEG2RAD);
				float cos = cosf(centralAngle * DEG2RAD);
				points[i] = (Vector2){sin * imgSize.x / 2, cos * imgSize.y / 2};
				texcoords[i] = (Vector2){0.5f + sin * 0.5f, 0.5f + cos * 0.5f};
				centralAngle += 10;
			}
			Vector2 positions[max] = { 0 };
			for (int i=0; i < max; i++) 
			{	
				positions[i] = Vector2Rotate(points[i], transform.angle*DEG2RAD);
			}
			
			DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), (Vector2){0.5f, 0.5f}, positions, texcoords, max, shape->fill->col);
			
			break;
		}
		
		case 1:
		{
			
			break;
		}
		
		case 2:
		{
			
			break;
		}
		
		case 3:
		{
			int max = 4;
			Vector2 texcoords[max] =
			{ 
				(Vector2){0.5f, 0.0f},
				(Vector2){0.0f, 1.0f},
				(Vector2){1.0f, 1.0f},
				(Vector2){0.5f, 0.0f}
			};
			Vector2 points[max] =
			{ 
				(Vector2){0, imgSize.y * -0.5f},
				(Vector2){imgSize.x * -0.5f, imgSize.y * 0.5f},
				(Vector2){imgSize.x * 0.5f, imgSize.y * 0.5f},
				(Vector2){0, imgSize.y * -0.5f}
			};
			Vector2 positions[max] = { 0 };
			for (int i = 0; i < max; i++)
			{	
				positions[i] = Vector2Rotate(points[i], transform.angle*DEG2RAD);
			}
			
			DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), (Vector2){0.5f, 0.5f}, positions, texcoords, max, shape->fill->col);
			
			break;
		}
		
		case 4:
		{
			Rectangle source = {0, 0, (float)img.img->width, (float)img.img->height};
			// center on shape
			Vector2 destPos = transform.pos(NoGUI::Align(0, 0));
			Rectangle dest = {destPos.x, destPos.y, imgSize.x, imgSize.y};
			Vector2 origin = {dest.width / 2, dest.height / 2};
			
			DrawTexturePro((*img.img), source, dest, origin, transform.angle, shape->fill->col);
			
			break;
		}
		
		default:
		{
			int max = shape->n + 1;
			int centralAngle = 0;
			Vector2 texcoords[max] = { 0 };
			Vector2 points[max] = { 0 };
			for (int i=0; i < max; i++)
			{
				float sin = sinf(centralAngle * DEG2RAD);
				float cos = cosf(centralAngle * DEG2RAD);
				points[i] = (Vector2){sin * imgSize.x / 2, cos * imgSize.y / 2};
				texcoords[i] = (Vector2){0.5f + sin * 0.5f, 0.5f + cos * 0.5f};
				centralAngle += 360.0f / (float)shape->n;
			}
			Vector2 positions[max] = { 0 };
			for (int i = 0; i < max; i++)
			{	
				positions[i] = Vector2Rotate(points[i], transform.angle*DEG2RAD);
			}
			
			DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), (Vector2){0.5f, 0.5f}, positions, texcoords, max, shape->fill->col);
			
			break;
		}
	}
}

void NoGUI::DrawCImage(CImage& img, std::shared_ptr< nShape > shape, const NoGUI::Transform& transform)
{
	switch(img.crop)
	{
		case Crop::NONE:
		{
			DrawCImageShaped(img, transform, shape);
			
			break;
		}
		
		case Crop::FIT:
		{
			DrawCImageFitted(img, shape, transform);
			
			break;
		}
		
		case Crop::CUT:
		{
			DrawCImageCropped(img, shape, transform);
			
			break;
		}
	}
}

void NoGUI::DrawCInput(CInput& input, std::shared_ptr< Font > font, float fontSize, const char* txt, const Color& col, const Vector2& spacing, const Align& txtAlign, const Transform& transform, const Crop& cropping, float angle)
{
	// draw blinkChar if it has been blinkRate time since lastBlink + blinkHold time
	double currentTime = GetTime();
	if ( currentTime - input.lastBlink >= input.blinkRate )
	{
		double timeGate = input.lastBlink + input.blinkHold + input.blinkRate;
		if ( currentTime > timeGate )
		{
			input.lastBlink = currentTime;
		}
		if ( (input.blinkChar >= 32) && (input.blinkChar <= 125) )
		{
			int byteSize = 0;
			const char* toDraw = CodepointToUTF8(input.blinkChar, &byteSize);
			Font drawFont = (font) ? *(font) : GetFontDefault();
			Vector2 blinkPos = transform.pos(txtAlign);
			Vector2 origin = {0, 0};
			float lastLineWidth = 0.0f;
			float txtHeight = 0.0f;
			int numLines = 0;
			switch (cropping)
			{
				case Crop::NONE:
				{
					const char** lines = TextSplit(txt, '\n', &numLines);
					lastLineWidth = MeasureTextEx(drawFont, lines[numLines - 1], fontSize, spacing.x).x;
					txtHeight = (numLines - 1) * fontSize + spacing.y * (numLines - 2);
					
					break;
				}
				
				case Crop::FIT:
				{
					std::vector< std::tuple< const char*, float, unsigned int > > lines = WrapText(txt, drawFont, fontSize, spacing.x, transform);
					lastLineWidth = std::get< float >(lines.at(lines.size() -  1));
					txtHeight = (lines.size() - 1) * fontSize + spacing.y * (lines.size() - 2);
					
					break;
				}
				
				case Crop::CUT:
				{
					const char** lines = TextSplit(txt, '\n', &numLines);
					lastLineWidth = MeasureTextEx(drawFont, lines[numLines - 1], fontSize, spacing.x).x;
					if ( lastLineWidth > transform.width() )
					{
						lastLineWidth = transform.width();
					}
					txtHeight = (numLines - 1) * fontSize + spacing.y * (numLines - 2);
					
					break;
				}
			}
			switch ( txtAlign.x )
			{
				case XAlign::LEFT:
				{
					origin.x = lastLineWidth * -1;
					
					break;
				}
				
				case XAlign::CENTER:
				{
					origin.x = lastLineWidth / -2;
					
					break;
				}
				
				case XAlign::RIGHT:
				{
					
					break;
				}
			}
			switch ( txtAlign.y )
			{
				case YAlign::TOP:
				{
					origin.y = txtHeight * -1;
					
					break;
				}
				
				case YAlign::CENTER:
				{
					origin.y = (txtHeight - fontSize) / -2;
					
					break;
				}
				
				case YAlign::BOTTOM:
				{
					origin.y = fontSize;
					
					break;
				}
			}
			
			DrawTextPro(drawFont, toDraw, blinkPos, origin, angle, fontSize, 0, col);
		}
	}
}

void NoGUI::DrawCInput(CInput& input, CText& fmt, const char* txt, const NoGUI::Transform& transform)
{
	Color col = WHITE;
	if ( fmt.fill )
	{
		col = fmt.fill->hoverCol;
	}
	DrawCInput(input, fmt.font, fmt.size, txt, col, fmt.spacing, fmt.align, transform, Crop::NONE, fmt.angle);
}

void NoGUI::DrawCInput(CInput& input, CTextBox& fmt, const char* txt, const NoGUI::Transform& transform)
{
	Color col = WHITE;
	if ( fmt.fill )
	{
		col = fmt.fill->hoverCol;
	}
	Crop cropping = (fmt.wrap) ? Crop::FIT : Crop::CUT;
	DrawCInput(input, fmt.font, fmt.size, txt, col, fmt.spacing, fmt.align, transform, cropping, 0);
}

void NoGUI::DrawCMultiShape(const Transform& anchor, const CMultiShape& shapes, bool hovered)
{
	for ( std::pair< std::shared_ptr< nShape >, Transform > shape : shapes.shapes )
	{
		Transform transform = shape.second;
		Vector2 center = anchor.pos(transform.origin);
		Vector2 offset = transform.pos();
		float angle = transform.angle;
		if ( anchor.angle != 0 )
		{
			offset = Vector2Rotate(offset, anchor.angle * DEG2RAD);
			angle += anchor.angle;
		}
		center.x += offset.x;
		center.y += offset.y;
		
		DrawShape(*(shape.first), center, transform.radius, (Vector2){0, 0}, angle, hovered);
	}
}

void NoGUI::DrawComponents(Components& components, std::shared_ptr< nShape > shape, const NoGUI::Transform& transform, const char* inner, bool hovered)
{
	CImage& imgComp = std::get< CImage >(components);
	CText& txtComp = std::get< CText >(components);
	CTextBox& txtBoxComp =  std::get< CTextBox >(components);
	CMultiShape& multiShapeComp = std::get< CMultiShape >(components);
	CInput& inputComp = std::get< CInput >(components);
	if ( imgComp.active )
	{
		if ( imgComp.shape )
		{
			DrawCImage(imgComp, imgComp.shape, transform);
		}
		else
		{
			std::shared_ptr< NoGUI::Fill > imgFill = std::make_shared< NoGUI::Fill >();
			std::shared_ptr< NoGUI::nShape > imgShape =  std::make_shared< NoGUI::nShape >(shape->n, imgFill, nullptr); // ehhh, not the greatest solution
			DrawCImage(imgComp, imgShape, transform);
		}
	}
	if ( txtComp.active )
	{
		DrawCText(inner, txtComp, transform);
	}
	if ( txtBoxComp.active )
	{
		if ( txtBoxComp.wrap )
		{
			DrawCTextBoxWrapped(inner, txtBoxComp, transform);
		}
		else
		{
			DrawCTextBox(inner, txtBoxComp, transform);
		}
	}
	if ( multiShapeComp.active )
	{
		DrawCMultiShape(transform, multiShapeComp, hovered);
	}
	if ( inputComp.active && hovered )
	{
		if ( txtComp.active )
		{
			DrawCInput(inputComp, txtComp, inner, transform);
		}
		else if ( txtBoxComp.active )
		{
			DrawCInput(inputComp, txtBoxComp, inner, transform);
		}
	}
}

void NoGUI::DrawComponents(Element* elem)
{
	DrawComponents(elem->components->getComponents(), elem->getShape(), *(elem), elem->getInner(), elem->getHover());
}

void NoGUI::DrawElement(const NoGUI::Transform& transform, std::shared_ptr< nShape > shape, const char* inner, std::shared_ptr< NoGUI::CContainer > components, bool hovered)
{
	Vector2 center = transform.pos();
	Vector2 origin = {(float)static_cast< int >(transform.origin.x), (float)static_cast< int >(transform.origin.y)};
	origin.x *= transform.radius.x;
	origin.y *= transform.radius.y;
	switch (shape->n)
	{
		case 0:
		{
			DrawEllipseFill(shape->fill, center, transform.radius, origin, transform.angle, hovered);
			if ( components )
			{
				DrawComponents(components->getComponents(), shape, transform, inner, hovered);
			}	
			DrawEllipseOutline(shape->outline, center, transform.radius, origin, transform.angle, hovered);
			
			break;
		}
		
		case 1:
		{
			DrawPixelFill(shape->fill, Vector2Add(center, origin), hovered);
			if ( components )
			{
				DrawComponents(components->getComponents(), shape, transform, inner, hovered);
			}
			
			break;
		}
		
		case 2:
		{
			Vector2 startPos;
			Vector2 endPos;
			if ( transform.angle == 0.0f )
			{
				startPos = {center.x - transform.radius.x - origin.x, center.y - origin.y / 2};
				endPos = {center.x + transform.radius.x - origin.x, center.y - origin.y / 2};
			}
			else
			{
				float rads = transform.angle * DEG2RAD;
				// align to origin
				Vector2 leftPos = {-transform.radius.x - origin.x, -origin.y / 2};
				Vector2 rightPos = {transform.radius.x - origin.x, -origin.y / 2};
				// rotate
				startPos = Vector2Rotate(leftPos, rads);
				endPos = Vector2Rotate(rightPos, rads);
				// translate back
				startPos.x += center.x;
				startPos.y += center.y;
				endPos.x += center.x;
				endPos.y += center.y;
			}
			DrawLineFill(shape->fill, startPos, endPos, transform.radius.y, hovered);
			if ( components )
			{
				DrawComponents(components->getComponents(), shape, transform, inner, hovered);
			}
			
			break;
		}
		
		case 3:
		{
			Vector2 v1;
			Vector2 v2;
			Vector2 v3;
			if ( transform.angle == 0 )
			{
				v1 = {center.x - origin.x, center.y - origin.y - transform.radius.y};
				v2 = {center.x - origin.x - transform.radius.x, center.y - origin.y + transform.radius.y};
				v3 = {center.x - origin.x + transform.radius.x, center.y - origin.y + transform.radius.y};
			}
			else
			{
				float rads = transform.angle * DEG2RAD;
				// align to origin
				Vector2 o1 = {-origin.x, -origin.y - transform.radius.y};
				Vector2 o2 = {-origin.x - transform.radius.x, -origin.y + transform.radius.y};
				Vector2 o3 = {-origin.x + transform.radius.x, -origin.y + transform.radius.y};
				// rotate
				Vector2 v1Rotate = Vector2Rotate(o1, rads);
				Vector2 v2Rotate = Vector2Rotate(o2, rads);
				Vector2 v3Rotate = Vector2Rotate(o3, rads);
				// translate back
				v1 = {v1Rotate.x + center.x, v1Rotate.y + center.y};
				v2 = {v2Rotate.x + center.x, v2Rotate.y + center.y};
				v3 = {v3Rotate.x + center.x, v3Rotate.y + center.y};
			}
			
			DrawTriangleFill(shape->fill, v1, v2, v3, hovered);
			if ( components )
			{
				DrawComponents(components->getComponents(), shape, transform, inner, hovered);
			}
			DrawTriangleOutline(shape->outline, v1, v2, v3, hovered);
			
			break;
		}
		
		case 4:
		{
			Rectangle rect = {center.x, center.y, transform.radius.x * 2, transform.radius.y * 2};
			origin.x += transform.radius.x;
			origin.y += transform.radius.y;
			
			DrawRectangleFill(shape->fill, rect, origin, transform.angle, hovered);
			if ( components )
			{
				DrawComponents(components->getComponents(), shape, transform, inner, hovered);
			}
			DrawRectangleOutline(shape->outline, rect, origin, transform.angle, hovered);
			
			break;
		}
		
		default:
		{
			DrawPolyFill(shape->fill, shape->n, center, transform.radius, origin, transform.angle, hovered);
			if ( components )
			{
				DrawComponents(components->getComponents(), shape, transform, inner, hovered);
			}
			DrawPolyOutline(shape->outline, shape->n, center, transform.radius, origin, transform.angle, hovered);
			
			break;
		}
	}
}

void NoGUI::DrawElement(Element* elem)
{
	DrawElement(*(elem), elem->getShape(), elem->getInner(), elem->components, elem->getHover());
}

Vector2 NoGUI::Transform::pos() const
{
	
	return position;
}

Vector2 NoGUI::Transform::pos(const Align& originPoint) const
{	
	Vector2 ret = Vector2Subtract(position, offset()); // center on element
	int xdir = static_cast< int >(originPoint.x);
	int ydir = static_cast< int >(originPoint.y);
	Vector2 distance = {xdir * radius.x, ydir * radius.y};
	if ( angle == 0 )
	{
		ret = Vector2Add(ret, distance);
	}
	else
	{
		ret = Vector2Add(ret, Vector2Rotate(distance, angle * DEG2RAD));
	}
	
	return ret;
}

Vector2 NoGUI::Transform::size() const
{
	Vector2 ret = Vector2Scale(radius, 2);
	
	return ret;
}

float NoGUI::Transform::width() const
{
	
	return radius.x * 2.0f;
}

float NoGUI::Transform::height() const
{
	
	return radius.y * 2.0f;
}

Vector2 NoGUI::Transform::offset() const
{
	int xint = static_cast< int >(origin.x);
	int yint = static_cast< int >(origin.y);
	Vector2 off = {xint * radius.x, yint * radius.y};
	if ( angle == 0 )
	{
		
		return off;
	}
	else
	{
		float mag;
		float direction;
		if ( off.x == 0 )
		{
			mag = off.y;
			if ( mag > 0 )
			{
				mag *= -1;
			}
		}
		else if ( off.y == 0 )
		{
			mag = off.x;
			if ( mag > 0 )
			{
				mag *= -1;
			}
		}
		else
		{
			mag = Vector2Length(off);
			if ( mag > 0 )
			{
				mag *= -1;
			}
		}
		
		direction = atan2(off.y * -1, off.x * -1) * RAD2DEG;
		if ( direction < 0 )
		{
			direction += 360;
		}
		direction += angle;
		off = {mag * cosf(direction * DEG2RAD), mag * sinf(direction * DEG2RAD)};
		
		return off;
	}
}

float NoGUI::Transform::rotation() const
{
	
	return angle;
}
	
Vector2 NoGUI::Transform::translate(float x, float y)
{
	position.x += x;
	position.y += y;

	return position;
}
	
Vector2 NoGUI::Transform::translate(const Vector2 inc)
{
	
	return translate(inc.x, inc.y);
}
	
Vector2 NoGUI::Transform::repos(Vector2 newPos)
{
	position = newPos;

	return position;
}
	
Vector2 NoGUI::Transform::repos(Vector2 newPos, const Align& originPoint, bool update)
{
	if ( update )
	{
		origin = originPoint;
	}
	else
	{
		Vector2 translate = Vector2Subtract(pos(originPoint), position);
		newPos = Vector2Subtract(newPos, translate);
	}
	
	repos(newPos);
	
	return position;
}
	
void NoGUI::Transform::resize(const Vector2& size)
{
	radius = size;
}
	
void NoGUI::Transform::rotate(float degrees, const Align& originPoint, bool update)
{
	if ( origin.x == originPoint.x && origin.y == originPoint.y )
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

void NoGUI::Transform::rotate(float degrees, const Vector2& originPoint)
{
	angle += degrees;
	position = Vector2RotateAround(position, originPoint, degrees * DEG2RAD);
}

void NoGUI::Transform::reorient(float degrees, const Align& originPoint, bool update)
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

void NoGUI::Transform::reorient(float degrees, const Vector2& originPoint)
{
	angle = degrees;
	Vector2 temp = {position.x - originPoint.x, position.y - originPoint.y};
	Vector2 posInc = Vector2Rotate(temp, degrees * DEG2RAD);
	// translate back
	position = Vector2Add(position, posInc);
}

void Element::draw()
{
	DrawElement(this);
}

std::shared_ptr< nShape > Element::getShape()
{
	
	return shape;
}

std::shared_ptr< nShape > Element::setShape(std::shared_ptr< nShape > set)
{
	shape = set;
	
	return shape;
}

void Element::kill()
{
	alive = false;
}

bool Element::getAlive()
{
	
	return alive;
}

bool Element::isHover()
{
	Vector2 mousePos = GetMousePosition();
	hover = CheckCollisionPointShape(mousePos, shape->n, *(this));
	
	if ( components )
	{
		NoGUI::CMultiShape& multiShapeComp = components->getComponent< NoGUI::CMultiShape >();
		NoGUI::CInput& inputComp = components->getComponent< NoGUI::CInput >();
		
		if ( !hover )
		{
			if ( multiShapeComp.active && multiShapeComp.collision )
			{
				for ( std::pair< std::shared_ptr< nShape >, Transform > shape : multiShapeComp.shapes )
				{
					Vector2 center = pos(shape.second.origin);
					Vector2 offset = shape.second.pos();
					float angle = shape.second.angle;
					if ( rotation() != 0 )
					{
						offset = Vector2Rotate(offset, rotation() * DEG2RAD);
						angle += rotation();
					}
					center.x += offset.x;
					center.y += offset.y;
					NoGUI::Transform bbox = NoGUI::Transform(center, shape.second.radius, NoGUI::Align(0, 0), angle);
					if ( CheckCollisionPointShape(mousePos, shape.first->n, bbox) )
					{
						hover = true;
				
						break;
					}
				}
			}
		}
		if ( inputComp.active && hover )
		{
			collectInput(this);
		}
	}
	
	return hover;
}

bool Element::getActive()
{
	
	return active;
}

bool Element::getFocus()
{
	
	return focus;
}

bool Element::isFocus()
{
	
	return getFocus();
}

bool Element::setActive(bool set)
{
	active = set;
	
	return active;
}


bool Element::setFocus(bool set)
{
	focus = set;
	
	return focus;
}

bool Element::getHover()
{
	
	return hover;
}

bool Button::isFocus()
{
	if ( active )
	{
		focus = getHover() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
		
		return focus;
	}
	else
	{
		
		return false;
	}
}

bool Hoverable::isFocus()
{
	if ( active )
	{
		focus = getHover();
		
		return focus;
	}
	else
	{
		
		return false;
	}
}

bool Toggle::isFocus()
{
	if ( active )
	{
		if ( getHover() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
		{
			focus = !focus;
		}
		
		return focus;
	}
	else
	{
		
		return false;
	}
}

bool Trigger::isFocus()
{
	if ( active )
	{
		focus = getHover() && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
		
		return focus;
	}
	else
	{
		
		return false;
	}
}

void CheckBox::draw()
{
	if ( getFocus() )
	{
		DrawElement(this);
	}
	else
	{
		DrawShape(*(shape), *(this), hover);
	}
}

void Page::update()
{
	std::map< const NoMAD::ObjTag, std::vector< std::shared_ptr< Element > > > new_map;
	for (auto it : elements)
	{
		for (size_t elemIndex=0; elemIndex < it.second.size(); elemIndex++)
		{
			auto elem = it.second.at(elemIndex);
			if ( elem->getAlive() )
			{
				new_map[it.first.tag].push_back(elem);
			}
		}
	}
	if ( !toAdd.empty() )
	{
		for (auto add : toAdd)
		{
			if ( !add.second.empty() )
			{
				for (auto elem : add.second)
				{
					new_map[add.first.tag].push_back(elem);
				}
			}
		}
		toAdd.clear();
	}
	
	elements = new_map;
}

bool Page::getActive()
{
	
	return active;
}

bool Page::setActive(bool set)
{
	active = set;
	
	return active;
}

size_t Page::size()
{
	
	return total;
}

std::map< const NoMAD::ObjTag, std::vector< std::shared_ptr< Element > > > Page::getBody()
{
	
	return elements;
}

std::shared_ptr< Element > Page::getElement(size_t id)
{
	for (auto it=elements.begin(); it != elements.end(); it++)
	{
		for (size_t elemIndex=0; elemIndex < it->second.size(); elemIndex++)
		{
			if ( it->second.at(elemIndex)->getId() == id )
			{
				
				return it->second[elemIndex];
			}
		}
	}
	
	return nullptr;
}

std::vector< std::shared_ptr< Element > > Page::getElements(const char* tag)
{
	// don't make a new entry by using [] operator, and don't throw exception if tag is not in map
	// simply return empty vector if tag is not in map
	for (auto it=elements.begin(); it != elements.end(); it++)
	{
		int compare = strcmp(it->first.tag, tag);
		if ( compare == 0 )
		{
			
			return it->second;
		}
	}
	
	return std::vector< std::shared_ptr< Element > >();
}

// TODO: gotta be a better way to do this
std::vector< std::shared_ptr< Element > > Page::getElements()
{
	std::vector< std::shared_ptr< Element > > elems(total);
	for (auto it=elements.begin(); it != elements.end(); it++) // order by id
	{
		for (std::shared_ptr< Element > elem : it->second)
		{
			elems.at(elem->getId()) = elem;
		}
	}
	
	std::vector< std::shared_ptr< Element > > result;
	for (std::shared_ptr< Element > elem : elems) // remove dead elements
	{
		if ( elem )
		{
			result.push_back(elem);
		}
	}
	
	return result;
}

void Page::removeElement(size_t id)
{
	for (auto it=elements.begin(); it != elements.end(); it++)
	{
		for (std::shared_ptr< Element > elem : it->second)
		{
			if ( elem->getId() == id )
			{
				elem->kill();
				
				return;
			}
		}
	}
}

void Page::removeElements(const char* tag)
{
	elements.erase(tag);
}

void Page::clearElements()
{
	for (auto it=elements.begin(); it != elements.end(); it++)
	{
		for (std::shared_ptr< Element > elem : it->second)
		{
			elem->kill();
		}
	}
	total = 0;
}

// std::shared_ptr< Element > GUIManager::addElement(std::shared_ptr< nShape > style, const Transform& dimensions, const char* tag="Default", const char* inner="", size_t pageIndex=0)
// {
	
	// return pages.at(pageIndex)->addElement(style, dimensions, tag, inner);
// }

std::shared_ptr< Page > Manager::addPage(std::shared_ptr< Page > pg)
{
	pages.push_back(pg);
	
	return pages.back();
}

std::shared_ptr< Page > Manager::addPage(bool active)
{
	std::shared_ptr< Page > pg = std::shared_ptr< Page >(new Page(active));
	
	return addPage(pg);
}

std::shared_ptr< Page > Manager::addPage(std::map< const NoMAD::ObjTag, std::shared_ptr< CContainer > > comps, bool active)
{
	std::shared_ptr< Page > pg = std::shared_ptr< Page >(new Page(comps, active));
	
	return addPage(pg);
}

std::shared_ptr< Page > Manager::getPage(size_t pageIndex)
{
	
	return pages.at(pageIndex);
}

std::vector< std::shared_ptr< Page > > Manager::getPages()
{
	
	return pages;
}

size_t Manager::size()
{
	
	return pages.size();
}

void Manager::removePage(size_t pageIndex)
{
	pages.erase(pages.begin() + pageIndex);
}

//void GUIManager::removeElement(size_t id, size_t pageIndex)
//{
//	
//}

void Manager::clear()
{
	pages.clear();
}

void Manager::update()
{
	for (auto pageIt=pages.rbegin(); pageIt != pages.rend(); pageIt++)
	{
		std::shared_ptr< Page > page = *(pageIt);
		page->update();
		if ( page->getActive() )
		{
			std::vector< std::shared_ptr< NoGUI::Element > > elements = page->getElements();
			for (auto elemIt=elements.rbegin(); elemIt != elements.rend(); elemIt++)
			{
				//elem->isHover();
				std::shared_ptr< Element > elem = *(elemIt);
//				bool prevHover = elem->getHover();
				bool prevFocus = elem->getFocus();
				elem->isHover();
				elem->isFocus();
				int event = 0;
				if ( !prevFocus )
				{
					if ( elem->getFocus() )
					{
						if ( !onFocus )
						{
							event = ONFOCUS;
							onFocus = true;
						}
					}
				}
				else
				{
					if ( elem->getFocus() )
					{
						event = FOCUSING;
					}
					else
					{
						event = OFFFOCUS;
					}
				}
				if ( event )
				{
					notify(elem, static_cast<Event>(event));
				}
			}
		}
	}
	onFocus = false;
}

void Manager::render()
{
	for (auto page : pages)
	{
		if ( page->getActive() )
		{
			for (auto elem : page->getElements())
			{
				elem->draw();
			}
		}
	}
}

void Manager::setActive(size_t index)
{
	for (auto page : pages)
	{
		page->setActive(false);
	}
	pages.at(index)->setActive(true);
}

void ManagerGrid::update()
{
	for (auto pageIt=pages.rbegin(); pageIt != pages.rend(); pageIt++)
	{
		std::shared_ptr< Page > page = *(pageIt);
		page->update();
		if ( page->getActive() )
		{
			std::vector< std::shared_ptr< NoGUI::Element > > elements = page->getElements();
			for (auto elemIt=elements.rbegin(); elemIt != elements.rend(); elemIt++)
			{
				//elem->isHover();
				std::shared_ptr< Element > elem = *(elemIt);
				Transform transform = Transform(Vector2Multiply(elem->pos(), cellSize), Vector2Multiply(elem->radius, cellSize), elem->origin, elem->angle);
//				bool prevHover = elem->getHover();
				bool prevFocus = elem->getFocus();
//				elem->isHover();
				Vector2 mousePos = GetMousePosition();
				elem->hover = CheckCollisionPointShape(mousePos, elem->getShape()->n, transform);
				if ( elem->components )
				{
					CMultiShape& multiShapeComp = elem->components->getComponent< CMultiShape >();
					NoGUI::CInput& inputComp = elem->components->getComponent< NoGUI::CInput >();
					if ( !elem->getHover() )
					{
						if ( multiShapeComp.active && multiShapeComp.collision )
						{
							for ( std::pair< std::shared_ptr< nShape >, Transform > shape : multiShapeComp.shapes )
							{
								Vector2 center = elem->pos(shape.second.origin);
								Vector2 offset = shape.second.pos();
								float angle = shape.second.angle;
								if ( elem->rotation() != 0 )
								{
									offset = Vector2Rotate(offset, elem->rotation() * DEG2RAD);
									angle += elem->rotation();
								}
								center.x += offset.x;
								center.y += offset.y;
								NoGUI::Transform bbox = NoGUI::Transform(Vector2Multiply(center, cellSize), Vector2Multiply(shape.second.radius, cellSize), NoGUI::Align(0, 0), angle);
								if ( CheckCollisionPointShape(mousePos, shape.first->n, bbox) )
								{
									elem->hover = true;
				
									break;
								}
							}
						}
					}
					if ( elem->getHover() && inputComp.active )
					{
						collectInput(elem.get());
					}
				}
				elem->isFocus();
				int event = 0;
				if ( !prevFocus )
				{
					if ( elem->getFocus() )
					{
						if ( !onFocus )
						{
							event = ONFOCUS;
							onFocus = true;
						}
					}
				}
				else
				{
					if ( elem->getFocus() )
					{
						event = FOCUSING;
					}
					else
					{
						event = OFFFOCUS;
					}
				}
				if ( event )
				{
					notify(elem, static_cast<Event>(event));
				}
			}
		}
	}
	onFocus = false;
}

void ManagerGrid::render()
{
	for (auto page : pages)
	{
		if ( page->getActive() )
		{
			for (auto elem : page->getElements())
			{
				Transform transform = Transform(Vector2Multiply(elem->pos(), cellSize), Vector2Multiply(elem->radius, cellSize), elem->origin, elem->angle);
				std::shared_ptr< NoGUI::nShape > shape = elem->getShape();
				//DrawElement(transform, shape, elem->getInner(), elem->components, elem->getHover());
				// TODO: the following is a slower but cleaner way of drawing the Element. It can be optimized.
				DrawShapeFill(shape->n, shape->fill, transform, elem->getHover());
				if ( elem->components )
				{
					// transforms in the multishape component need to follow the grid sizing
					if ( elem->components->getComponent< CMultiShape >().active )
					{
						CMultiShape& multiShape = elem->components->getComponent< CMultiShape >();
						multiShape.active = false; // manually draw the MultiShape Component
						DrawComponents(elem->components->getComponents(), elem->getShape(), transform, elem->getInner(), elem->getHover());
						for ( std::pair< std::shared_ptr< nShape >, Transform > shape : multiShape.shapes )
						{
							Transform shapeTransform = shape.second;
							shapeTransform.position = Vector2Multiply(shapeTransform.position, cellSize); // grid scaling
							shapeTransform.radius = Vector2Multiply(shapeTransform.radius, cellSize); // grid scaling
							Vector2 center = transform.pos(shapeTransform.origin);
							Vector2 offset = shapeTransform.pos();
							float angle = shapeTransform.angle;
							if ( transform.angle != 0 )
							{
								offset = Vector2Rotate(offset, transform.angle * DEG2RAD);
								angle += transform.angle;
							}
							center.x += offset.x;
							center.y += offset.y;
							
							DrawShape(*(shape.first), center, shapeTransform.radius, (Vector2){0, 0}, angle, elem->getHover());
						}
						multiShape.active = true;
					}
					else
					{
						DrawComponents(elem->components->getComponents(), elem->getShape(), transform, elem->getInner(), elem->getHover());
					}
				}
				DrawShapeOutline(shape->n, shape->outline, transform, elem->getHover());
			}
		}
	}
}

void ManagerGrid::drawCells(const Color& col)
{
	for (float x=cellSize.x; x < GetScreenWidth(); x+=cellSize.x)
	{
		DrawLine(x, 0, x, GetScreenHeight(), col);
	}
	for (float y=cellSize.y; y < GetScreenHeight(); y+=cellSize.y)
	{
		DrawLine(0, y, GetScreenWidth(), y, col);
	}
}

Vector2 ManagerGrid::getCellSize()
{
	
	return cellSize;
}

void ManagerGrid::setCellSize(float newSize)
{
	cellSize = (Vector2){newSize, newSize};
}

void ManagerGrid::setCellSize(float x, float y)
{
	cellSize = (Vector2){x, y};
}