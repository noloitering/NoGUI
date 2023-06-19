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

// TODO: break and clean this up
void NoGUI::DrawCImage(CImage& img, std::shared_ptr< nShape > shape, const NoGUI::Transform& transform)
{
	switch(img.crop)
	{
		case Crop::NONE:
		{
			// calculate image dimensions
			Vector2 imgSize = {img.img->width * img.scale.x, img.img->height * img.scale.y};
			Rectangle source = {0, 0, (float)img.img->width, (float)img.img->height};
			// center on shape
			Vector2 destPos = transform.pos(NoGUI::Align(0, 0));
			Rectangle dest = {destPos.x, destPos.y, imgSize.x, imgSize.y};
			Vector2 origin = {dest.width / 2, dest.height / 2};
			
			DrawTexturePro((*img.img), source, dest, origin, transform.angle, img.col);
			
			break;
		}
		
		case Crop::FIT:
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
			
					DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), points, texcoords, max, img.col);
			
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
			
					DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), positions, texcoords, max, img.col);
			
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
			
					DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), positions, texcoords, max, img.col);
			
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
			
					DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), positions, texcoords, max, img.col);
			
					break;
				}
			}
			
			break;
		}
		
		case Crop::CUT:
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
			Vector2 diff;
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
			
			switch (shape->n)
			{
				case 0:
				{
					int max = 37;
					float centralAngle = 0;
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
						texcoords[i] = (Vector2){0.5f + sin * (0.5f - umod), 0.5f + cos * (0.5f - vmod)};
						
						centralAngle += 10;
					}
			
					DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), points, texcoords, max, img.col);
			
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
					// create UVs for triangle
					Vector2 texcoords[max] =
					{ 
						(Vector2){0.5f, 0.0f + vmod},
						(Vector2){0.0f + umod, 1.0f - vmod},
						(Vector2){1.0f - umod, 1.0f - vmod},
						(Vector2){0.5f, 0.0f + vmod}
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
			
					DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), positions, texcoords, max, img.col);
			
					break;
				}
		
				case 4:
				{
					int max = 5;
					Vector2 maxRadius = {maxSize.x / 2, maxSize.y / 2};
					// create UVs for rectangle
					Vector2 texcoords[5] = 
					{
						(Vector2){0.0f + umod, 0.0f + vmod},
						(Vector2){0.0f + umod, 1.0f - vmod},
						(Vector2){1.0f - umod, 1.0f - vmod},
						(Vector2){1.0f - umod, 0.0f + vmod},
						(Vector2){0.0f + umod, 0.0f + vmod}
					};
					// create coordnites for texture (rectangle)
					Vector2 points[max] = 
					{
						(Vector2){maxRadius.x * -1, maxRadius.y * -1},
						(Vector2){maxRadius.x * -1, maxRadius.y},
						(Vector2){maxRadius.x, maxRadius.y},
						(Vector2){maxRadius.x, maxRadius.y * -1},
						(Vector2){maxRadius.x * -1, maxRadius.y * -1}
					};
					// create copy to rotate coordnites
					Vector2 positions[5] = { 0 };
					for (int i = 0; i < max; i++)
					{	
						positions[i] = Vector2Rotate(points[i], transform.angle*DEG2RAD);
					}
					
					DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), positions, texcoords, max, img.col);
					
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
						float sin = sinf(centralAngle * DEG2RAD);
						float cos = cosf(centralAngle * DEG2RAD);
						// calculate texture coordnites offset
						points[i].x = sin * 0.5f * maxSize.x;
						points[i].y = cos * 0.5f * maxSize.y;
						// calculate texture coordnites
						texcoords[i] = (Vector2){0.5f + sin * (0.5f - umod), 0.5f + cos * (0.5f - vmod)};
						
						centralAngle += 360.0f / (float)shape->n;
					}
					// create copy to rotate coordnites
					Vector2 positions[max] = { 0 };
					for (int i=0; i < max; i++) 
					{	
						positions[i] = Vector2Rotate(points[i], transform.angle*DEG2RAD);
					}
			
					DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), positions, texcoords, max, img.col);
			
					break;
				}
			}
			
			break;
		}
		
		case Crop::SCROLL:
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
						texcoords[i] = (Vector2){0.5f + sin * (0.5f - umod), 0.5f + cos * (0.5f - vmod)};
						
						centralAngle += 10;
					}
			
					DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), points, texcoords, max, img.col);
			
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
					// create UVs for triangle
					Vector2 texcoords[max] =
					{ 
						(Vector2){0.5f, 0.0f + vmod},
						(Vector2){0.0f + umod, 1.0f - vmod},
						(Vector2){1.0f - umod, 1.0f - vmod},
						(Vector2){0.5f, 0.0f + vmod}
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
			
					DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), positions, texcoords, max, img.col);
			
					break;
				}
		
				case 4:
				{
					Vector2 sourceSize = maxSize; // texture size
					Vector2 destSize = sourceSize; // screen size
					Vector2 sourcePos = {img.scrollPos.x * (img.img->width - maxSize.x), img.scrollPos.y * (img.img->height - maxSize.y)};
					Vector2 destPos = transform.pos(NoGUI::Align(0, 0));
					if ( img.scale.x <  0 )
					{
						sourcePos.x = img.scrollPos.x * (img.img->width + maxSize.x);
						destSize.x *= -1;
					}
					if ( img.scale.y <  0 )
					{
						sourcePos.y = img.scrollPos.y * (img.img->height + maxSize.y);
						destSize.y *= -1;
					}
					if ( isMax )
					{
						sourceSize = {maxSize.x - maxSize.x * (1.0f - 1.0f / img.scale.x), maxSize.y - maxSize.y * (1.0f - 1.0f / img.scale.y)};
						sourcePos = {img.scrollPos.x * (img.img->width - sourceSize.x), img.scrollPos.y * (img.img->height - sourceSize.y)};
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
						// scroll bars
						float scrollBarSize = 3;
						std::shared_ptr< NoGUI::Fill > barCol = std::make_shared< NoGUI::Fill >(shape->fill->hoverCol);
						std::shared_ptr< NoGUI::Fill > outlineCol = std::make_shared< NoGUI::Fill >(BLACK);
						std::shared_ptr< NoGUI::Outline > barOutline = std::make_shared< NoGUI::Outline >(outlineCol, 1);
						std::shared_ptr< NoGUI::Fill > cursorCol = std::make_shared< NoGUI::Fill >(shape->outline->fill->col, shape->outline->fill->hoverCol);
						NoGUI::nShape barShape = {4, barCol, barOutline};
						NoGUI::nShape cursorShape = {4, cursorCol, barOutline};
						
						if ( diff.y > 0 )
						{
							Vector2 scrollBarPos = transform.pos(NoGUI::Align(1, 0));
							scrollBarPos.x -= scrollBarSize;
							float percentShown = maxSize.y / imgSize.y;
							float percentCropped = 1 - percentShown;
							Vector2 scrollCursorPos = {scrollBarPos.x, scrollBarPos.y};
							scrollCursorPos.y += (img.scrollPos.y - 0.5) * percentCropped * transform.size().y;
							float scrollCursorSize = percentShown * transform.size().y;
							if (shape->fill)
							{
								DrawShape(barShape, scrollBarPos, (Vector2){scrollBarSize, transform.radius.y}, (Vector2){0, 0}, transform.angle);
								DrawShape(cursorShape, scrollCursorPos, (Vector2){scrollBarSize, scrollCursorSize / 2}, (Vector2){0, 0}, transform.angle);
							}
						
						}
						if ( diff.x > 0 )
						{
							Vector2 scrollBarPos = transform.pos(NoGUI::Align(0, 1));
							scrollBarPos.y -= scrollBarSize;
							float percentShown = maxSize.x / imgSize.x;
							float percentCropped = 1 - percentShown;
							Vector2 scrollCursorPos = {scrollBarPos.x, scrollBarPos.y};
							scrollCursorPos.x += (img.scrollPos.x - 0.5) * percentCropped * transform.size().x;
							float scrollCursorSize = percentShown * transform.size().x;
							if (shape->fill)
							{
								DrawShape(barShape, scrollBarPos, (Vector2){transform.radius.x, scrollBarSize}, (Vector2){0, 0}, transform.angle);
								DrawShape(cursorShape, scrollCursorPos, (Vector2){scrollCursorSize / 2, scrollBarSize}, (Vector2){0, 0}, transform.angle);
							}
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
						texcoords[i] = (Vector2){0.5f + sin * (0.5f - umod), 0.5f + cos * (0.5f - vmod)};
						
						centralAngle += 360.0f / (float)shape->n;
					}
					// create copy to rotate coordnites
					Vector2 positions[max] = { 0 };
					for (int i=0; i < max; i++) 
					{	
						positions[i] = Vector2Rotate(points[i], transform.angle*DEG2RAD);
					}
			
					DrawTexturePoly((*img.img), transform.pos(NoGUI::Align(0, 0)), positions, texcoords, max, img.col);
			
					break;
				}
			}
			
			
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
	// TODO: account for angle
	Vector2 ret = position;
	int xdes = static_cast< int >(originPoint.x);
	int ydes = static_cast< int >(originPoint.y);
	
