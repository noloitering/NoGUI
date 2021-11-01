#include "GUI.h"

using namespace NoGUI;

// Procedural functions
Vector2 NoGUI::alignTextLeft(const CText& fmt, const Style& elem, int lineNum)
{
	Vector2 result;
	int leftPos = elem.pos.x - elem.radius.x;
	int topPos = elem.pos.y - elem.radius.y;
	int newlineSpace = lineNum * (fmt.size + fmt.spacing.y) * static_cast< int >(fmt.wrap);
	
	result.x = leftPos + fmt.margin.x;
	result.y = topPos + fmt.margin.y + newlineSpace;
	
	return result;
}

// TODO: fix bugs
Vector2 NoGUI::alignTextCenter(const char* text, const CText& fmt, const Style& elem, int lineNum)
{
	Vector2 result;
	Font font = (fmt.font) ? (*fmt.font) : GetFontDefault();
	Vector2 textSize = MeasureTextEx(font, text, fmt.size, fmt.spacing.x);
	// weird bug
	int leftPos;
	if (elem.radius.x <= 25)
	{
		leftPos = elem.pos.x - textSize.x / 2 + 4;
	}
	else
	{
		leftPos = elem.pos.x - textSize.x / 2;
	}
	int topPos = elem.pos.y - textSize.y / 2;
	int newlineSpace = lineNum * (textSize.y + fmt.spacing.y) * static_cast< int >(fmt.wrap);

	result.x = leftPos + fmt.margin.x;
	result.y = topPos + fmt.margin.y + newlineSpace;
	
	return result;
}

Vector2 NoGUI::alignTextTop(const char* text, const CText& fmt, const Style& elem, int lineNum)
{
	Vector2 result;
	Font font = (fmt.font) ? (*fmt.font) : GetFontDefault();
	Vector2 textSize = MeasureTextEx(font, text, fmt.size, fmt.spacing.x);
	// weird bug
	int leftPos;
	if (elem.radius.x <= 25)
	{
		leftPos = elem.pos.x - textSize.x / 2 + 4;
	}
	else
	{
		leftPos = elem.pos.x - textSize.x / 2;
	}
	int topPos = elem.pos.y - elem.radius.y;
	int newlineSpace = lineNum * (textSize.y + fmt.spacing.y) * static_cast< int >(fmt.wrap);

	result.x = leftPos + fmt.margin.x;
	result.y = topPos + fmt.margin.y + newlineSpace;
	
	return result;
}

Vector2 NoGUI::alignTextBottom(const char* text, const CText& fmt, const Style& elem, int lineNum)
{
	Vector2 result;
	Font font = (fmt.font) ? (*fmt.font) : GetFontDefault();
	Vector2 textSize = MeasureTextEx(font, text, fmt.size, fmt.spacing.x);
	// weird bug
	int leftPos;
	if (elem.radius.x <= 25)
	{
		leftPos = elem.pos.x - textSize.x / 2 + 4;
	}
	else
	{
		leftPos = elem.pos.x - textSize.x / 2;
	}
	int topPos = elem.pos.y + elem.radius.y - textSize.y;
	int newlineSpace = lineNum * (textSize.y + fmt.spacing.y) * static_cast< int >(fmt.wrap);

	result.x = leftPos + fmt.margin.x;
	result.y = topPos + fmt.margin.y + newlineSpace;
	
	return result;
}

Vector2 NoGUI::alignTextBottomLeft(const char* text, const CText& fmt, const Style& elem, int lineNum)
{
	Vector2 result;
	Font font = (fmt.font) ? (*fmt.font) : GetFontDefault();
	Vector2 textSize = MeasureTextEx(font, text, fmt.size, fmt.spacing.x);
	int leftPos = elem.pos.x - elem.radius.x;
	int topPos = elem.pos.y + elem.radius.y - textSize.y;
	int newlineSpace = lineNum * (textSize.y + fmt.spacing.y) * static_cast< int >(fmt.wrap);

	result.x = leftPos + fmt.margin.x;
	result.y = topPos + fmt.margin.y + newlineSpace;
	
	return result;
}

