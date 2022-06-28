#include "GUI.h"

using namespace NoGUI;

void NoGUI::DrawShapeCenter(int posX, int posY, float radiusH, float radiusV, const Shape& shape, float angle)
{
	switch (shape.sides)
	{
		case 0:
		{
			DrawElipsePro(posX, posY, radiusH, radiusV, angle, shape.fill->col);
				
			break;
		}
		
		case 1:
		{
			DrawPixel(posX, posY, shape.fill->col);
			
			break;
		}
		
		case 2:
		{
			Vector2 startPos;
			Vector2 endPos;
			if ( angle == 0.0f )
			{
				startPos = {posX - radiusH, (float)posY};
				endPos = {posX + radiusH, (float)posY};
			}
			else
			{
				startPos = {-1 * radiusH, 0};
				endPos = {radiusH, 0};
				
				startPos.x = cosf(DEG2RAD * angle) * startPos.x - sinf(DEG2RAD * angle) * startPos.y;
				startPos.y = sinf(DEG2RAD * angle) * startPos.x + cosf(DEG2RAD * angle) * startPos.y;				
				endPos.x = cosf(DEG2RAD * angle) * endPos.x - sinf(DEG2RAD * angle) * endPos.y;
				endPos.y = sinf(DEG2RAD * angle) * endPos.x + cosf(DEG2RAD * angle) * endPos.y;
				
				startPos.x += posX;
				startPos.y += posY;
				endPos.x += posX;
				endPos.y += posY;
			}
				
			DrawLineEx(startPos, endPos, radiusV, shape.fill->col);
				
			break;
		}
			
		case 3:
		{
			Vector2 posV = {float(posX), float(posY)};
			Vector2 radius = {radiusH , radiusV};
			angle += 180;
				
			DrawPolyEx(posV, shape.sides, radius, angle, shape.fill->col);
				
			break;
		}
			
		case 4:
		{
			Rectangle render = (Rectangle){posX - radiusH, posY - radiusV, radiusH * 2, radiusV * 2};
			Vector2 origin = {0, 0};
			DrawRectanglePro(render, origin, angle, shape.fill->col);
			
			break;
		}
		
		default:
		{
			Vector2 posV = {float(posX), float(posY)};
			Vector2 radius = {radiusH , radiusV};
				
			DrawPolyEx(posV, shape.sides, radius, angle, shape.fill->col);
			
			break;
		}
	}
}

void NoGUI::DrawShapeCenter(const Vector2& pos, const Vector2& radius, const Shape& shape, float angle)
{
	DrawShapeCenter(pos.x, pos.y, radius.x, radius.y, shape, angle);
}

void NoGUI::DrawShapeLeft(int posX, int posY, float radiusH, float radiusV, const Shape& shape, float angle)
{
	// TODO: 2 sides/line case
	if ( shape.sides == 2 )
	{
		posX += radiusH;
		posY += radiusV / 2;
	}
	else
	{
		posX += radiusH;
		posY += radiusV;
	}
	
	DrawShapeCenter(posX, posY, radiusH, radiusV, shape, angle);
}

void NoGUI::DrawShapeLeft(const Vector2& pos, const Vector2& radius, const Shape& shape, float angle)
{
	DrawShapeLeft(pos.x, pos.y, radius.x, radius.y, shape, angle);
}

void NoGUI::DrawShapeRight(int posX, int posY, float radiusH, float radiusV, const Shape& shape, float angle)
{
	// TODO: 2 sides/line case
	if ( shape.sides == 2 )
	{
		posX -= radiusH;
		posY += radiusV / 2;
	}
	else
	{
		posX -= radiusH;
		posY += radiusV;
	}
	
	DrawShapeCenter(posX, posY, radiusH, radiusV, shape, angle);
}

void NoGUI::DrawShapeRight(const Vector2& pos, const Vector2& radius, const Shape& shape, float angle)
{
	DrawShapeRight(pos.x, pos.y, radius.x, radius.y, shape, angle);
}

