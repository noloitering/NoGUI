#include "GUI.h"

using namespace NoGUI;

void NoGUI::DrawShape(const nShape& shape, Vector2 center, Vector2 radius, Vector2 origin, float angle)
{
	switch (shape.n)
	{
		case 0:
		{
			DrawEllipsePro(center, radius, origin, angle, shape.fill->col);
			if ( shape.outline )
			{
				DrawEllipseLinesPro(center, radius, origin, angle, shape.outline->thick, shape.outline->fill->col);
			}
			
			break;
		}
		
		case 1:
		{
			DrawPixel(center.x, center.y, shape.fill->col);
			
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
				float sinRotation = sinf(angle*DEG2RAD);
				float cosRotation = cosf(angle*DEG2RAD);
				// align to origin
				Vector2 leftPos = {-radius.x - origin.x, -origin.y / 2};
				Vector2 rightPos = {radius.x - origin.x, -origin.y / 2};
				// rotate
				startPos.x = leftPos.x * cosRotation - leftPos.y * sinRotation;
				startPos.y = leftPos.x * sinRotation + leftPos.y * cosRotation;
				endPos.x = rightPos.x * cosRotation - rightPos.y * sinRotation;
				endPos.y = rightPos.x * sinRotation + rightPos.y * cosRotation;
				// translate back
				startPos.x += center.x;
				startPos.y += center.y;
				endPos.x += center.x;
				endPos.y += center.y;
			}
			
			DrawLineEx(startPos, endPos, radius.y, shape.fill->col);
			
			break;
		}
		
		case 3:
		{
			
			
			break;
		}
		
		case 4:
		{
			Rectangle rect = {center.x, center.y, radius.x * 2, radius.y * 2};
			origin.x += radius.x;
			origin.y += radius.y;
			DrawRectanglePro(rect, origin, angle, shape.fill->col);
			if ( shape.outline )
			{
				DrawRectangleLinesPro(rect, origin, angle, shape.outline->thick, shape.outline->fill->col);
			}
			
			break;
		}
		
		default:
		{
			DrawPolyPro(center, shape.n, radius, origin, angle, shape.fill->col);
			if ( shape.outline )
			{
				DrawPolyLinesPro(center, shape.n, radius, origin, angle, shape.outline->thick, shape.outline->fill->col);
			}
			
			break;
		}
	}
}

void NoGUI::DrawShape(const nShape& shape, const NoGUI::Transform& transform)
{
	DrawShape(shape, transform.pos(), transform.radius, transform.offset(), transform.rotation());
}


void NoGUI::DrawElement(Element* elem)
{
	std::shared_ptr< NoGUI::nShape > shape = elem->style();
	DrawShape(*(shape.get()), *(elem));
}

void Element::draw()
{
//	DrawShape(transform, *(shape.get()));
	DrawElement(this);
}

bool Element::getFocus()
{
	
	return focus;
}

bool Element::getActive()
{
	
	return active;
}

std::shared_ptr< nShape > Element::style()
{
	
	return shape;
}

// void NoGUI::DrawPolyEx(Vector2 center, int sides, Vector2 radius, float angle, Color col)
// {
    // if (sides < 3) sides = 3;
    // float centralAngle = 0.0f;

// #if defined(SUPPORT_QUADS_DRAW_MODE)
    // rlCheckRenderBatchLimit(4*sides); // Each side is a quad
// #else
    // rlCheckRenderBatchLimit(3*sides);
// #endif

    // rlPushMatrix();
        // rlTranslatef(center.x, center.y, 0.0f);
        // rlRotatef(angle, 0.0f, 0.0f, 1.0f);

// #if defined(SUPPORT_QUADS_DRAW_MODE)
		// rlSetTexture(texShapes.id);

		// rlBegin(RL_QUADS);
			// for (int i = 0; i < sides; i++)
			// {
				// rlColor4ub(col.r, col.g, col.b, col.a);

				// rlTexCoord2f(texShapesRec.x/texShapes.width, texShapesRec.y/texShapes.height);
				// rlVertex2f(0, 0);

				// rlTexCoord2f(texShapesRec.x/texShapes.width, (texShapesRec.y + texShapesRec.height)/texShapes.height);
				// rlVertex2f(sinf(DEG2RAD*centralAngle)*radius.x, cosf(DEG2RAD*centralAngle)*radius.y);

				// rlTexCoord2f((texShapesRec.x + texShapesRec.width)/texShapes.width, (texShapesRec.y + texShapesRec.height)/texShapes.height);
				// rlVertex2f(sinf(DEG2RAD*centralAngle)*radius.x, cosf(DEG2RAD*centralAngle)*radius.y);

				// centralAngle += 360.0f/(float)sides;
				// rlTexCoord2f((texShapesRec.x + texShapesRec.width)/texShapes.width, texShapesRec.y/texShapes.height);
				// rlVertex2f(sinf(DEG2RAD*centralAngle)*radius.x, cosf(DEG2RAD*centralAngle)*radius.y);
			// }
		// rlEnd();
		// rlSetTexture(0);
