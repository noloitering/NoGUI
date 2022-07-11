#include "GUI.h"

using namespace NoGUI;

void NoGUI::DrawShapeCenter(int posX, int posY, float radiusH, float radiusV, const Shape& shape, float angle)
{
	switch (shape.sides)
	{
		case 0:
		{
			Vector2 pos = {(float)posX, (float)posY};
			Vector2 radius = {radiusH, radiusV};
			Vector2 origin = {0, 0};
			
			DrawElipsePro(pos, radius, origin, angle, shape.fill->col);
				
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
				// center on origin
				Vector2 leftPos = {-1 * radiusH, 0};
				Vector2 rightPos = {radiusH, 0};
				// calculate values
				float sinRotation = sinf(angle*DEG2RAD);
				float cosRotation = cosf(angle*DEG2RAD);
				
				startPos.x = leftPos.x * cosRotation - leftPos.y * sinRotation;
				startPos.y = leftPos.x * sinRotation + leftPos.y * cosRotation;				
				endPos.x = rightPos.x * cosRotation - rightPos.y * sinRotation;
				endPos.y = rightPos.x * sinRotation + rightPos.y * cosRotation;
				// translate back
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
			Vector2 top;
			Vector2 left;
			Vector2 right;
			if ( angle == 0 )
			{
				top = (Vector2){(float)posX, posY - radiusV};
				left = (Vector2){posX - radiusH, posY + radiusV};
				right = (Vector2){posX + radiusH, posY + radiusV};
			}
			else
			{
				// center on origin
				Vector2 topInc = (Vector2){0, -radiusV};
				Vector2 leftInc = (Vector2){-radiusH, radiusV};
				Vector2 rightInc = (Vector2){radiusH, radiusV};
				// calculate values
				float sinRotation = sinf(angle*DEG2RAD);
				float cosRotation = cosf(angle*DEG2RAD);
				
				top.x = topInc.x * cosRotation - topInc.y * sinRotation;
				top.y = topInc.x * sinRotation + topInc.y * cosRotation;
				left.x = leftInc.x * cosRotation - leftInc.y * sinRotation;
				left.y = leftInc.x * sinRotation + leftInc.y * cosRotation;
				right.x = rightInc.x * cosRotation - rightInc.y * sinRotation;
				right.y = rightInc.x * sinRotation + rightInc.y * cosRotation;
				// translate back
				top.x += posX;
				top.y += posY;
				left.x += posX;
				left.y += posY;
				right.x += posX;
				right.y += posY;
			}
			
			DrawTriangle(top, left, right, shape.fill->col);
				
			break;
		}
			
		case 4:
		{
			Rectangle render = (Rectangle){(float)posX, (float)posY, radiusH * 2, radiusV * 2};
			Vector2 origin = {radiusH, radiusV};
			DrawRectanglePro(render, origin, angle, shape.fill->col);
			
			break;
		}
		
		default:
		{
			Vector2 posV = {float(posX), float(posY)};
			Vector2 radius = {radiusH , radiusV};
			Vector2 origin = {0, 0};

			DrawPolyPro(posV, shape.sides, radius, origin, angle, shape.fill->col);
			
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
	switch (shape.sides)
	{
		case 0:
		{
			Vector2 pos = {(float)posX, (float)posY};
			Vector2 radius = {radiusH, radiusV};
			Vector2 origin = {-radiusH, -radiusV};
			
			DrawElipsePro(pos, radius, origin, angle, shape.fill->col);
				
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
				startPos = {(float)posX, posY + radiusV / 2};
				endPos = {posX + radiusH * 2, posY + radiusV / 2};
			}
			else
			{
				// center on origin
				Vector2 leftPos = {0, radiusV / 2};
				Vector2 rightPos = {radiusH * 2, radiusV / 2};
				// calculate values
				float sinRotation = sinf(angle*DEG2RAD);
				float cosRotation = cosf(angle*DEG2RAD);
				
				startPos.x = leftPos.x * cosRotation - leftPos.y * sinRotation;
				startPos.y = leftPos.x * sinRotation + leftPos.y * cosRotation;				
				endPos.x = rightPos.x * cosRotation - rightPos.y * sinRotation;
				endPos.y = rightPos.x * sinRotation + rightPos.y * cosRotation;
				// translate back
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
			Vector2 top;
			Vector2 left;
			Vector2 right;
			if ( angle == 0 )
			{
				top = (Vector2){(float)posX + radiusH, (float)posY};
				left = (Vector2){(float)posX, (float)posY + radiusV * 2};
				right = (Vector2){(float)posX + radiusH * 2, posY + radiusV * 2};
			}
			else
			{
				// center on origin
				Vector2 topInc = (Vector2){radiusH, 0};
				Vector2 leftInc = (Vector2){0, radiusV * 2};
				Vector2 rightInc = (Vector2){radiusH * 2, radiusV * 2};
				// calculate values
				float sinRotation = sinf(angle*DEG2RAD);
				float cosRotation = cosf(angle*DEG2RAD);
				
				top.x = topInc.x * cosRotation - topInc.y * sinRotation;
				top.y = topInc.x * sinRotation + topInc.y * cosRotation;
				left.x = leftInc.x * cosRotation - leftInc.y * sinRotation;
				left.y = leftInc.x * sinRotation + leftInc.y * cosRotation;
				right.x = rightInc.x * cosRotation - rightInc.y * sinRotation;
				right.y = rightInc.x * sinRotation + rightInc.y * cosRotation;
				// translate back
				top.x += posX;
				top.y += posY;
				left.x += posX;
				left.y += posY;
				right.x += posX;
				right.y += posY;
			}
			
			DrawTriangle(top, left, right, shape.fill->col);
				
			break;
		}
			
		case 4:
		{
			Rectangle render = (Rectangle){(float)posX, (float)posY, radiusH * 2, radiusV * 2};
			Vector2 origin = {0, 0};
			DrawRectanglePro(render, origin, angle, shape.fill->col);
			
			break;
		}
		
		default:
		{
			Vector2 posV = {float(posX), float(posY)};
			Vector2 radius = {radiusH , radiusV};
			Vector2 origin = {-radiusH, -radiusV};
				
			DrawPolyPro(posV, shape.sides, radius, origin, angle, shape.fill->col);
			
			break;
		}
	}
}

void NoGUI::DrawShapeLeft(const Vector2& pos, const Vector2& radius, const Shape& shape, float angle)
{
	DrawShapeLeft(pos.x, pos.y, radius.x, radius.y, shape, angle);
}

void NoGUI::DrawShapeRight(int posX, int posY, float radiusH, float radiusV, const Shape& shape, float angle)
{
	switch (shape.sides)
	{
		case 0:
		{
			Vector2 pos = {(float)posX, (float)posY};
			Vector2 radius = {radiusH, radiusV};
			Vector2 origin = {radiusH, -radiusV};
			
			DrawElipsePro(pos, radius, origin, angle, shape.fill->col);
				
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
				startPos = {posX + radiusH * -2, posY + radiusV / 2};
				endPos = {(float)posX, posY + radiusV / 2};
			}
			else
			{
				// center on origin
				Vector2 leftPos = {radiusH * -2, radiusV / 2};
				Vector2 rightPos = {0, radiusV / 2};
				// calculate values
				float sinRotation = sinf(angle*DEG2RAD);
				float cosRotation = cosf(angle*DEG2RAD);
				
				startPos.x = leftPos.x * cosRotation - leftPos.y * sinRotation;
				startPos.y = leftPos.x * sinRotation + leftPos.y * cosRotation;				
				endPos.x = rightPos.x * cosRotation - rightPos.y * sinRotation;
				endPos.y = rightPos.x * sinRotation + rightPos.y * cosRotation;
				// translate back
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
			Vector2 top;
			Vector2 left;
			Vector2 right;
			if ( angle == 0 )
			{
				top = (Vector2){(float)posX - radiusH, (float)posY};
				left = (Vector2){posX - radiusH * 2, (float)posY + radiusV * 2};
				right = (Vector2){(float)posX, posY + radiusV * 2};
			}
			else
			{
				// center on origin
				Vector2 topInc = (Vector2){-radiusH, 0};
				Vector2 leftInc = (Vector2){-radiusH * 2, radiusV * 2};
				Vector2 rightInc = (Vector2){0, radiusV * 2};
				// calculate values
				float sinRotation = sinf(angle*DEG2RAD);
				float cosRotation = cosf(angle*DEG2RAD);
				
				top.x = topInc.x * cosRotation - topInc.y * sinRotation;
				top.y = topInc.x * sinRotation + topInc.y * cosRotation;
				left.x = leftInc.x * cosRotation - leftInc.y * sinRotation;
				left.y = leftInc.x * sinRotation + leftInc.y * cosRotation;
				right.x = rightInc.x * cosRotation - rightInc.y * sinRotation;
				right.y = rightInc.x * sinRotation + rightInc.y * cosRotation;
				// translate back
				top.x += posX;
				top.y += posY;
				left.x += posX;
				left.y += posY;
				right.x += posX;
				right.y += posY;
			}
			
			DrawTriangle(top, left, right, shape.fill->col);
				
			break;
		}
			
		case 4:
		{
			Rectangle render = (Rectangle){(float)posX, (float)posY, radiusH * 2, radiusV * 2};
			Vector2 origin = {radiusH * 2, 0};
			DrawRectanglePro(render, origin, angle, shape.fill->col);
			
			break;
		}
		
		default:
		{
			Vector2 posV = {float(posX), float(posY)};
			Vector2 radius = {radiusH , radiusV};
			Vector2 origin = {radiusH, -radiusV};
				
			DrawPolyPro(posV, shape.sides, radius, origin, angle, shape.fill->col);
			
			break;
		}
	}
}

void NoGUI::DrawShapeRight(const Vector2& pos, const Vector2& radius, const Shape& shape, float angle)
{
	DrawShapeRight(pos.x, pos.y, radius.x, radius.y, shape, angle);
}

void NoGUI::DrawShapeTop(int posX, int posY, float radiusH, float radiusV, const Shape& shape, float angle)
{
	switch (shape.sides)
	{
		case 0:
		{
			Vector2 pos = {(float)posX, (float)posY};
			Vector2 radius = {radiusH, radiusV};
			Vector2 origin = {0, -radiusV};
			
			DrawElipsePro(pos, radius, origin, angle, shape.fill->col);
				
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
				startPos = {posX - radiusH, (float)posY + radiusV / 2};
				endPos = {posX + radiusH, (float)posY + radiusV / 2};
			}
			else
			{
				// center on origin
				Vector2 leftPos = {-1 * radiusH, radiusV / 2};
				Vector2 rightPos = {radiusH, radiusV / 2};
				// calculate values
				float sinRotation = sinf(angle*DEG2RAD);
				float cosRotation = cosf(angle*DEG2RAD);
				
				startPos.x = leftPos.x * cosRotation - leftPos.y * sinRotation;
				startPos.y = leftPos.x * sinRotation + leftPos.y * cosRotation;				
				endPos.x = rightPos.x * cosRotation - rightPos.y * sinRotation;
				endPos.y = rightPos.x * sinRotation + rightPos.y * cosRotation;
				// translate back
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
			Vector2 top;
			Vector2 left;
			Vector2 right;
			if ( angle == 0 )
			{
				top = (Vector2){(float)posX, (float)posY};
				left = (Vector2){posX - radiusH, (float)posY + radiusV * 2};
				right = (Vector2){posX + radiusH, (float)posY + radiusV * 2};
			}
			else
			{
				// center on origin
				Vector2 topInc = (Vector2){0, 0};
				Vector2 leftInc = (Vector2){-radiusH, radiusV * 2};
				Vector2 rightInc = (Vector2){radiusH, radiusV * 2};
				// calculate values
				float sinRotation = sinf(angle*DEG2RAD);
				float cosRotation = cosf(angle*DEG2RAD);
				
				top.x = topInc.x * cosRotation - topInc.y * sinRotation;
				top.y = topInc.x * sinRotation + topInc.y * cosRotation;
				left.x = leftInc.x * cosRotation - leftInc.y * sinRotation;
				left.y = leftInc.x * sinRotation + leftInc.y * cosRotation;
				right.x = rightInc.x * cosRotation - rightInc.y * sinRotation;
				right.y = rightInc.x * sinRotation + rightInc.y * cosRotation;
				// translate back
				top.x += posX;
				top.y += posY;
				left.x += posX;
				left.y += posY;
				right.x += posX;
				right.y += posY;
			}
			
			DrawTriangle(top, left, right, shape.fill->col);
				
			break;
		}
			
		case 4:
		{
			Rectangle render = (Rectangle){(float)posX, (float)posY, radiusH * 2, radiusV * 2};
			Vector2 origin = {radiusH, 0};
			
			DrawRectanglePro(render, origin, angle, shape.fill->col);
			
			break;
		}
		
		default:
		{
			Vector2 posV = {float(posX), float(posY)};
			Vector2 radius = {radiusH, radiusV};
			Vector2 origin = {0, -radiusV};

			DrawPolyPro(posV, shape.sides, radius, origin, angle, shape.fill->col);
			
			break;
		}
	}
}

void NoGUI::DrawShapeTop(const Vector2& pos, const Vector2& radius, const Shape& shape, float angle)
{
	DrawShapeTop(pos.x, pos.y, radius.x, radius.y, shape, angle);
}

void NoGUI::DrawShapeBottom(int posX, int posY, float radiusH, float radiusV, const Shape& shape, float angle)
{	
	switch (shape.sides)
	{
		case 0:
		{
			Vector2 pos = {(float)posX, (float)posY};
			Vector2 radius = {radiusH, radiusV};
			Vector2 origin = {0, radiusV};
			
			DrawElipsePro(pos, radius, origin, angle, shape.fill->col);
				
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
				startPos = {posX - radiusH, (float)posY + radiusV / -2};
				endPos = {posX + radiusH, (float)posY + radiusV / -2};
			}
			else
			{
				// center on origin
				Vector2 leftPos = {-1 * radiusH, radiusV / -2};
				Vector2 rightPos = {radiusH, radiusV / -2};
				// calculate values
				float sinRotation = sinf(angle*DEG2RAD);
				float cosRotation = cosf(angle*DEG2RAD);
				
				startPos.x = leftPos.x * cosRotation - leftPos.y * sinRotation;
				startPos.y = leftPos.x * sinRotation + leftPos.y * cosRotation;				
				endPos.x = rightPos.x * cosRotation - rightPos.y * sinRotation;
				endPos.y = rightPos.x * sinRotation + rightPos.y * cosRotation;
				// translate back
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
			Vector2 top;
			Vector2 left;
			Vector2 right;
			if ( angle == 0 )
			{
				top = (Vector2){(float)posX, posY - radiusV * 2};
				left = (Vector2){posX - radiusH, (float)posY};
				right = (Vector2){posX + radiusH, (float)posY};
			}
			else
			{
				// center on origin
				Vector2 topInc = (Vector2){0, -radiusV * 2};
				Vector2 leftInc = (Vector2){-radiusH, 0};
				Vector2 rightInc = (Vector2){radiusH, 0};
				// calculate values
				float sinRotation = sinf(angle*DEG2RAD);
				float cosRotation = cosf(angle*DEG2RAD);
				
				top.x = topInc.x * cosRotation - topInc.y * sinRotation;
				top.y = topInc.x * sinRotation + topInc.y * cosRotation;
				left.x = leftInc.x * cosRotation - leftInc.y * sinRotation;
				left.y = leftInc.x * sinRotation + leftInc.y * cosRotation;
				right.x = rightInc.x * cosRotation - rightInc.y * sinRotation;
				right.y = rightInc.x * sinRotation + rightInc.y * cosRotation;
				// translate back
				top.x += posX;
				top.y += posY;
				left.x += posX;
				left.y += posY;
				right.x += posX;
				right.y += posY;
			}
			
			DrawTriangle(top, left, right, shape.fill->col);
			
			break;
		}

		case 4:
		{
			Rectangle render = (Rectangle){(float)posX, (float)posY, radiusH * 2, radiusV * 2};
			Vector2 origin = {radiusH, radiusV * 2};
			
			DrawRectanglePro(render, origin, angle, shape.fill->col);
			
			break;
		}
		
		default:
		{
			Vector2 posV = {float(posX), float(posY)};
			Vector2 radius = {radiusH , radiusV};
			Vector2 origin = {0, radiusV};

			DrawPolyPro(posV, shape.sides, radius, origin, angle, shape.fill->col);
			
			break;
		}
	}
}

void NoGUI::DrawShapeBottom(const Vector2& pos, const Vector2& radius, const Shape& shape, float angle)
{
	DrawShapeBottom(pos.x, pos.y, radius.x, radius.y, shape, angle);
}

void NoGUI::DrawShapeBottomL(int posX, int posY, float radiusH, float radiusV, const Shape& shape, float angle)
{
	switch (shape.sides)
	{
		case 0:
		{
			Vector2 pos = {(float)posX, (float)posY};
			Vector2 radius = {radiusH, radiusV};
			Vector2 origin = {-radiusH, radiusV};
			
			DrawElipsePro(pos, radius, origin, angle, shape.fill->col);
				
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
				startPos = {(float)posX, posY + radiusV / -2};
				endPos = {(float)posX + radiusH * 2, posY + radiusV / -2};
			}
			else
			{
				// center on origin
				Vector2 leftPos = {0, radiusV / -2};
				Vector2 rightPos = {radiusH * 2, radiusV / -2};
				// calculate values
				float sinRotation = sinf(angle*DEG2RAD);
				float cosRotation = cosf(angle*DEG2RAD);
				
				startPos.x = leftPos.x * cosRotation - leftPos.y * sinRotation;
				startPos.y = leftPos.x * sinRotation + leftPos.y * cosRotation;				
				endPos.x = rightPos.x * cosRotation - rightPos.y * sinRotation;
				endPos.y = rightPos.x * sinRotation + rightPos.y * cosRotation;
				// translate back
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
			Vector2 top;
			Vector2 left;
			Vector2 right;
			if ( angle == 0 )
			{
				top = (Vector2){posX + radiusH, posY - radiusV * 2};
				left = (Vector2){(float)posX, (float)posY};
				right = (Vector2){posX + radiusH * 2, (float)posY};
			}
			else
			{
				// center on origin
				Vector2 topInc = (Vector2){radiusH, -radiusV * 2};
				Vector2 leftInc = (Vector2){0, 0};
				Vector2 rightInc = (Vector2){radiusH * 2, 0};
				// calculate values
				float sinRotation = sinf(angle*DEG2RAD);
				float cosRotation = cosf(angle*DEG2RAD);
				
				top.x = topInc.x * cosRotation - topInc.y * sinRotation;
				top.y = topInc.x * sinRotation + topInc.y * cosRotation;
				left.x = leftInc.x * cosRotation - leftInc.y * sinRotation;
				left.y = leftInc.x * sinRotation + leftInc.y * cosRotation;
				right.x = rightInc.x * cosRotation - rightInc.y * sinRotation;
				right.y = rightInc.x * sinRotation + rightInc.y * cosRotation;
				// translate back
				top.x += posX;
				top.y += posY;
				left.x += posX;
				left.y += posY;
				right.x += posX;
				right.y += posY;
			}
			
			DrawTriangle(top, left, right, shape.fill->col);
				
			break;
		}
			
		case 4:
		{
			Rectangle render = (Rectangle){(float)posX, (float)posY, radiusH * 2, radiusV * 2};
			Vector2 origin = {0, radiusV * 2};
			
			DrawRectanglePro(render, origin, angle, shape.fill->col);
			
			break;
		}
		
		default:
		{
			Vector2 posV = {float(posX), float(posY)};
			Vector2 radius = {radiusH , radiusV};
			Vector2 origin = {-radiusH, radiusV};

			DrawPolyPro(posV, shape.sides, radius, origin, angle, shape.fill->col);
			
			break;
		}
	}
}

void NoGUI::DrawShapeBottomL(const Vector2& pos, const Vector2& radius, const Shape& shape, float angle)
{
	DrawShapeBottomL(pos.x, pos.y, radius.x, radius.y, shape, angle);
}

void NoGUI::DrawShapeBottomR(int posX, int posY, float radiusH, float radiusV, const Shape& shape, float angle)
{
	switch (shape.sides)
	{
		case 0:
		{
			Vector2 pos = {(float)posX, (float)posY};
			Vector2 radius = {radiusH, radiusV};
			Vector2 origin = {radiusH, radiusV};
			
			DrawElipsePro(pos, radius, origin, angle, shape.fill->col);
				
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
				startPos = {posX + radiusH * -2, posY - radiusV / 2};
				endPos = {(float)posX, posY - radiusV / 2};
			}
			else
			{
				// center on origin
				Vector2 leftPos = {radiusH * -2, radiusV / -2};
				Vector2 rightPos = {0, radiusV / -2};
				// calculate values
				float sinRotation = sinf(angle*DEG2RAD);
				float cosRotation = cosf(angle*DEG2RAD);
				
				startPos.x = leftPos.x * cosRotation - leftPos.y * sinRotation;
				startPos.y = leftPos.x * sinRotation + leftPos.y * cosRotation;				
				endPos.x = rightPos.x * cosRotation - rightPos.y * sinRotation;
				endPos.y = rightPos.x * sinRotation + rightPos.y * cosRotation;
				// translate back
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
			Vector2 top;
			Vector2 left;
			Vector2 right;
			if ( angle == 0 )
			{
				top = (Vector2){posX - radiusH, posY - radiusV * 2};
				left = (Vector2){(float)posX - radiusH * 2, (float)posY};
				right = (Vector2){(float)posX, (float)posY};
			}
			else
			{
				// center on origin
				Vector2 topInc = (Vector2){-radiusH, -radiusV * 2};
				Vector2 leftInc = (Vector2){-radiusH * 2, 0};
				Vector2 rightInc = (Vector2){0, 0};
				// calculate values
				float sinRotation = sinf(angle*DEG2RAD);
				float cosRotation = cosf(angle*DEG2RAD);
				
				top.x = topInc.x * cosRotation - topInc.y * sinRotation;
				top.y = topInc.x * sinRotation + topInc.y * cosRotation;
				left.x = leftInc.x * cosRotation - leftInc.y * sinRotation;
				left.y = leftInc.x * sinRotation + leftInc.y * cosRotation;
				right.x = rightInc.x * cosRotation - rightInc.y * sinRotation;
				right.y = rightInc.x * sinRotation + rightInc.y * cosRotation;
				// translate back
				top.x += posX;
				top.y += posY;
				left.x += posX;
				left.y += posY;
				right.x += posX;
				right.y += posY;
			}
			
			DrawTriangle(top, left, right, shape.fill->col);
				
			break;
		}
			
		case 4:
		{
			Rectangle render = (Rectangle){(float)posX, (float)posY, radiusH * 2, radiusV * 2};
			Vector2 origin = {radiusH * 2, radiusV * 2};
			
			DrawRectanglePro(render, origin, angle, shape.fill->col);
			
			break;
		}
		
		default:
		{
			Vector2 posV = {float(posX), float(posY)};
			Vector2 radius = {radiusH, radiusV};
			Vector2 origin = {radiusH, radiusV};

			DrawPolyPro(posV, shape.sides, radius, origin, angle, shape.fill->col);
			
			break;
		}
	}
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
			
			break;
		}
		
		case Align::CENTER:
		{
			DrawShapeCenter(posX, posY, radiusH, radiusV, shape, angle);
			
			break;
		}
		
		case Align::RIGHT:
		{
			DrawShapeRight(posX, posY, radiusH, radiusV, shape, angle);
			
			break;
		}
		
		case Align::TOP:
		{
			DrawShapeTop(posX, posY, radiusH, radiusV, shape, angle);
			
			break;
		}
		
		case Align::BOTTOML:
		{
			DrawShapeBottomL(posX, posY, radiusH, radiusV, shape, angle);
			
			break;
		}
		
		case Align::BOTTOM:
		{
			DrawShapeBottom(posX, posY, radiusH, radiusV, shape, angle);
			
			break;
		}
		
		case Align::BOTTOMR:
		{
			DrawShapeBottomR(posX, posY, radiusH, radiusV, shape, angle);
			
			break;
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

void Element::draw()
{
	DrawShape(transform, *(shape.get()));
}

bool Element::getFocus()
{
	
	return focus;
}

bool Element::getActive()
{
	
	return active;
}

NoGUI::Transform Element::dimensions()
{
	
	return transform;
}

std::shared_ptr< Shape > Element::style()
{
	
	return shape;
}

Vector2 Element::pos()
{
	
	return transform.pos;
}

Vector2 Element::pos(const Align& origin)
{
	Vector2 ret = transform.pos;
	
	switch (transform.origin)
	{
		case Align::LEFT:
		{
			switch (origin)
			{
				case Align::LEFT:
				{
						
					break;
				}
				
				case Align::CENTER:
				{
					ret.x += transform.radius.x;
					ret.y += transform.radius.y;
						
					break;
				}
					
				case Align::RIGHT:
				{
					ret.x += transform.radius.x * 2;
						
					break;
				}
					
				case Align::TOP:
				{
					ret.x += transform.radius.x;
						
					break;
				}
					
				case Align::BOTTOM:
				{
					ret.x += transform.radius.x;
					ret.y -= transform.radius.y;
						
					break;
				}
					
				case Align::BOTTOML:
				{
					ret.y -= transform.radius.y;
						
					break;
				}
					
				case Align::BOTTOMR:
				{
					ret.x += transform.radius.x * 2;
					ret.y -= transform.radius.y;
						
					break;
				}
			}
			
			break;
		}
			
		case Align::CENTER:
		{
			switch (origin)
			{
				case Align::LEFT:
				{
					ret.x -= transform.radius.x;
					ret.y -= transform.radius.y;
						
					break;
				}
				
				case Align::CENTER:
				{
						
					break;
				}
					
				case Align::RIGHT:
				{
					ret.x += transform.radius.x;
					ret.y -= transform.radius.y;
						
					break;
				}
					
				case Align::TOP:
				{
					ret.y -= transform.radius.y;
					
					break;
				}
					
				case Align::BOTTOM:
				{
					ret.y += transform.radius.y;
						
					break;
				}
					
				case Align::BOTTOML:
				{
					ret.x -= transform.radius.x;
					ret.y += transform.radius.y;
						
					break;
				}
					
				case Align::BOTTOMR:
				{
					ret.x += transform.radius.x;
					ret.y += transform.radius.y;
						
					break;
				}
			}
			
			break;
		}
			
		case Align::RIGHT:
		{
			switch (origin)
			{
				case Align::LEFT:
				{
					ret.x -= transform.radius.x * 2;
						
					break;
				}
					
				case Align::CENTER:
				{
					ret.x += transform.radius.x;
					ret.y += transform.radius.y;
						
					break;
				}
				
				case Align::RIGHT:
				{

					break;
				}
					
				case Align::TOP:
				{
					ret.x -= transform.radius.x;
						
					break;
				}
					
				case Align::BOTTOM:
				{
					ret.x -= transform.radius.x;
					ret.y += transform.radius.y * 2;
						
					break;
				}
					
				case Align::BOTTOML:
				{
					ret.x -= transform.radius.x;
					ret.y += transform.radius.y * 2;
					
					break;
				}
					
				case Align::BOTTOMR:
				{
					ret.y += transform.radius.y * 2;
					
					break;
				}
			}
			
			break;
		}
			
		case Align::TOP:
		{
			switch (origin)
			{
				case Align::LEFT:
				{
					ret.x -= transform.radius.x;
					
					break;
				}
					
				case Align::CENTER:
				{
					ret.y += transform.radius.y;
					
					break;
				}
					
				case Align::RIGHT:
				{
					ret.x += transform.radius.x;
					
					break;
				}
				
				case Align::TOP:
				{
					
					break;
				}
					
				case Align::BOTTOM:
				{
					ret.y += transform.radius.y * 2;
					
					break;
				}
					
				case Align::BOTTOML:
				{
					ret.x -= transform.radius.x;
					ret.y += transform.radius.y * 2;
					
					break;
				}
					
				case Align::BOTTOMR:
				{
					ret.x -= transform.radius.x;
					ret.y += transform.radius.y * 2;
						
					break;
				}
			}
			
			break;
		}
			
		case Align::BOTTOM:
		{
			switch (origin)
			{
				case Align::LEFT:
				{
					ret.x -= transform.radius.x;
					ret.y -= transform.radius.y * 2;
					
					break;
				}
					
				case Align::CENTER:
				{
					ret.y -= transform.radius.y;
					
					break;
				}
				
				case Align::RIGHT:
				{
					ret.x += transform.radius.x;
					ret.y -= transform.radius.y * 2;
					
					break;
				}
					
				case Align::TOP:
				{
					ret.y += transform.radius.y * 2;
					
					break;
				}
				
				case Align::BOTTOM:
				{
					
					break;
				}
					
				case Align::BOTTOML:
				{
					ret.x -= transform.radius.x;
					
					break;
				}
					
				case Align::BOTTOMR:
				{
					ret.x += transform.radius.x;
					
					break;
				}
			}
			
			break;
		}
			
		case Align::BOTTOML:
		{
			switch (origin)
			{
				case Align::LEFT:
				{
					ret.y -= transform.radius.y * 2;
					
					break;
				}
				
				case Align::CENTER:
				{
					ret.x += transform.radius.x;
					ret.y -= transform.radius.y;
					
					break;
				}
					
				case Align::RIGHT:
				{
					ret.x += transform.radius.x * 2;
					ret.y -= transform.radius.y * 2;
					
					break;
				}
					
				case Align::TOP:
				{
					ret.x += transform.radius.x;
					ret.y -= transform.radius.y * 2;
					
					break;
				}
					
				case Align::BOTTOM:
				{
					ret.x += transform.radius.x;
					
					break;
				}
				
				case Align::BOTTOML:
				{
					
					break;
				}
					
				case Align::BOTTOMR:
				{
					ret.x += transform.radius.x * 2;
					
					break;
				}
			}
			
			break;
		}
			
		case Align::BOTTOMR:
		{
			switch (origin)
			{
				case Align::LEFT:
				{
					ret.x -= transform.radius.x * 2;
					ret.y -= transform.radius.y * 2;
					
					break;
				}
				
				case Align::CENTER:
				{
					ret.x -= transform.radius.x;
					ret.y -= transform.radius.y;
					
					break;
				}
				
				case Align::RIGHT:
				{
					ret.y -= transform.radius.y * 2;
					
					break;
				}
				
				case Align::TOP:
				{
					ret.x -= transform.radius.x;
					ret.y -= transform.radius.y * 2;
					
					break;
				}
				
				case Align::BOTTOM:
				{
					ret.x += transform.radius.x;
					
					break;
				}
				
				case Align::BOTTOML:
				{
					ret.x += transform.radius.x * 2;
					
					break;
				}
				
				case Align::BOTTOMR:
				{
					
					break;
				}
			}
		}
		
		break;
	}
	
	return ret;
}

Vector2 Element::radius()
{
	
	return transform.radius;
}

Vector2 Element::size()
{
	Vector2 ret = transform.radius;
	ret.x *= 2;
	ret.y *= 2;
	
	return ret;
}

Align Element::origin()
{
	
	return transform.origin;
}

float Element::rotation()
{
	
	return transform.angle;
}

Vector2 Element::repos(Vector2 newPos)
{
	transform.pos = newPos;
	
	return transform.pos;
}

Vector2 Element::repos(Vector2 newPos, const Align& origin, bool update)
{
	if ( update )
	{
		transform.origin = origin;
	}
	else if ( origin != transform.origin )
	{
		Vector2 translate = pos(origin);
		translate.x -= transform.pos.x;
		translate.y -= transform.pos.y;
		newPos.x -= translate.x;
		newPos.y -= translate.y;
	}
	
	repos(newPos);
	
	return transform.pos;
}

void Element::resize(const Vector2& size)
{
	transform.radius = (Vector2){size.x / 2, size.y / 2};
}

void Element::reorient(float degrees, const Align& origin, bool update)
{
	if ( origin == transform.origin )
	{
		transform.angle = degrees;
	}
	else if ( update )
	{
		transform.origin = origin;
		transform.angle = degrees;
	}
	else
	{
		reorient(degrees, pos(origin));
	}
}

void Element::reorient(float degrees, const Vector2& origin)
{
	transform.angle = degrees;
	Vector2 temp = {transform.pos.x - origin.x, transform.pos.y - origin.y};
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
	transform.pos.x += posInc.x;
	transform.pos.y += posInc.y;
}

void Element::rotate(float degrees, const Align& origin, bool update)
{
	if ( origin == transform.origin )
	{
		transform.angle += degrees;
	}
	else if ( update )
	{
		transform.origin = origin;
		transform.angle += degrees;
	}
	else
	{
		rotate(degrees, pos(origin));
	}
}

void Element::rotate(float degrees, const Vector2& origin)
{
	transform.angle += degrees;
	Vector2 newPos = {transform.pos.x - origin.x, transform.pos.y - origin.y};
	Vector2 posInc;
	// calculate values
	float sinRotation = sinf(degrees*DEG2RAD);
	float cosRotation = cosf(degrees*DEG2RAD);
		
	posInc.x = newPos.x * cosRotation - newPos.y * sinRotation;
	posInc.y = newPos.x * sinRotation + newPos.y * cosRotation;				
	// translate back
	transform.pos.x = posInc.x + origin.x;
	transform.pos.y = posInc.y + origin.y;
}

void Element::reshape(std::shared_ptr< Shape > newShape)
{
	shape = newShape;
}

void Element::redimension(const NoGUI::Transform& newTransform)
{
	transform = newTransform;
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

void NoGUI::DrawPolyPro(Vector2 center, int sides, Vector2 radius, Vector2 origin, float angle, Color col)
{
    if (sides < 3) sides = 3;
    float centralAngle = 0.0f;
	if ( angle == 0 )
	{
		center.x -= origin.x;
		center.y -= origin.y;
	}
	else
	{
		float sinRotation = sinf(angle*DEG2RAD);
		float cosRotation = cosf(angle*DEG2RAD);
		Vector2 pivot = {center.x + origin.x, center.y + origin.y};
		Vector2 newPos = center;
		Vector2 finalPos;
		newPos.x -= pivot.x;
		newPos.y -= pivot.y;
			
		finalPos.x = newPos.x * cosRotation - newPos.y * sinRotation;
		finalPos.y = newPos.x * sinRotation + newPos.y * cosRotation;
				
		center.x += finalPos.x;
		center.y += finalPos.y;
	}
#if defined(SUPPORT_QUADS_DRAW_MODE)
    rlCheckRenderBatchLimit(4*sides); // Each side is a quad
#else
    rlCheckRenderBatchLimit(3*sides);
#endif

    rlPushMatrix();
        rlTranslatef(center.x, center.y, 0.0f);
        rlRotatef(angle, 0.0f, 0.0f, 1.0f);

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
	rlPopMatrix();
}

void NoGUI::DrawElipsePro(Vector2 center, Vector2 radius, Vector2 origin, float angle, Color col)
{
	if ( angle == 0 )
	{
		center.x -= origin.x;
		center.y -= origin.y;
	}
	else
	{
		float sinRotation = sinf(angle*DEG2RAD);
		float cosRotation = cosf(angle*DEG2RAD);
		Vector2 pivot = {center.x + origin.x, center.y + origin.y};
		Vector2 newPos = center;
		Vector2 finalPos;
		newPos.x -= pivot.x;
		newPos.y -= pivot.y;
			
		finalPos.x = newPos.x * cosRotation - newPos.y * sinRotation;
		finalPos.y = newPos.x * sinRotation + newPos.y * cosRotation;
				
		center.x += finalPos.x;
		center.y += finalPos.y;
	}
	
	rlCheckRenderBatchLimit(3*36);
	
	rlPushMatrix();
		rlTranslatef(center.x, center.y, 0.0f);
		rlRotatef(angle, 0.0f, 0.0f, 1.0f);
		
		rlBegin(RL_TRIANGLES);
			for (int i = 0; i < 360; i += 10)
			{
				rlColor4ub(col.r, col.g, col.b, col.a);
				
				rlVertex2f(0, 0);
				rlVertex2f(sinf(DEG2RAD*i)*radius.x, cosf(DEG2RAD*i)*radius.y);
				
				rlVertex2f(sinf(DEG2RAD*(i + 10))*radius.x, cosf(DEG2RAD*(i + 10))*radius.y);
			}
		rlEnd();
	rlPopMatrix();
}