void NoGUI::DrawShapeTop(int posX, int posY, float radiusH, float radiusV, const Shape& shape, float angle)
{
	// TODO: 2 sides/line case
	if ( shape.sides == 2 )
	{
		posY += radiusV / 2;
	}
	else
	{
		posY += radiusV;
	}
	
	DrawShapeCenter(posX, posY, radiusH, radiusV, shape, angle);
}

void NoGUI::DrawShapeTop(const Vector2& pos, const Vector2& radius, const Shape& shape, float angle)
{
	DrawShapeTop(pos.x, pos.y, radius.x, radius.y, shape, angle);
}

void NoGUI::DrawShapeBottom(int posX, int posY, float radiusH, float radiusV, const Shape& shape, float angle)
{
	// TODO: 2 sides/line case
	if ( shape.sides == 2 )
	{
		posY -= radiusV / 2;
	}
	else
	{
		posY -= radiusV;
	}
	
	DrawShapeCenter(posX, posY, radiusH, radiusV, shape, angle);
}

void NoGUI::DrawShapeBottom(const Vector2& pos, const Vector2& radius, const Shape& shape, float angle)
{
	DrawShapeBottom(pos.x, pos.y, radius.x, radius.y, shape, angle);
}

void NoGUI::DrawShapeBottomL(int posX, int posY, float radiusH, float radiusV, const Shape& shape, float angle)
{
	// TODO: 2 sides/line case
	if ( shape.sides == 2 )
	{
		posX += radiusH;
		posY -= radiusV / 2;
	}
	else
	{
		posX += radiusH;
		posY -= radiusV;
	}
	
	DrawShapeCenter(posX, posY, radiusH, radiusV, shape, angle);
}

void NoGUI::DrawShapeBottomL(const Vector2& pos, const Vector2& radius, const Shape& shape, float angle)
{
	DrawShapeBottomL(pos.x, pos.y, radius.x, radius.y, shape, angle);
}

void NoGUI::DrawShapeBottomR(int posX, int posY, float radiusH, float radiusV, const Shape& shape, float angle)
{
	if ( shape.sides == 2 )
	{
		posX -= radiusH;
		posY -= radiusV / 2;
	}
	else
	{
		posX -= radiusH;
		posY -= radiusV;
	}
	
	DrawShapeCenter(posX, posY, radiusH, radiusV, shape, angle);
}

void NoGUI::DrawShapeBottomR(const Vector2& pos, const Vector2& radius, const Shape& shape, float angle)
{
	DrawShapeBottomR(pos.x, pos.y, radius.x, radius.y, shape, angle);
}

void NoGUI::DrawShape(int posX, int posY, float radiusH, float radiusV, const Shape& shape, const NoGUI::Align& origin, float angle)
{
	switch (origin)
	{
		case Align::LEFT:
		{
			DrawShapeLeft(posX, posY, radiusH, radiusV, shape, angle);
		}
		
		case Align::CENTER:
		{
			DrawShapeCenter(posX, posY, radiusH, radiusV, shape, angle);
		}
		
		case Align::RIGHT:
		{
			DrawShapeRight(posX, posY, radiusH, radiusV, shape, angle);
		}
		
		case Align::TOP:
		{
			DrawShapeTop(posX, posY, radiusH, radiusV, shape, angle);
		}
		
		case Align::BOTTOML:
		{
			DrawShapeBottomL(posX, posY, radiusH, radiusV, shape, angle);
		}
		
		case Align::BOTTOM:
		{
			DrawShapeBottom(posX, posY, radiusH, radiusV, shape, angle);
		}
		
		case Align::BOTTOMR:
		{
			DrawShapeBottomR(posX, posY, radiusH, radiusV, shape, angle);
		}
	}
}