//	Vector2 coords = {xdes * radius.x + position.x, ydes * radius.y + position.y};
//	dest = Vector2RotateAround(coords, position, angle);
//	dest.x -= position.x;
//	dest.y -= position.y;
	
//	Vector2 dir = {xdes * radius.x, ydes * radius.y};
//	if ( angle == 0 )
//	{
//		dest = dir;
//	}
//	else
//	{
//		float mag = Vector2Length(dir);
//		float dirAngle = atan2f(ydes * -1, xdes) * RAD2DEG;
//		dirAngle -= angle;
//		dest = {mag * cosf(dirAngle * DEG2RAD), mag * sinf(dirAngle * DEG2RAD)};
//	}
	
	if (xdes == 0 && ydes == 0)
	{
		ret.x -= offset().x;
		ret.y -= offset().y;
	}
	else
	{
		Vector2 dest = {xdes * radius.x, ydes * radius.y};
		Vector2 curr = offset();
		
		ret.x += dest.x - curr.x;
		ret.y += dest.y - curr.y;
	}

	return ret;
}

Vector2 NoGUI::Transform::size() const
{
	Vector2 ret;
	ret.x = radius.x * 2;
	ret.y = radius.y * 2;
	
	return ret;
}

float NoGUI::Transform::width() const
{

	return radius.x * 2;
}

float NoGUI::Transform::height() const
{
			
	return radius.y * 2;
}

Vector2 NoGUI::Transform::offset() const
{
	// TODO: account for angle
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
//			direction = angle;
			if ( mag > 0 )
			{
				mag *= -1;
			}
		}
		else if ( off.y == 0 )
		{
			mag = off.x;
//			direction = angle;
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
		Vector2 translate = pos(originPoint);
		translate.x -= position.x;
		translate.y -= position.y;
		newPos.x -= translate.x;
		newPos.y -= translate.y;
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
	position.x += posInc.x;
	position.y += posInc.y;
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