Vector2 NoGUI::alignTextBottomRight(const char* text, const CText& fmt, const Style& elem, int lineNum)
{
	Vector2 result;
	Font font = (fmt.font) ? (*fmt.font) : GetFontDefault();
	Vector2 textSize = MeasureTextEx(font, text, fmt.size, fmt.spacing.x);
	int leftPos;
	// weird bug
	if (elem.radius.x <= 25)
	{
		leftPos = elem.pos.x + elem.radius.x - textSize.x;
	}
	else
	{
		leftPos = elem.pos.x + elem.radius.x - textSize.x + 8;
	}
	int topPos = elem.pos.y + elem.radius.y - textSize.y;
	int newlineSpace = lineNum * (textSize.y + fmt.spacing.y) * static_cast< int >(fmt.wrap);

	result.x = leftPos + fmt.margin.x;
	result.y = topPos + fmt.margin.y + newlineSpace;
	
	return result;
}

Vector2 NoGUI::alignTextRight(const char* text, const CText& fmt, const Style& elem, int lineNum)
{
	Vector2 result;
	Font font = (fmt.font) ? (*fmt.font) : GetFontDefault();
	Vector2 textSize = MeasureTextEx(font, text, fmt.size, fmt.spacing.x);
	int leftPos;
	// weird bug
	if (elem.radius.x <= 25)
	{
		leftPos = elem.pos.x + elem.radius.x - textSize.x;
	}
	else
	{
		leftPos = elem.pos.x + elem.radius.x - textSize.x + 8;
	}
	int topPos = elem.pos.y - elem.radius.y;
	int newlineSpace = lineNum * (textSize.y + fmt.spacing.y) * static_cast< int >(fmt.wrap);

	result.x = leftPos + fmt.margin.x;
	result.y = topPos + fmt.margin.y + newlineSpace;
	
	return result;
}

Vector2 NoGUI::alignText(const char* text, const CText& fmt, const Style& elem, int lineNum)
{
	Vector2 result;

	switch (fmt.align)
	{
		case TextAlign::LEFT:
		{
			result = alignTextLeft(fmt, elem, lineNum);
			
			break;
		}
		
		case TextAlign::CENTER:
		{
			result = alignTextCenter(text, fmt, elem, lineNum);
			
			break;
		}
		
		case TextAlign::RIGHT:
		{
			result = alignTextRight(text, fmt, elem, lineNum);
			
			break;
		}
		
		case TextAlign::TOP:
		{
			result = alignTextTop(text, fmt, elem, lineNum);
			
			break;
		}
		
		case TextAlign::BOTTOM:
		{
			result = alignTextBottom(text, fmt, elem, lineNum);
			
			break;
		}
		
		case TextAlign::BOTTOML:
		{
			result = alignTextBottomLeft(text, fmt, elem, lineNum);
			
			break;
		}
		
		case TextAlign::BOTTOMR:
		{
			result = alignTextBottomRight(text, fmt, elem, lineNum);
			
			break;
		}
	}
	
	return result;
}

// TODO: refactor
std::vector<std::string> NoGUI::wrapText(const char* text, const CText& fmt, int width)
{
	std::vector<std::string> result;
	std::string line = std::string();
	std::string copy = std::string();
	Font font = (fmt.font) ? (*fmt.font) : GetFontDefault();
	int numWords = 0;
	int lineIndex = 0;
	const char **words = TextSplit(text, ' ', &numWords); // changes numWords
	for (int i=0; i < numWords; i++)
	{
		line.append(words[i]);
		line.append(" ");
		if ( MeasureTextEx(font, line.c_str(), fmt.size, fmt.spacing.x).x > width )
		{
			if ( i != lineIndex ) // check to see if it's a single word that's too big
			{
//				result.push_back(line.substr(0, line.rfind(" ")));
				int lineEnd = --i;
				for (; lineIndex < lineEnd; lineIndex++)
				{
					copy.append(words[lineIndex]);
					copy.append(" ");
					words[lineIndex] = "";
				}
				result.push_back(copy);
				line = std::string();
				copy = std::string();
			}
			else
			{
				copy.append(words[lineIndex]);
				words[lineIndex] = "";
				result.push_back(copy);
				copy = std::string();
				line = std::string();
				lineIndex++;
			}
		}
	}
	// get the last line
	if ( lineIndex < numWords)
	{
		for (; lineIndex < numWords; lineIndex++)
		{
			copy.append(words[lineIndex]);
			copy.append(" ");
		}
		result.push_back(copy);
	}
	
	return result;
}