void NoGUI::DrawShape(const Vector2& pos, const Vector2& radius, const Shape& shape, const Align& origin, float angle)
{
	DrawShape(pos.x, pos.y, radius.x, radius.y, shape, origin, angle);
}

void NoGUI::DrawShape(const Transform& transform, const Shape& shape)
{
	DrawShape(transform.pos.x, transform.pos.y, transform.radius.x, transform.radius.y, shape, transform.origin, transform.angle);
}

void NoGUI::DrawPolyEx(Vector2 center, int sides, Vector2 radius, float angle, Color col)
{
    if (sides < 3) sides = 3;
    float centralAngle = 0.0f;

#if defined(SUPPORT_QUADS_DRAW_MODE)
    rlCheckRenderBatchLimit(4*sides); // Each side is a quad
#else
    rlCheckRenderBatchLimit(3*sides);
#endif

    rlPushMatrix();
        rlTranslatef(center.x, center.y, 0.0f);
        rlRotatef(angle, 0.0f, 0.0f, 1.0f);

#if defined(SUPPORT_QUADS_DRAW_MODE)
		rlSetTexture(texShapes.id);

		rlBegin(RL_QUADS);
			for (int i = 0; i < sides; i++)
			{
				rlColor4ub(col.r, col.g, col.b, col.a);

				rlTexCoord2f(texShapesRec.x/texShapes.width, texShapesRec.y/texShapes.height);
				rlVertex2f(0, 0);

				rlTexCoord2f(texShapesRec.x/texShapes.width, (texShapesRec.y + texShapesRec.height)/texShapes.height);
				rlVertex2f(sinf(DEG2RAD*centralAngle)*radius.x, cosf(DEG2RAD*centralAngle)*radius.y);

				rlTexCoord2f((texShapesRec.x + texShapesRec.width)/texShapes.width, (texShapesRec.y + texShapesRec.height)/texShapes.height);
				rlVertex2f(sinf(DEG2RAD*centralAngle)*radius.x, cosf(DEG2RAD*centralAngle)*radius.y);

				centralAngle += 360.0f/(float)sides;
				rlTexCoord2f((texShapesRec.x + texShapesRec.width)/texShapes.width, texShapesRec.y/texShapes.height);
				rlVertex2f(sinf(DEG2RAD*centralAngle)*radius.x, cosf(DEG2RAD*centralAngle)*radius.y);
			}
		rlEnd();
		rlSetTexture(0);
#else
		rlBegin(RL_TRIANGLES);
			for (int i = 0; i < sides; i++)
			{
				rlColor4ub(col.r, col.g, col.b, col.a);

				rlVertex2f(0, 0);
				rlVertex2f(sinf(DEG2RAD*centralAngle)*radius.x, cosf(DEG2RAD*centralAngle)*radius.y);

				centralAngle += 360.0f/(float)sides;
				rlVertex2f(sinf(DEG2RAD*centralAngle)*radius.x, cosf(DEG2RAD*centralAngle)*radius.y);
			}
			rlEnd();
#endif
	rlPopMatrix();
}

void NoGUI::DrawElipsePro(int centerX, int centerY, float radiusH, float radiusV, float angle, Color col)
{
	rlCheckRenderBatchLimit(3*36);
	
	rlPushMatrix();
		rlTranslatef(centerX, centerY, 0.0f);
		rlRotatef(angle, 0.0f, 0.0f, 1.0f);
		
		rlBegin(RL_TRIANGLES);
			for (int i = 0; i < 360; i += 10)
			{
				rlColor4ub(col.r, col.g, col.b, col.a);
				
				rlVertex2f(0, 0);
				rlVertex2f(sinf(DEG2RAD*i)*radiusH, cosf(DEG2RAD*i)*radiusV);
				
				rlVertex2f(sinf(DEG2RAD*(i + 10))*radiusH, cosf(DEG2RAD*(i + 10))*radiusV);
			}
		rlEnd();
	rlPopMatrix();
}
