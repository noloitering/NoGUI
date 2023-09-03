#include <iostream>
#include <vector>

#include "../../../../src/GUI.h"

int main(int argc, char ** argv)
{
	// initialization
	Vector2 window = {1280, 720};
	Vector2 elemSize = {100, 100};
	std::vector< std::shared_ptr< NoGUI::Element > > elemVec;
	char msg[NoMAD::INBUFF];
	int msgLength = 0;
	TextAppend(msg, "test", &msgLength);
	
	InitWindow(window.x, window.y, "test");
	SetTargetFPS(60);
	
	std::shared_ptr< NoGUI::Fill > fill = std::make_shared< NoGUI::Fill >(GRAY);
	std::shared_ptr< NoGUI::Fill > noFill = std::make_shared< NoGUI::Fill >((Color){0, 0, 0, 0});
	std::shared_ptr< NoGUI::Fill > lineFill = std::make_shared< NoGUI::Fill >(BLUE);
	std::shared_ptr< NoGUI::Outline > outline = std::make_shared< NoGUI::Outline >(lineFill, 3);
	std::shared_ptr< NoGUI::nShape > rect = std::make_shared< NoGUI::nShape >(4, fill, outline);
	std::shared_ptr< NoGUI::nShape > tipShape = std::make_shared< NoGUI::nShape >(4, noFill);
	std::shared_ptr< Font > font = nullptr;
	NoGUI::Wrap wrap = NoGUI::Wrap::DOWN;
	if ( argc > 1 )
	{
		font = std::make_shared< Font >(LoadFont(argv[1]));
	}
	else
	{
		font = std::make_shared< Font >(GetFontDefault());
	}
	
	NoGUI::Align left = NoGUI::Align(-1, -1);
	NoGUI::Align top = NoGUI::Align(0, -1);
	NoGUI::Align right = NoGUI::Align(1, -1);
	NoGUI::Align centerLeft = NoGUI::Align(-1, 0);
	NoGUI::Align center = NoGUI::Align(0, 0);
	NoGUI::Align centerRight = NoGUI::Align(1, 0);
	NoGUI::Align bottomLeft = NoGUI::Align(-1, 1);
	NoGUI::Align bottom = NoGUI::Align(0, 1);
	NoGUI::Align bottomRight = NoGUI::Align(1, 1);
	
	NoGUI::Transform dataT = NoGUI::Transform((Vector2){(elemSize.x + window.x / 2) / 2, window.y / 2}, elemSize, center);
	NoGUI::Transform toggleT = NoGUI::Transform((Vector2){(elemSize.x * 2 + window.x / 2), window.y / 2}, elemSize, center);
	NoGUI::Transform leftPos = NoGUI::Transform((Vector2){0, 0}, elemSize, left);
	NoGUI::Transform topPos = NoGUI::Transform((Vector2){window.x / 2, 0}, elemSize, top);
	NoGUI::Transform rightPos = NoGUI::Transform((Vector2){window.x, 0}, elemSize, right);
	NoGUI::Transform centerLeftPos = NoGUI::Transform((Vector2){0, window.y / 2}, elemSize, centerLeft);
	NoGUI::Transform centerRightPos = NoGUI::Transform((Vector2){window.x, window.y / 2}, elemSize, centerRight);
	NoGUI::Transform centerPos = NoGUI::Transform((Vector2){window.x / 2, window.y / 2}, elemSize, center);
	NoGUI::Transform bottomLeftPos = NoGUI::Transform((Vector2){0, window.y}, elemSize, bottomLeft);
	NoGUI::Transform bottomPos = NoGUI::Transform((Vector2){window.x / 2, window.y}, elemSize, bottom);
	NoGUI::Transform bottomRightPos = NoGUI::Transform((Vector2){window.x, window.y}, elemSize, bottomRight);

	std::shared_ptr< NoGUI::Element > dataElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, tipShape, dataT, std::make_shared< NoGUI::CContainer >(), "Tip");
	std::shared_ptr< NoGUI::Element > toggleElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, tipShape, toggleT, std::make_shared< NoGUI::CContainer >(), "Tip", "Wrap DOWN");
	std::shared_ptr< NoGUI::Element > leftElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, leftPos, std::make_shared< NoGUI::CContainer >(), "Test", msg);
	std::shared_ptr< NoGUI::Element > topElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, topPos, std::make_shared< NoGUI::CContainer >(), "Test", msg);
	std::shared_ptr< NoGUI::Element > rightElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, rightPos, std::make_shared< NoGUI::CContainer >(), "Test", msg);
	std::shared_ptr< NoGUI::Element > centerElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, centerPos, std::make_shared< NoGUI::CContainer >(), "Test", msg);
	std::shared_ptr< NoGUI::Element > centerLeftElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, centerLeftPos, std::make_shared< NoGUI::CContainer >(), "Test", msg);
	std::shared_ptr< NoGUI::Element > centerRightElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, centerRightPos, std::make_shared< NoGUI::CContainer >(), "Test", msg);
	std::shared_ptr< NoGUI::Element > bottomElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, bottomPos, std::make_shared< NoGUI::CContainer >(), "Test", msg);
	std::shared_ptr< NoGUI::Element > bottomLeftElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, bottomLeftPos, std::make_shared< NoGUI::CContainer >(), "Test", msg);
	std::shared_ptr< NoGUI::Element > bottomRightElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, bottomRightPos, std::make_shared< NoGUI::CContainer >(), "Test", msg);
	dataElem->components->addComponent< NoGUI::CText >();
	toggleElem->components->addComponent< NoGUI::CText >();
	leftElem->components->addComponent< NoGUI::CText >(nullptr, font, 20, left, wrap);
	topElem->components->addComponent< NoGUI::CText >(nullptr, font, 20, top, wrap);
	rightElem->components->addComponent< NoGUI::CText >(nullptr, font, 20, right, wrap);
	centerElem->components->addComponent< NoGUI::CText >(nullptr, font, 20, center, wrap);
	centerLeftElem->components->addComponent< NoGUI::CText >(nullptr, font, 20, centerLeft, wrap);
	centerRightElem->components->addComponent< NoGUI::CText >(nullptr, font, 20, centerRight, wrap);
	bottomElem->components->addComponent< NoGUI::CText >(nullptr, font, 20, bottom, wrap);
	bottomLeftElem->components->addComponent< NoGUI::CText >(nullptr, font, 20, bottomLeft, wrap);
	bottomRightElem->components->addComponent< NoGUI::CText >(nullptr, font, 20, bottomRight, wrap);
	
	elemVec.push_back(dataElem);
	elemVec.push_back(toggleElem);
	elemVec.push_back(leftElem);
	elemVec.push_back(topElem);
	elemVec.push_back(rightElem);
	elemVec.push_back(centerElem);
	elemVec.push_back(centerLeftElem);
	elemVec.push_back(centerRightElem);
	elemVec.push_back(bottomLeftElem);
	elemVec.push_back(bottomElem);
	elemVec.push_back(bottomRightElem);
	// main
	while ( !WindowShouldClose() )
	{
		bool rElemLeft = false;
		bool rElemRight = false;
		bool rTxtLeft = false;
		bool rTxtRight = false;
		bool addLine = false;
		float translateX = 0.0f;
		float translateY = 0.0f;
		float scroll = GetMouseWheelMove();
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		{
			if ( IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT) )
			{
				rTxtLeft = true;
			}
			else
			{
				rElemLeft = true;
			}
		}
		else if ( IsMouseButtonDown(MOUSE_RIGHT_BUTTON) )
		{
			if ( IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT) )
			{
				rTxtRight = true;
			}
			else
			{
				rElemRight = true;
			}
		}
		if ( IsKeyDown(KEY_LEFT) )
		{
			translateX -= 1.0f;
		}
		else if ( IsKeyDown(KEY_RIGHT) )
		{
			translateX += 1.0f;
		}
		if ( IsKeyDown(KEY_DOWN) )
		{
			translateY -= 1.0f;
		}
		else if ( IsKeyDown(KEY_UP) )
		{
			translateY += 1.0f;
		}
		if ( IsKeyPressed(KEY_ENTER) )
		{
			TextAppend(msg, "\ntest", &msgLength);
			addLine = true;
		}
		if ( IsKeyPressed(KEY_SPACE) )
		{
			for (auto elem : elemVec)
			{
				if (!TextIsEqual(elem->getTag(), "Tip"))
				{
					NoGUI::CText& txtComp = elem->components->getComponent< NoGUI::CText >();
					if ( txtComp.wrap == NoGUI::Wrap::UP )
					{
						txtComp.wrap = NoGUI::Wrap::DOWN;
						toggleElem->setInner("Wrap DOWN");
					}
					else
					{
						txtComp.wrap = NoGUI::Wrap::UP;
						toggleElem->setInner("Wrap UP");
					}
				}
			}
		}
		
		dataElem->setInner(TextFormat("Element Angle: %03.02f\nText Angle: %03.02f\nText Size: %01.01f\nHorizontal Spacing: %01.01f\nVertical Spacing: %01.01f", centerElem->angle, centerElem->components->getComponent< NoGUI::CText >().angle, centerElem->components->getComponent< NoGUI::CText >().size, centerElem->components->getComponent< NoGUI::CText >().spacing.x, centerElem->components->getComponent< NoGUI::CText >().spacing.y));
		
		BeginDrawing();
			ClearBackground(BLACK);
			for ( auto elem : elemVec )
			{
				if (!TextIsEqual(elem->getTag(), "Tip"))
				{
					NoGUI::CText& txtComp = elem->components->getComponent< NoGUI::CText >();
					txtComp.spacing.x += translateX;
					txtComp.spacing.y += translateY;
					if ( scroll )
					{
						txtComp.size += 1.0f * scroll;
					}
					if ( addLine )
					{
						elem->setInner(msg);
					}
					if ( rElemLeft )
					{
						elem->rotate(-1, elem->origin);
					}
					else if ( rElemRight )
					{
						elem->rotate(1, elem->origin);
					}
					if ( rTxtLeft )
					{
						txtComp.angle -= 1.0f;
					}
					else if ( rTxtRight )
					{
						txtComp.angle += 1.0f;
					}
				}
				elem->draw();
			}
		EndDrawing();
	}
	
	return 0;
}