void NoGUI::DrawGUIElement(Element* elem)
{
	Style shape = elem->styling();
	if ( elem->getHover() )
	{
		shape.backCol = elem->getHoverCol();
	}
	DrawGUIShape(shape);
	if ( elem->hasComponent< CText >() )
	{
		CText txtFmt = elem->getComponent< CText >();
		if ( txtFmt.contents.empty() )
		{
			txtFmt.contents = wrapText(elem->getInner().c_str(), txtFmt, elem->styling().radius.x * 2 - txtFmt.margin.x);
		}
		DrawGUITextWrapped(txtFmt.contents, elem->getComponent< CText >(), elem->styling());
	}
	if ( elem->hasComponent< CImage >() )
	{
		CImage imgFmt = elem->getComponent< CImage >();
		DrawGUIImage(imgFmt, elem->styling());
	}
	if ( elem->hasComponent< CMultiStyle >() )
	{
		std::vector< Style > children = elem->getComponent< CMultiStyle >().styles;
		Vector2 origin = shape.pos;
		for (auto child : children)
		{
			shape = child;
			shape.pos.x = origin.x + shape.pos.x;
			shape.pos.y = origin.y + shape.pos.y;
			DrawGUIShape(shape);
		}
	}
}

void NoGUI::DrawGUIShape(const Style& elem)
{
	switch (elem.sides)
	{
		case 0:
		{
			// TODO: rotation
			DrawEllipse(elem.pos.x, elem.pos.y, elem.radius.x, elem.radius.y, elem.backCol);
			for (int i=0; i < elem.outlineThick; i++)
			{
				DrawEllipseLines(elem.pos.x, elem.pos.y, elem.radius.x + i, elem.radius.y + i, elem.outlineCol);
			}
			
			break;
		}
		
		case 1:
		{
			DrawPixelV(elem.pos, elem.backCol);
			
			break;
		}
		
		case 2:
		{
			// TODO: rotation
			Vector2 startPos;
			Vector2 endPos;
			startPos.x = elem.pos.x - elem.radius.x;
			startPos.y = elem.pos.y - elem.radius.y;
			endPos.x = elem.pos.x + elem.radius.x;
			endPos.y = elem.pos.y + elem.radius.y;
			DrawLineEx(startPos, endPos, elem.outlineThick, elem.backCol);
		
			break;
		}
		
		case 3:
		{
			// TODO: rotation
			Vector2 left = (Vector2){elem.pos.x - elem.radius.x, elem.pos.y + elem.radius.y};
			Vector2 top = (Vector2){elem.pos.x, elem.pos.y - elem.radius.y};
			Vector2 right = (Vector2){elem.pos.x + elem.radius.x, elem.pos.y + elem.radius.y};
			DrawTriangle(top, left, right, elem.backCol);
			Vector2 ldx = left;
			Vector2 tdx = top;
			Vector2 rdx = right;
			// TODO: fix outline
			for (int i=0; i < elem.outlineThick; i++)
			{
				ldx.x--;
//				ldx.y += i;
				tdx.y--;
//				rdx.y += i;
				rdx.x++;
				DrawTriangleLines(tdx, ldx, rdx, elem.outlineCol);
			}
			if ( elem.outlineThick )
			{
				ldx.y += elem.outlineThick / 2;
				rdx.y += elem.outlineThick / 2;
				DrawLineEx(ldx, rdx, elem.outlineThick, elem.outlineCol);
			}
			
			break;
		}
		
		case 4:
		{
			Rectangle render = (Rectangle){elem.pos.x - elem.radius.x, elem.pos.y - elem.radius.y, elem.radius.x * 2, elem.radius.y * 2};
			Vector2 origin = {0, 0};
			DrawRectanglePro(render, origin, elem.rotation, elem.backCol);
			for (int i=0; i < elem.outlineThick; i++)
			{
				DrawRectangleLines(render.x - i, render.y - i, render.width + i * 2, render.height + i * 2, elem.outlineCol);
			}
			
			break;
		}
		
		default:
		{
			DrawPoly(elem.pos, elem.sides, elem.radius.x, elem.rotation, elem.backCol);
			for (int i=0; i < elem.outlineThick; i++)
			{
				DrawPolyLines(elem.pos, elem.sides, elem.radius.x + i, elem.rotation, elem.outlineCol);
			}
			
			
			break;
		}
	}
}