// #else
		// rlBegin(RL_TRIANGLES);
			// for (int i = 0; i < sides; i++)
			// {
				// rlColor4ub(col.r, col.g, col.b, col.a);

				// rlVertex2f(0, 0);
				// rlVertex2f(sinf(DEG2RAD*centralAngle)*radius.x, cosf(DEG2RAD*centralAngle)*radius.y);

				// centralAngle += 360.0f/(float)sides;
				// rlVertex2f(sinf(DEG2RAD*centralAngle)*radius.x, cosf(DEG2RAD*centralAngle)*radius.y);
			// }
			// rlEnd();
// #endif
	// rlPopMatrix();
// }

// void NoGUI::DrawPolyPro(Vector2 center, int sides, Vector2 radius, Vector2 origin, float angle, Color col)
// {
    // if (sides < 3) sides = 3;
    // float centralAngle = 0.0f;
	// if ( angle == 0 )
	// {
		// center.x -= origin.x;
		// center.y -= origin.y;
	// }
	// else
	// {
		// float sinRotation = sinf(angle*DEG2RAD);
		// float cosRotation = cosf(angle*DEG2RAD);
		// Vector2 pivot = {center.x + origin.x, center.y + origin.y};
		// Vector2 newPos = center;
		// Vector2 finalPos;
		// newPos.x -= pivot.x;
		// newPos.y -= pivot.y;
			
		// finalPos.x = newPos.x * cosRotation - newPos.y * sinRotation;
		// finalPos.y = newPos.x * sinRotation + newPos.y * cosRotation;
				
		// center.x += finalPos.x;
		// center.y += finalPos.y;
	// }
// #if defined(SUPPORT_QUADS_DRAW_MODE)
    // rlCheckRenderBatchLimit(4*sides); // Each side is a quad
// #else
    // rlCheckRenderBatchLimit(3*sides);
// #endif

    // rlPushMatrix();
        // rlTranslatef(center.x, center.y, 0.0f);
        // rlRotatef(angle, 0.0f, 0.0f, 1.0f);

		// rlBegin(RL_TRIANGLES);
			// for (int i = 0; i < sides; i++)
			// {
				// rlColor4ub(col.r, col.g, col.b, col.a);

				// rlVertex2f(0, 0);
				// rlVertex2f(sinf(DEG2RAD*centralAngle)*radius.x, cosf(DEG2RAD*centralAngle)*radius.y);

				// centralAngle += 360.0f/(float)sides;
				// rlVertex2f(sinf(DEG2RAD*centralAngle)*radius.x, cosf(DEG2RAD*centralAngle)*radius.y);
			// }
		// rlEnd();
	// rlPopMatrix();
// }

// void NoGUI::DrawEllipsePro(Vector2 center, Vector2 radius, Vector2 origin, float angle, Color col)
// {
	// if ( angle == 0 )
	// {
		// center.x -= origin.x;
		// center.y -= origin.y;
	// }
	// else
	// {
		// float sinRotation = sinf(angle*DEG2RAD);
		// float cosRotation = cosf(angle*DEG2RAD);
		// Vector2 pivot = {center.x + origin.x, center.y + origin.y};
		// Vector2 newPos = center;
		// Vector2 finalPos;
		// newPos.x -= pivot.x;
		// newPos.y -= pivot.y;
			
		// finalPos.x = newPos.x * cosRotation - newPos.y * sinRotation;
		// finalPos.y = newPos.x * sinRotation + newPos.y * cosRotation;
				
		// center.x += finalPos.x;
		// center.y += finalPos.y;
	// }
	
	// rlCheckRenderBatchLimit(3*36);
	
	// rlPushMatrix();
		// rlTranslatef(center.x, center.y, 0.0f);
		// rlRotatef(angle, 0.0f, 0.0f, 1.0f);
		
		// rlBegin(RL_TRIANGLES);
			// for (int i = 0; i < 360; i += 10)
			// {
				// rlColor4ub(col.r, col.g, col.b, col.a);
				
				// rlVertex2f(0, 0);
				// rlVertex2f(sinf(DEG2RAD*i)*radius.x, cosf(DEG2RAD*i)*radius.y);
				
				// rlVertex2f(sinf(DEG2RAD*(i + 10))*radius.x, cosf(DEG2RAD*(i + 10))*radius.y);
			// }
		// rlEnd();
	// rlPopMatrix();
// }
