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

void NoGUI::DrawCImageCropped(CImage& img, std::shared_ptr< nShape > shape, const NoGUI::Transform& transform, bool scroll)
{
	// calculate img dimensions
	Vector2 imgSize = {img.img->width * img.scale.x, img.img->height * img.scale.y};
	Vector2 maxSize = imgSize;
	bool isMax = false;
	if ( imgSize.x > transform.width() )
	{
		maxSize.x = transform.width();
		isMax = imgSize.y >= transform.height();
	}
	else if ( imgSize.x < transform.width() * -1 )
	{
		maxSize.x = transform.width() * -1;
		isMax = imgSize.y <= transform.height() * -1;
	}
	if ( imgSize.y > transform.height() )
	{
		maxSize.y = transform.height();
	}
	else if ( imgSize.y < transform.height() * -1 )
	{
		maxSize.y = transform.height() * -1;
	}
	// convert into same proportions as shape.
	Vector2 diff = {0};
	float umod = 0;
	float vmod = 0;
	if ( !isMax )
	{
		if ( imgSize.y < imgSize.x )
		{ 
			float widthRate = transform.width() / transform.height();
			maxSize.x = maxSize.y * widthRate;
		}
		else if ( imgSize.y > imgSize.x )
		{
			float heightRate = transform.height() / transform.width();
			maxSize.y = maxSize.x * heightRate;
		}
		// calculate difference between texture and shape as percentage
		if ( img.scale.x > 0 )
		{
			diff.x = (imgSize.x - maxSize.x * img.scale.x) / imgSize.x;
		}
		else
		{
			diff.x = (imgSize.x + maxSize.x * img.scale.x) / imgSize.x;
		}
		if ( img.scale.y > 0 )
		{
			diff.y = (imgSize.y - maxSize.y * img.scale.y) / imgSize.y;
		}
		else
		{
			diff.y = (imgSize.y + maxSize.y * img.scale.y) / imgSize.y;
		}
		umod = (diff.x > 0) ? diff.x / 2 : 0;
		vmod = (diff.y > 0) ? diff.y / 2 : 0;
	}
	else
	{
		diff = {(imgSize.x - maxSize.x) / imgSize.x, (imgSize.y - maxSize.y) / imgSize.y};
		umod = diff.x / 2;
		vmod = diff.y / 2;
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
			Vector2 texCenter = {0.5f, 0.5f};
			// TODO: gross hack
			if ( scroll )
			{
				texCenter.x = img.scrollPos.x - ((img.scrollPos.x - 0.5f) / 2);
				texCenter.y = img.scrollPos.y - ((img.scrollPos.y - 0.5f) / 4.0f * 3);
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
				texcoords[i] = (Vector2){texCenter.x + sin * (0.5f - umod), texCenter.y + cos * (0.5f - vmod)};
						
				centralAngle += 10;
			}
			
			DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), texCenter, points, texcoords, max, img.col);
			if ( isMax && scroll )
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
			Vector2 maxRadius = {maxSize.x / 2, maxSize.y / 2};
			Vector2 texCenter = {0.5f, 0.5f};
			// TODO: gross hack
			if ( scroll )
			{
				texCenter.x = img.scrollPos.x - ((img.scrollPos.x - 0.5f) / 2);
				texCenter.y = img.scrollPos.y - ((img.scrollPos.y - 0.5f) / 4.0f * 3);
			}
			Vector2 texcoords[max] =
			{ 
				(Vector2){texCenter.x, texCenter.y - 0.5f + vmod},
				(Vector2){texCenter.x - 0.5f + umod, texCenter.y + 0.5f - vmod},
				(Vector2){texCenter.x + 0.5f - umod, texCenter.y + 0.5f - vmod},
				(Vector2){texCenter.x, texCenter.y - 0.5f + vmod}
			};
			// create coordnites for texture (triangle)
			Vector2 points[max] = 
			{
				(Vector2){0, maxRadius.y * -1},
				(Vector2){maxRadius.x * -1, maxRadius.y},
				(Vector2){maxSize.x / 2, maxRadius.y},
				(Vector2){0.0f, maxRadius.y * -1}
			};
			// create copy to rotate coordnites
			Vector2 positions[max] = { 0 };
			for (int i = 0; i < max; i++)
			{	
				positions[i] = Vector2Rotate(points[i], transform.angle*DEG2RAD);
			}
			
			DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), texCenter, positions, texcoords, max, img.col);
			if ( isMax && scroll )
			{
				Vector2 percentShown = {maxSize.x / imgSize.x, maxSize.y / imgSize.y};
				DrawScrollBars(nullptr, nullptr, transform, img.scrollPos, percentShown, 3);
			}
			
			break;
		}
		
		case 4:
		{
			Vector2 sourceSize = maxSize; // texture size
			Vector2 destSize = sourceSize; // screen size
			Vector2 texCenter = {0.5f, 0.5f};
			if ( scroll )
			{
				texCenter.x = img.scrollPos.x;
				texCenter.y = img.scrollPos.y;
			}
			Vector2 sourcePos = {texCenter.x * (img.img->width - maxSize.x), texCenter.y * (img.img->height - maxSize.y)};
			Vector2 destPos = transform.pos(NoGUI::Align(0, 0));
			if ( img.scale.x <  0 )
			{
				sourcePos.x = texCenter.x * (img.img->width + maxSize.x);
				destSize.x *= -1;
			}
			if ( img.scale.y <  0 )
			{
				sourcePos.y = texCenter.y * (img.img->height + maxSize.y);
				destSize.y *= -1;
			}
			if ( isMax )
			{
				sourceSize = {maxSize.x - maxSize.x * (1.0f - 1.0f / img.scale.x), maxSize.y - maxSize.y * (1.0f - 1.0f / img.scale.y)};
				sourcePos = {texCenter.x * (img.img->width - sourceSize.x), texCenter.y * (img.img->height - sourceSize.y)};
				if ( img.scale.x <  0 )
				{
					destSize.x *= -1;
				}
				if ( img.scale.y <  0 )
				{
					destSize.y *= -1;
				}
				Rectangle source = {sourcePos.x, sourcePos.y, sourceSize.x, sourceSize.y};
				Rectangle dest = {destPos.x, destPos.y, destSize.x, destSize.y};
				Vector2 origin = {dest.width / 2, dest.height / 2};
				DrawTexturePro((*img.img), source, dest, origin, transform.angle, WHITE); // draw before scroll bars
				if ( scroll )
				{
					Vector2 percentShown = {maxSize.x / imgSize.x, maxSize.y / imgSize.y};
					DrawScrollBars(nullptr, nullptr, transform, img.scrollPos, percentShown, 3);
				}
			}
			else
			{
				Rectangle source = {sourcePos.x, sourcePos.y, sourceSize.x, sourceSize.y};
				Rectangle dest = {destPos.x, destPos.y, destSize.x, destSize.y};
				Vector2 origin = {dest.width / 2, dest.height / 2};
				DrawTexturePro((*img.img), source, dest, origin, transform.angle, WHITE);
			}

			break;
		}
		
		default:
		{
			int max = shape->n + 1;
			float centralAngle = 0;
			Vector2 texCenter = {0.5f, 0.5f};
			// TODO: gross hack
			if ( scroll )
			{
				texCenter.x = img.scrollPos.x - ((img.scrollPos.x - 0.5f) / 2);
				texCenter.y = img.scrollPos.y - ((img.scrollPos.y - 0.5f) / 4.0f * 3);
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
				texcoords[i] = (Vector2){texCenter.x + sin * (0.5f - umod), texCenter.y + cos * (0.5f - vmod)};
						
				centralAngle += 360.0f / (float)shape->n;
			}
			// create copy to rotate coordnites
			Vector2 positions[max] = { 0 };
			for (int i=0; i < max; i++) 
			{	
				positions[i] = Vector2Rotate(points[i], transform.angle*DEG2RAD);
			}
			
			DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), texCenter, positions, texcoords, max, img.col);
			if ( isMax && scroll )
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
	switch (shape->n)
	{
		case 0:
		{
			int max = 37;
			float centralAngle = transform.angle;
			Vector2 texcoords[max] = { 0 };
			Vector2 points[max] = { 0 };
			for (int i=0; i < max; i++)
			{
				texcoords[i] = (Vector2){0.5f + sinf(centralAngle * DEG2RAD) * 0.5f, 0.5f + cosf(centralAngle * DEG2RAD) * 0.5f};
				centralAngle += 10;
				
				points[i].x = (texcoords[i].x - 0.5f) * transform.width();
				points[i].y = (texcoords[i].y - 0.5f) * transform.height();
			}
			
			DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), (Vector2){0.5f, 0.5f}, points, texcoords, max, img.col);
			
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
			Vector2 points[max] = { 0 };
			for (int i=0; i < max; i++)
			{
				points[i].x = (texcoords[i].x - 0.5f) * transform.width();
				points[i].y = (texcoords[i].y - 0.5f) * transform.height();
			}
					
			Vector2 positions[max] = { 0 };
			for (int i = 0; i < max; i++) 
			{	
				positions[i] = points[i];
			}
			for (int i = 0; i < max; i++)
			{	
				positions[i] = Vector2Rotate(points[i], transform.angle*DEG2RAD);
			}
			
			DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), (Vector2){0.5f, 0.5f}, positions, texcoords, max, img.col);
			
			break;
		}
		
		case 4:
		{
			int max = 5;
			Vector2 texcoords[max] =
			{ 
				(Vector2){0.0f, 0.0f},
				(Vector2){0.0f, 1.0f},
				(Vector2){1.0f, 1.0f},
				(Vector2){1.0f, 0.0f},
				(Vector2){0.0f, 0.0f}
			};
			Vector2 points[max] = { 0 };
			for (int i=0; i < max; i++)
			{
				points[i].x = (texcoords[i].x - 0.5f) * transform.width();
				points[i].y = (texcoords[i].y - 0.5f) * transform.height();
			}
			Vector2 positions[max] = { 0 };
			for (int i = 0; i < max; i++) 
			{	
				positions[i] = points[i];
			}
			for (int i = 0; i < max; i++)
			{	
				positions[i] = Vector2Rotate(points[i], transform.angle*DEG2RAD);
			}
			
			DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), (Vector2){0.5f, 0.5f}, positions, texcoords, max, img.col);
			
			break;
		}
		
		default:
		{
			int max = shape->n + 1;
			float centralAngle = 0;
			Vector2 texcoords[max] = { 0 };
			Vector2 points[max] = { 0 };
			for (int i=0; i < max; i++)
			{
				texcoords[i] = (Vector2){0.5f + sinf(centralAngle * DEG2RAD) * 0.5f, 0.5f + cosf(centralAngle * DEG2RAD) * 0.5f};
				centralAngle += 360.0f / (float)shape->n;
						
				points[i].x = (texcoords[i].x - 0.5f) * transform.width();
				points[i].y = (texcoords[i].y - 0.5f) * transform.height();
			}
			Vector2 positions[max] = { 0 };
			for (int i = 0; i < max; i++) 
			{	
				positions[i] = points[i];
			}
			for (int i = 0; i < max; i++)
			{	
				positions[i] = Vector2Rotate(points[i], transform.angle*DEG2RAD);
			}
			
			DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), (Vector2){0.5f, 0.5f}, positions, texcoords, max, img.col);
			
			break;
		}
	}
}