// TODO: rotate text around center
void NoGUI::DrawGUITextV(const char* text, const CText& fmt, const Vector2& pos)
{
	Font font = (fmt.font) ? (*fmt.font) : GetFontDefault();
	Vector2 origin = {0, 0};
	
	if ( fmt.shadow.draw )
	{
		Vector2 shadowPos = pos;
		shadowPos.x += fmt.shadow.offset.x;
		shadowPos.y += fmt.shadow.offset.y;
		DrawTextPro(font, text, shadowPos, origin, fmt.rotation, fmt.size, fmt.spacing.x, fmt.shadow.col);
	}
	DrawTextPro(font, text, pos, origin, fmt.rotation, fmt.size, fmt.spacing.x, fmt.col);
}

// TODO: not aligning when there are 2 words
void NoGUI::DrawGUITextWrapped(const std::vector<std::string>& text, const CText& fmt, const Style& elem)
{
	Vector2 textPos;
	switch (fmt.align)
	{
		case TextAlign::LEFT:
		{
			for (unsigned int i = 0; i < text.size(); i++)
			{
				textPos = alignTextLeft(fmt, elem, i);
				DrawGUITextV(text[i].c_str(), fmt, textPos);
			}
			
			break;
		}
		
		case TextAlign::CENTER:
		{
			for (unsigned int i = 0; i < text.size(); i++)
			{
				textPos = alignTextCenter(text[i].c_str(), fmt, elem, i);
				DrawGUITextV(text[i].c_str(), fmt, textPos);
			}
			
			break;
		}
		
		case TextAlign::RIGHT:
		{
			for (unsigned int i = 0; i < text.size(); i++)
			{
				textPos = alignTextRight(text[i].c_str(), fmt, elem, i);
				DrawGUITextV(text[i].c_str(), fmt, textPos);
			}
			
			break;
		}
		
		case TextAlign::TOP:
		{
			for (unsigned int i = 0; i < text.size(); i++)
			{
				textPos = alignTextTop(text[i].c_str(), fmt, elem, i);
				DrawGUITextV(text[i].c_str(), fmt, textPos);
			}
			
			break;
		}
		
		case TextAlign::BOTTOM:
		{
			for (unsigned int i = 0; i < text.size(); i++)
			{
				textPos = alignTextBottom(text[i].c_str(), fmt, elem, i);
				DrawGUITextV(text[i].c_str(), fmt, textPos);
			}
			
			break;
		}
		
		case TextAlign::BOTTOML:
		{
			for (unsigned int i = 0; i < text.size(); i++)
			{
				textPos = alignTextBottomLeft(text[i].c_str(), fmt, elem, i);
				DrawGUITextV(text[i].c_str(), fmt, textPos);
			}
			
			break;
		}
		
		case TextAlign::BOTTOMR:
		{
			for (unsigned int i = 0; i < text.size(); i++)
			{
				textPos = alignTextBottomRight(text[i].c_str(), fmt, elem, i);
				DrawGUITextV(text[i].c_str(), fmt, textPos);
			}
			
			break;
		}
	}
}

void NoGUI::DrawGUIText(const char * text, const CText& fmt, const Style& elem)
{
	switch(fmt.wrap)
	{
		case TextWrap::NONE:
		{
			Vector2 textPos = alignText(text, fmt, elem);
			DrawGUITextV(text, fmt, textPos);
			
			break;
		}

		default:
		{
			int elemSize = elem.radius.x * 2 - fmt.margin.x;
			std::vector<std::string> lines = wrapText(text, fmt, elemSize);
			DrawGUITextWrapped(lines, fmt, elem);

			break;
		}
	}
}

