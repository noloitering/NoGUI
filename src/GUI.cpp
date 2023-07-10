#include "GUI.h"

using namespace NoGUI;

void NoGUI::DrawShape(const nShape& shape, Vector2 center, Vector2 radius, Vector2 origin, float angle)
{
	switch (shape.n)
	{
		case 0:
		{
			if (shape.fill)
			{
				DrawEllipsePro(center, radius, origin, angle, shape.fill->col);
			}
			if ( shape.outline )
			{
				DrawEllipseLinesPro(center, radius, origin, angle, shape.outline->thick, shape.outline->fill->col);
			}
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
			
			DrawLineEx(startPos, endPos, radius.y, shape.fill->col);
			
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
			
			if (shape.fill)
			{
				DrawTriangle(v1, v2, v3, shape.fill->col);
			}
			if ( shape.outline )
			{
				DrawTriangleLinesEx(v1, v2, v3, shape.outline->thick, shape.outline->fill->col);
			}
			
			break;
		}
		
		case 4:
		{
			Rectangle rect = {center.x, center.y, radius.x * 2, radius.y * 2};
			origin.x += radius.x;
			origin.y += radius.y;
			
			if (shape.fill)
			{
				DrawRectanglePro(rect, origin, angle, shape.fill->col);
			}
			if ( shape.outline )
			{
				DrawRectangleLinesPro(rect, origin, angle, shape.outline->thick, shape.outline->fill->col);
			}
			
			break;
		}
		
		default:
		{
			if (shape.fill)
			{
				DrawPolyPro(center, shape.n, radius, origin, angle, shape.fill->col);
			}
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
	Vector2 shapeOrigin = {(float)static_cast< int >(transform.origin.x), (float)static_cast< int >(transform.origin.y)};
	shapeOrigin.x *= transform.radius.x;
	shapeOrigin.y *= transform.radius.y;
	
	DrawShape(shape, transform.pos(), transform.radius, shapeOrigin, transform.rotation());
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

// TODO: draw outlines last
void NoGUI::DrawElement(Element* elem)
{
	std::shared_ptr< NoGUI::nShape > shape = elem->style();
	DrawShape(*(shape.get()), *(elem));
	if (elem->components)
	{
		CImage& imgComp = elem->components->getComponent< NoGUI::CImage >();
		if ( imgComp.active )
		{
			if ( imgComp.shape )
			{
				DrawCImage(imgComp, imgComp.shape, (*elem));
			}
			else
			{
				std::shared_ptr< NoGUI::Fill > imgFill = std::make_shared< NoGUI::Fill >();
				std::shared_ptr< NoGUI::nShape > imgShape =  std::make_shared< NoGUI::nShape >(elem->style()->n, imgFill, nullptr); // ehhh, not the greatest solution
				DrawCImage(imgComp, imgShape, (*elem));
			}
		}
	}
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