void NoGUI::DrawCImage(CImage& img, const NoGUI::Transform& transform)
{
	// calculate image dimensions
	Vector2 imgSize = {img.img->width * img.scale.x, img.img->height * img.scale.y};
	Rectangle source = {0, 0, (float)img.img->width, (float)img.img->height};
	// center on shape
	Vector2 destPos = transform.pos(NoGUI::Align(0, 0));
	Rectangle dest = {destPos.x, destPos.y, imgSize.x, imgSize.y};
	Vector2 origin = {dest.width / 2, dest.height / 2};
			
	DrawTexturePro((*img.img), source, dest, origin, transform.angle, img.col);
}

void NoGUI::DrawCImage(CImage& img, std::shared_ptr< nShape > shape, const NoGUI::Transform& transform)
{
	switch(img.crop)
	{
		case Crop::NONE:
		{
			DrawCImage(img, transform);
			
			break;
		}
		
		case Crop::FIT:
		{
			DrawCImageFitted(img, shape, transform);
			
			break;
		}
		
		case Crop::CUT:
		{
			DrawCImageCropped(img, shape, transform, false);
			
			break;
		}
		
		case Crop::SCROLL:
		{
			DrawCImageCropped(img, shape, transform, true);
			
			break;
		}
	}
}

void NoGUI::DrawElement(Element* elem)
{
	std::shared_ptr< NoGUI::nShape > shape = elem->style();
	DrawShape(*(shape.get()), *(elem));
	if (elem->components)
	{
		CImage& imgComp = elem->components->getComponent< NoGUI::CImage >();
		if ( imgComp.active )
		{
			DrawCImage(imgComp, elem->style(), (*elem));
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
