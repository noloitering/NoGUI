#include "../../../src/GUI.h"

int main(int argc, char ** argv)
{
	// initialization
	Vector2 window = {1280, 720};
//	Vector2 elemSize = {100, 50};
	Vector2 elemSize = {100, 100};
	std::vector< std::shared_ptr< NoGUI::Element > > elemVec;
	
	std::shared_ptr< NoGUI::Fill > fill = std::make_shared< NoGUI::Fill >(RAYWHITE, GRAY);
	std::shared_ptr< NoGUI::Fill > outFill = std::make_shared< NoGUI::Fill >(BLUE, RED);
	std::shared_ptr< NoGUI::Fill > focusFill = std::make_shared< NoGUI::Fill >(RED, MAROON);
	std::shared_ptr< NoGUI::Fill > noFill = std::make_shared< NoGUI::Fill >((Color){0, 0, 0, 0});
	std::shared_ptr< NoGUI::Outline > outline = std::make_shared< NoGUI::Outline >(outFill, 3);
	std::shared_ptr< NoGUI::nShape > tipShape = std::make_shared< NoGUI::nShape >(4, noFill, outline);
	std::shared_ptr< NoGUI::nShape > ellipse = std::make_shared< NoGUI::nShape >(0, fill, outline);
	std::shared_ptr< NoGUI::nShape > line = std::make_shared< NoGUI::nShape >(2, fill, outline);
	std::shared_ptr< NoGUI::nShape > triangle = std::make_shared< NoGUI::nShape >(3, fill, outline);
	std::shared_ptr< NoGUI::nShape > rect = std::make_shared< NoGUI::nShape >(4, fill, outline);
	std::shared_ptr< NoGUI::nShape > octagon = std::make_shared< NoGUI::nShape >(8, fill, outline);
	
	NoGUI::Transform leftT = NoGUI::Transform((Vector2){0, 0}, elemSize, NoGUI::Align(-1, -1));
	NoGUI::Transform topT = NoGUI::Transform((Vector2){window.x / 2, 0}, elemSize, NoGUI::Align(0, -1));
	NoGUI::Transform rightT = NoGUI::Transform((Vector2){window.x, 0}, elemSize, NoGUI::Align(1, -1));
	NoGUI::Transform centerT = NoGUI::Transform((Vector2){window.x / 2, window.y / 2}, elemSize, NoGUI::Align());
	NoGUI::Transform centerLeftT = NoGUI::Transform((Vector2){0, window.y / 2}, (Vector2){200, 100}, NoGUI::Align(-1, 0));
	NoGUI::Transform centerRightT = NoGUI::Transform((Vector2){window.x, window.y / 2}, (Vector2){200, 100}, NoGUI::Align(1, 0));
	NoGUI::Transform bottomLT = NoGUI::Transform((Vector2){0, window.y}, elemSize, NoGUI::Align(-1, 1));
	NoGUI::Transform bottomT = NoGUI::Transform((Vector2){window.x / 2, window.y}, elemSize, NoGUI::Align(0, 1));
	NoGUI::Transform bottomRT = NoGUI::Transform((Vector2){window.x, window.y}, elemSize, NoGUI::Align(1, 1));
	
	bottomT.radius.x = elemSize.y;
	bottomLT.radius.x = elemSize.y;
	bottomRT.radius.x = elemSize.y;
	
	std::shared_ptr< NoGUI::Element > dataElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, tipShape, centerLeftT, std::make_shared< NoGUI::CContainer >(), "Tip");
	std::shared_ptr< NoGUI::Element > shapeElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, tipShape, centerRightT, std::make_shared< NoGUI::CContainer >(), "Tip");
	std::shared_ptr< NoGUI::Element > leftElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ellipse, leftT);
	std::shared_ptr< NoGUI::Element > topElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, line, topT);
	std::shared_ptr< NoGUI::Element > rightElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, rightT);
	std::shared_ptr< NoGUI::Element > centerElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, triangle, centerT);
	std::shared_ptr< NoGUI::Element > bottomElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, octagon, bottomT);
	std::shared_ptr< NoGUI::Element > bottomLElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, bottomLT);
	std::shared_ptr< NoGUI::Element > bottomRElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ellipse, bottomRT);
	shapeElem->components->addComponent< NoGUI::CText >();
	dataElem->components->addComponent< NoGUI::CText >();
	shapeElem->setInner(TextFormat("click the\n%s elements!", argv[1]));
	if ( argc > 1 )
	{
		if ( strcasecmp(argv[1], "circle") == 0 )
		{
			leftT.radius.x = elemSize.y;
			topT.radius.x = elemSize.y;
			rightT.radius.x = elemSize.y;
			centerT.radius.x = elemSize.y;
			bottomT.radius.x = elemSize.y;
			bottomLT.radius.x = elemSize.y;
			bottomRT.radius.x = elemSize.y;
			leftElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ellipse, leftT);
			topElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ellipse, topT);
			rightElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ellipse, rightT);
			centerElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ellipse, centerT);
			bottomElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ellipse, bottomT);
			bottomLElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ellipse, bottomLT);
			bottomRElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ellipse, bottomRT);
		}
		else if ( strcasecmp(argv[1], "ellipse") == 0 )
		{
			bottomT.radius.x = bottomT.radius.y * 2;
			bottomLT.radius.x = bottomT.radius.y * 2;
			bottomRT.radius.x = bottomT.radius.y * 2;
			leftElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ellipse, leftT);
			topElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ellipse, topT);
			rightElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ellipse, rightT);
			centerElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ellipse, centerT);
			bottomElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ellipse, bottomT);
			bottomLElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ellipse, bottomLT);
			bottomRElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ellipse, bottomRT);
		}
		else if ( strcasecmp(argv[1], "line") == 0 )
		{
			leftElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, line, leftT);
			topElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, line, topT);
			rightElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, line, rightT);
			centerElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, line, centerT);
			bottomElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, line, bottomT);
			bottomLElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, line, bottomLT);
			bottomRElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, line, bottomRT);
		}
		else if ( strcasecmp(argv[1], "tri") == 0 )
		{
			leftT.radius.x = elemSize.y;
			topT.radius.x = elemSize.y;
			rightT.radius.x = elemSize.y;
			centerT.radius.x = elemSize.y;
			bottomT.radius.x = elemSize.y;
			bottomLT.radius.x = elemSize.y;
			bottomRT.radius.x = elemSize.y;
			leftElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, triangle, leftT);
			topElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, triangle, topT);
			rightElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, triangle, rightT);
			centerElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, triangle, centerT);
			bottomElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, triangle, bottomT);
			bottomLElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, triangle, bottomLT);
			bottomRElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, triangle, bottomRT);
		}
		else if ( strcasecmp(argv[1], "triangle") == 0 )
		{
			bottomT.radius.x = bottomT.radius.y * 2;
			bottomLT.radius.x = bottomT.radius.y * 2;
			bottomRT.radius.x = bottomT.radius.y * 2;
			leftElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, triangle, leftT);
			topElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, triangle, topT);
			rightElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, triangle, rightT);
			centerElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, triangle, centerT);
			bottomElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, triangle, bottomT);
			bottomLElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, triangle, bottomLT);
			bottomRElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, triangle, bottomRT);
		}
		else if ( strcasecmp(argv[1], "square") == 0 )
		{
			leftT.radius.x = elemSize.y;
			topT.radius.x = elemSize.y;
			rightT.radius.x = elemSize.y;
			centerT.radius.x = elemSize.y;
			bottomT.radius.x = elemSize.y;
			bottomLT.radius.x = elemSize.y;
			bottomRT.radius.x = elemSize.y;
			leftElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, leftT);
			topElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, topT);
			rightElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, rightT);
			centerElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, centerT);
			bottomElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, bottomT);
			bottomLElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, bottomLT);
			bottomRElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, bottomRT);
		}
		else if ( strcasecmp(argv[1], "rectangle") == 0 )
		{
			bottomT.radius.x = bottomT.radius.y * 2;
			bottomLT.radius.x = bottomT.radius.y * 2;
			bottomRT.radius.x = bottomT.radius.y * 2;
			leftElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, leftT);
			topElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, topT);
			rightElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, rightT);
			centerElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, centerT);
			bottomElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, bottomT);
			bottomLElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, bottomLT);
			bottomRElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, bottomRT);
		}
		else if ( strcasecmp(argv[1], "poly") == 0 )
		{
			leftT.radius.x = elemSize.y;
			topT.radius.x = elemSize.y;
			rightT.radius.x = elemSize.y;
			centerT.radius.x = elemSize.y;
			bottomT.radius.x = elemSize.y;
			bottomLT.radius.x = elemSize.y;
			bottomRT.radius.x = elemSize.y;
			std::shared_ptr< NoGUI::nShape > fivegon = std::make_shared< NoGUI::nShape >(5, fill, outline);
			std::shared_ptr< NoGUI::nShape > sixgon = std::make_shared< NoGUI::nShape >(6, fill, outline);
			std::shared_ptr< NoGUI::nShape > sevengon = std::make_shared< NoGUI::nShape >(7, fill, outline);
			std::shared_ptr< NoGUI::nShape > ninegon = std::make_shared< NoGUI::nShape >(9, fill, outline);
			std::shared_ptr< NoGUI::nShape > tengon = std::make_shared< NoGUI::nShape >(10, fill, outline);
			std::shared_ptr< NoGUI::nShape > elevengon = std::make_shared< NoGUI::nShape >(11, fill, outline);
			leftElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, fivegon, leftT);
			topElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, sixgon, topT);
			rightElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, sevengon, rightT);
			centerElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, octagon, centerT);
			bottomElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ninegon, bottomT);
			bottomLElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, tengon, bottomLT);
			bottomRElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, elevengon, bottomRT);
		}
		else if ( strcasecmp(argv[1], "polygon") == 0 )
		{
			bottomT.radius.x = bottomT.radius.y * 2;
			bottomLT.radius.x = bottomT.radius.y * 2;
			bottomRT.radius.x = bottomT.radius.y * 2;
			std::shared_ptr< NoGUI::nShape > fivegon = std::make_shared< NoGUI::nShape >(5, fill, outline);
			std::shared_ptr< NoGUI::nShape > sixgon = std::make_shared< NoGUI::nShape >(6, fill, outline);
			std::shared_ptr< NoGUI::nShape > sevengon = std::make_shared< NoGUI::nShape >(7, fill, outline);
			std::shared_ptr< NoGUI::nShape > ninegon = std::make_shared< NoGUI::nShape >(9, fill, outline);
			std::shared_ptr< NoGUI::nShape > tengon = std::make_shared< NoGUI::nShape >(10, fill, outline);
			std::shared_ptr< NoGUI::nShape > elevengon = std::make_shared< NoGUI::nShape >(11, fill, outline);
			leftElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, fivegon, leftT);
			topElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, sixgon, topT);
			rightElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, sevengon, rightT);
			centerElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, octagon, centerT);
			bottomElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ninegon, bottomT);
			bottomLElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, tengon, bottomLT);
			bottomRElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, elevengon, bottomRT);
		}
	}
	
	elemVec.push_back(shapeElem);
	elemVec.push_back(dataElem);
	elemVec.push_back(leftElem);
	elemVec.push_back(topElem);
	elemVec.push_back(rightElem);
	elemVec.push_back(centerElem);
	elemVec.push_back(bottomLElem);
	elemVec.push_back(bottomElem);
	elemVec.push_back(bottomRElem);
	
	// main
	InitWindow(window.x, window.y, "test");
	SetTargetFPS(60);
	while ( !WindowShouldClose() )
	{
//		bool plustate = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
//		bool minustate = IsMouseButtonDown(MOUSE_RIGHT_BUTTON);
		float scroll = GetMouseWheelMove();
		dataElem->setInner(TextFormat("Angle: %03.02f", centerElem->angle));
		BeginDrawing();
			ClearBackground(BLACK);
			for ( auto elem : elemVec )
			{
				if (!TextIsEqual(elem->getTag(), "Tip"))
				{
					elem->rotate(1.0f * scroll, NoGUI::Align(0, 0));
					if ( elem->isHover() )
					{
						if ( IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
						{
							elem->setFocus(!elem->getFocus());
						}
					}
					if ( elem->getFocus() )
					{
						elem->getShape()->fill = focusFill;
					}
					else
					{
						elem->getShape()->fill = fill;
					}
				}
				elem->draw();
			}
		EndDrawing();
	}
	
	return 0;
}