void NoGUI::DrawGUIImage(const CImage& fmt, const Style& elem)
{
	if ( fmt.texture )
	{
		Vector2 imgPos;
		// rotate and position about the center
		imgPos.x = elem.pos.x + fmt.margin.x;
		imgPos.y = elem.pos.y + fmt.margin.y;
		Rectangle source = {0, 0, fmt.texture->width, fmt.texture->height};
		Rectangle dest = {imgPos.x, imgPos.y, fmt.texture->width * fmt.scale.x, fmt.texture->height * fmt.scale.y};
		
		if ( fmt.cropping == Crop::FIT )
		{
			Vector2 maxArea;
			maxArea.x = elem.radius.x * 2 - abs(fmt.margin.x);
			maxArea.y = elem.radius.y * 2 - abs(fmt.margin.y);
			dest.width =  ( dest.width > maxArea.x ) ? maxArea.x : dest.width;
			dest.height =  ( dest.height > maxArea.y ) ? maxArea.y : dest.width;
		}
		Vector2 origin = (Vector2){dest.width / 2, dest.height / 2}; // rotate and position about the center
		DrawTexturePro((*fmt.texture), source, dest, origin, fmt.rotation, fmt.col);
	}
}

// Element object
bool Element::isFocus()
{
	
	return getFocus();
}

bool Element::getFocus()
{
	
	return focus;
}

bool Element::getHover()
{
	
	return hover;
}

bool Element::isActive()
{

	return active;
}

bool Element::isAlive()
{
	
	return alive;
}

bool Element::isHover()
{
	Vector2 mousePos = GetMousePosition();
	switch (style.sides)
	{
		case 0:
		{
			Rectangle collider = (Rectangle){style.pos.x - style.radius.x, style.pos.y - style.radius.y, style.radius.x * 2, style.radius.y * 2};
			float radius = ( style.radius.x > style.radius.y ) ? style.radius.x : style.radius.y;
			
			hover = CheckCollisionPointRec(mousePos, collider) && CheckCollisionPointCircle(GetMousePosition(), style.pos, radius);
			
			break;
		}
		
		case 1:
		{			
			hover = mousePos.x == style.pos.x && mousePos.y == style.pos.y;
		
			break;
		}
		
		case 2:
		{
			Vector2 startPos = {style.pos.x - style.radius.x, style.pos.y - style.radius.y};
			Vector2 endPos = {style.pos.x + style.radius.x, style.pos.y + style.radius.y};
			hover = CheckCollisionPointLine(mousePos, startPos, endPos, 1 + style.outlineThick);
		
			break;
		}
		
		case 3:
		{
			Vector2 p1;
			p1.x = style.pos.x - style.radius.x;
			p1.y = style.pos.y + style.radius.y;
			Vector2 p2;
			p2.x = style.pos.x;
			p2.y = style.pos.y - style.radius.y;
			Vector2 p3;
			p3.x = style.pos.x + style.radius.x;
			p3.y = style.pos.y + style.radius.y;
			hover = CheckCollisionPointTriangle(mousePos, p1, p2, p3);
			
			break;
		}
		
		case 4:
		{
			Rectangle collider = (Rectangle){style.pos.x - style.radius.x, style.pos.y - style.radius.y, style.radius.x * 2, style.radius.y * 2};
			hover = CheckCollisionPointRec(mousePos, collider);
			
			break;
		}
		
		default:
		{
			hover = CheckCollisionPointCircle(mousePos, style.pos, style.radius.x);
		
			break;
		}
	}

	return hover;
}

Color Element::getHoverCol()
{
	
	return hoverCol;
}

void Element::setHoverCol(const Color& col)
{
	hoverCol = col;
}

std::string Element::getInner()
{

	return inner;
}

void Element::setInner(const std::string& in)
{
	inner = in;
	if ( hasComponent< CText >() )
	{
		CText txtFmt = getComponent< CText >();
		txtFmt.contents = wrapText(inner.c_str(), txtFmt, style.radius.x * 2 - txtFmt.margin.x);
	}
}

Style Element::styling()
{
	
	return style;
}

void Element::draw()
{
	DrawGUIElement(this);
}

void Element::kill()
{
	alive = false;
}

void Element::repos(const Vector2& newPos)
{
	style.pos = newPos;
}

void Element::resize(const Vector2& newRadi)
{
	style.radius = newRadi;
}

void Element::recol(const Color& newBack, const Color& newHover)
{
	style.backCol = newBack;
	hoverCol = newHover;
}

void Element::reshape(int newSides)
{
	style.sides = newSides;
}


void Element::rotate(float rotation)
{
	style.rotation = rotation;
}

bool Button::isFocus()
{
	focus = false;
	if ( active )
	{
		if ( isHover() )
		{
			focus = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
		}
	}
	
	return focus;
}

// Pages
Page::Page(bool init)
{
	active = init;
}

bool Page::isActive()
{
	
	return active;
}

void Page::setActive(bool set)
{
	active = set;
}

// TODO: clean up your loops
void Page::removeElement(size_t id)
{
	for (auto it=elements.begin(); it != elements.end(); it++)
	{
		for (int elemIndex=0; elemIndex < it->second.size(); elemIndex++)
		{
			if ( it->second[elemIndex]->id == id )
			{
				it->second[elemIndex]->kill();
				
				return;
			}
		}
	}
}

void Page::clearElements()
{
	for (auto it=elements.begin(); it != elements.end(); it++)
	{
		for (int elemIndex=0; elemIndex < it->second.size(); elemIndex++)
		{
			it->second[elemIndex]->kill();
		}
	}
}

std::shared_ptr< Element > Page::getElement(size_t id)
{
	for (auto it=elements.begin(); it != elements.end(); it++)
	{
		for (int elemIndex=0; elemIndex < it->second.size(); elemIndex++)
		{
			if ( it->second[elemIndex]->id == id )
			{

				return it->second[elemIndex];
			}
		}
	}
	
	return nullptr;
}

std::vector< std::shared_ptr< Element > > Page::getElements(const std::string& tag)
{
	
	return elements[tag];
}

std::vector< std::shared_ptr< Element > > Page::getElements()
{
	std::vector< std::shared_ptr< Element > > result;
	
	for (auto it=elements.begin(); it != elements.end(); it++)
	{
		for (std::shared_ptr< Element > e : it->second)
		{
			result.push_back(e);
		}
	}
	
	return result;
}

void Page::update()
{
	std::map< std::string, std::vector< std::shared_ptr< Element > > > new_map;
	for (auto me : elements)
	{
		for (int elemIndex=0; elemIndex < me.second.size(); elemIndex++)
		{
			auto e = me.second[elemIndex];
			if ( e->isAlive() )
			{
				new_map[me.first].push_back(e);
			}
		}
	}
	if ( !toAdd.empty() )
	{
		for (auto a : toAdd)
		{
			if ( !a.second.empty() )
			{
				for (auto e : a.second)
				{
					new_map[a.first].push_back(e);
				}
			}
		}
		toAdd.clear();
	}
	elements = new_map;
}

size_t Page::size()
{

	return elements.size();
}

// GUI Manager
GUIManager::GUIManager()
{
	addPage(true);
}

void GUIManager::removeElement(size_t id, int pageIndex)
{
	
	return pages[pageIndex]->removeElement(id);
}

std::shared_ptr< Page > GUIManager::addPage(bool active)
{
	auto e = std::shared_ptr< Page >(new Page(active));
	pages.push_back(e);
	
	return e;
}

std::shared_ptr< Page > GUIManager::getPage(int pageIndex)
{
	
	return pages[pageIndex];
}

size_t GUIManager::size()
{
	
	return pages.size();
}

void GUIManager::removePage(int pageIndex)
{
	pages.erase(pages.begin() + pageIndex - 1);
}

void GUIManager::update()
{
	for (auto page : pages)
	{
		page->update();
		if ( page->isActive() )
		{
			for (auto elem : page->getElements())
			{
				if ( elem->isFocus() )
				{
					notify(elem);
				}
				if ( elem->hasComponent< CInput >() )
				{
					if ( elem->isHover() )
					{
						notify(elem);
					}
				}
			}
		}
	}
}

void GUIManager::render()
{
	for (auto page : pages)
	{
		if ( page->isActive() )
		{	
			for (auto e : page->getElements() )
			{
				e->draw();
			}
		}
	}	
}

void GUIManager::setActive(size_t index)
{
	for (auto page : pages)
	{
		page->setActive(false);
	}
	pages[index]->setActive(true);
}
