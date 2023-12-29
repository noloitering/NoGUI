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
	std::shared_ptr< NoGUI::Fill > textFill = std::make_shared< NoGUI::Fill >(DARKGRAY);
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
	
	std::shared_ptr< NoGUI::CContainer > dataComps = std::make_shared< NoGUI::CContainer >();
	std::shared_ptr< NoGUI::CContainer > shapeComps = std::make_shared< NoGUI::CContainer >();
	dataComps->addComponent< NoGUI::CText >();
	shapeComps->addComponent< NoGUI::CText >(textFill);
	std::shared_ptr< NoGUI::Toggle > dataElem = std::make_shared< NoGUI::Toggle >(NoMAD::OBJCOUNT, tipShape, centerLeftT, dataComps, "Tip");
	std::shared_ptr< NoGUI::Toggle > shapeElem = std::make_shared< NoGUI::Toggle >(NoMAD::OBJCOUNT, tipShape, centerRightT, dataComps, "Tip");
	std::shared_ptr< NoGUI::Button > leftElem = std::make_shared< NoGUI::Button >(NoMAD::OBJCOUNT, ellipse, leftT, shapeComps, "Shape", "Button");
	std::shared_ptr< NoGUI::Hoverable > topElem = std::make_shared< NoGUI::Hoverable >(NoMAD::OBJCOUNT, line, topT, shapeComps, "Shape", "Hoverable");
	std::shared_ptr< NoGUI::Toggle > rightElem = std::make_shared< NoGUI::Toggle >(NoMAD::OBJCOUNT, rect, rightT, shapeComps, "Shape", "Toggle");
	std::shared_ptr< NoGUI::Trigger > centerElem = std::make_shared< NoGUI::Trigger >(NoMAD::OBJCOUNT, triangle, centerT, shapeComps, "Shape", "Trigger");
	std::shared_ptr< NoGUI::CheckBox > bottomElem = std::make_shared< NoGUI::CheckBox >(NoMAD::OBJCOUNT, octagon, bottomT, shapeComps, "Shape", "CheckBox");
	std::shared_ptr< NoGUI::Slider > bottomLElem = std::make_shared< NoGUI::Slider >(NoMAD::OBJCOUNT, rect, bottomLT, shapeComps, "Shape", "Slider");
	std::shared_ptr< NoGUI::Cursorer > bottomRElem = std::make_shared< NoGUI::Cursorer >(NoMAD::OBJCOUNT, ellipse, ellipse, bottomRT, shapeComps, "Shape", "Cursorer");
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
			leftElem = std::make_shared< NoGUI::Button >(NoMAD::OBJCOUNT, ellipse, leftT, shapeComps, "Shape", "Button");
			topElem = std::make_shared< NoGUI::Hoverable >(NoMAD::OBJCOUNT, ellipse, topT, shapeComps, "Shape", "Hoverable");
			rightElem = std::make_shared< NoGUI::Toggle >(NoMAD::OBJCOUNT, ellipse, rightT, shapeComps, "Shape", "Toggle");
			centerElem = std::make_shared< NoGUI::Trigger >(NoMAD::OBJCOUNT, ellipse, centerT, shapeComps, "Shape", "Trigger");
			bottomElem = std::make_shared< NoGUI::CheckBox >(NoMAD::OBJCOUNT, ellipse, bottomT, shapeComps, "Shape", "CheckBox");
			bottomLElem = std::make_shared< NoGUI::Slider >(NoMAD::OBJCOUNT, ellipse, bottomLT, shapeComps, "Shape", "Slider");
			bottomRElem = std::make_shared< NoGUI::Cursorer >(NoMAD::OBJCOUNT, ellipse, ellipse, bottomRT, shapeComps, "Shape", "Cursorer");
		}
		else if ( strcasecmp(argv[1], "ellipse") == 0 )
		{
			bottomT.radius.x = bottomT.radius.y * 2;
			bottomLT.radius.x = bottomT.radius.y * 2;
			bottomRT.radius.x = bottomT.radius.y * 2;
			leftElem = std::make_shared< NoGUI::Button >(NoMAD::OBJCOUNT, ellipse, leftT, shapeComps, "Shape", "Button");
			topElem = std::make_shared< NoGUI::Hoverable >(NoMAD::OBJCOUNT, ellipse, topT, shapeComps, "Shape", "Hoverable");
			rightElem = std::make_shared< NoGUI::Toggle >(NoMAD::OBJCOUNT, ellipse, rightT, shapeComps, "Shape", "Toggle");
			centerElem = std::make_shared< NoGUI::Trigger >(NoMAD::OBJCOUNT, ellipse, centerT, shapeComps, "Shape", "Trigger");
			bottomElem = std::make_shared< NoGUI::CheckBox >(NoMAD::OBJCOUNT, ellipse, bottomT, shapeComps, "Shape", "CheckBox");
			bottomLElem = std::make_shared< NoGUI::Slider >(NoMAD::OBJCOUNT, ellipse, bottomLT, shapeComps, "Shape", "Slider");
			bottomRElem = std::make_shared< NoGUI::Cursorer >(NoMAD::OBJCOUNT, ellipse, ellipse, bottomRT, shapeComps, "Shape", "Cursorer");
		}
		else if ( strcasecmp(argv[1], "line") == 0 )
		{
			leftElem = std::make_shared< NoGUI::Button >(NoMAD::OBJCOUNT, line, leftT, shapeComps, "Shape", "Button");
			topElem = std::make_shared< NoGUI::Hoverable >(NoMAD::OBJCOUNT, line, topT, shapeComps, "Shape", "Hoverable");
			rightElem = std::make_shared< NoGUI::Toggle >(NoMAD::OBJCOUNT, line, rightT, shapeComps, "Shape", "Toggle");
			centerElem = std::make_shared< NoGUI::Trigger >(NoMAD::OBJCOUNT, line, centerT, shapeComps, "Shape", "Trigger");
			bottomElem = std::make_shared< NoGUI::CheckBox >(NoMAD::OBJCOUNT, line, bottomT, shapeComps, "Shape", "CheckBox");
			bottomLElem = std::make_shared< NoGUI::Slider >(NoMAD::OBJCOUNT, line, bottomLT, shapeComps, "Shape", "Slider");
			bottomRElem = std::make_shared< NoGUI::Cursorer >(NoMAD::OBJCOUNT, line, ellipse, bottomRT, shapeComps, "Shape", "Cursorer");
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
			leftElem = std::make_shared< NoGUI::Button >(NoMAD::OBJCOUNT, triangle, leftT, shapeComps, "Shape", "Button");
			topElem = std::make_shared< NoGUI::Hoverable >(NoMAD::OBJCOUNT, triangle, topT, shapeComps, "Shape", "Hoverable");
			rightElem = std::make_shared< NoGUI::Toggle >(NoMAD::OBJCOUNT, triangle, rightT, shapeComps, "Shape", "Toggle");
			centerElem = std::make_shared< NoGUI::Trigger >(NoMAD::OBJCOUNT, triangle, centerT, shapeComps, "Shape", "Trigger");
			bottomElem = std::make_shared< NoGUI::CheckBox >(NoMAD::OBJCOUNT, triangle, bottomT, shapeComps, "Shape", "CheckBox");
			bottomLElem = std::make_shared< NoGUI::Slider >(NoMAD::OBJCOUNT, triangle, bottomLT, shapeComps, "Shape", "Slider");
			bottomRElem = std::make_shared< NoGUI::Cursorer >(NoMAD::OBJCOUNT, triangle, ellipse, bottomRT, shapeComps, "Shape", "Cursorer");
		}
		else if ( strcasecmp(argv[1], "triangle") == 0 )
		{
			bottomT.radius.x = bottomT.radius.y * 2;
			bottomLT.radius.x = bottomT.radius.y * 2;
			bottomRT.radius.x = bottomT.radius.y * 2;
			leftElem = std::make_shared< NoGUI::Button >(NoMAD::OBJCOUNT, triangle, leftT, shapeComps, "Shape", "Button");
			topElem = std::make_shared< NoGUI::Hoverable >(NoMAD::OBJCOUNT, triangle, topT, shapeComps, "Shape", "Hoverable");
			rightElem = std::make_shared< NoGUI::Toggle >(NoMAD::OBJCOUNT, triangle, rightT, shapeComps, "Shape", "Toggle");
			centerElem = std::make_shared< NoGUI::Trigger >(NoMAD::OBJCOUNT, triangle, centerT, shapeComps, "Shape", "Trigger");
			bottomElem = std::make_shared< NoGUI::CheckBox >(NoMAD::OBJCOUNT, triangle, bottomT, shapeComps, "Shape", "CheckBox");
			bottomLElem = std::make_shared< NoGUI::Slider >(NoMAD::OBJCOUNT, triangle, bottomLT, shapeComps, "Shape", "Slider");
			bottomRElem = std::make_shared< NoGUI::Cursorer >(NoMAD::OBJCOUNT, triangle, ellipse, bottomRT, shapeComps, "Shape", "Cursorer");
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
			leftElem = std::make_shared< NoGUI::Button >(NoMAD::OBJCOUNT, rect, leftT, shapeComps, "Shape", "Button");
			topElem = std::make_shared< NoGUI::Hoverable >(NoMAD::OBJCOUNT, rect, topT, shapeComps, "Shape", "Hoverable");
			rightElem = std::make_shared< NoGUI::Toggle >(NoMAD::OBJCOUNT, rect, rightT, shapeComps, "Shape", "Toggle");
			centerElem = std::make_shared< NoGUI::Trigger >(NoMAD::OBJCOUNT, rect, centerT, shapeComps, "Shape", "Trigger");
			bottomElem = std::make_shared< NoGUI::CheckBox >(NoMAD::OBJCOUNT, rect, bottomT, shapeComps, "Shape", "CheckBox");
			bottomLElem = std::make_shared< NoGUI::Slider >(NoMAD::OBJCOUNT, rect, bottomLT, shapeComps, "Shape", "Slider");
			bottomRElem = std::make_shared< NoGUI::Cursorer >(NoMAD::OBJCOUNT, rect, ellipse, bottomRT, shapeComps, "Shape", "Cursorer");
		}
		else if ( strcasecmp(argv[1], "rectangle") == 0 )
		{
			bottomT.radius.x = bottomT.radius.y * 2;
			bottomLT.radius.x = bottomT.radius.y * 2;
			bottomRT.radius.x = bottomT.radius.y * 2;
			leftElem = std::make_shared< NoGUI::Button >(NoMAD::OBJCOUNT, rect, leftT, shapeComps, "Shape", "Button");
			topElem = std::make_shared< NoGUI::Hoverable >(NoMAD::OBJCOUNT, rect, topT, shapeComps, "Shape", "Hoverable");
			rightElem = std::make_shared< NoGUI::Toggle >(NoMAD::OBJCOUNT, rect, rightT, shapeComps, "Shape", "Toggle");
			centerElem = std::make_shared< NoGUI::Trigger >(NoMAD::OBJCOUNT, rect, centerT, shapeComps, "Shape", "Trigger");
			bottomElem = std::make_shared< NoGUI::CheckBox >(NoMAD::OBJCOUNT, rect, bottomT, shapeComps, "Shape", "CheckBox");
			bottomLElem = std::make_shared< NoGUI::Slider >(NoMAD::OBJCOUNT, rect, bottomLT, shapeComps, "Shape", "Slider");
			bottomRElem = std::make_shared< NoGUI::Cursorer >(NoMAD::OBJCOUNT, rect, ellipse, bottomRT, shapeComps, "Shape", "Cursorer");
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
			leftElem = std::make_shared< NoGUI::Button >(NoMAD::OBJCOUNT, fivegon, leftT, shapeComps, "Shape", "Button");
			topElem = std::make_shared< NoGUI::Hoverable >(NoMAD::OBJCOUNT, sixgon, topT, shapeComps, "Shape", "Hoverable");
			rightElem = std::make_shared< NoGUI::Toggle >(NoMAD::OBJCOUNT, sevengon, rightT, shapeComps, "Shape", "Toggle");
			centerElem = std::make_shared< NoGUI::Trigger >(NoMAD::OBJCOUNT, octagon, centerT, shapeComps, "Shape", "Trigger");
			bottomElem = std::make_shared< NoGUI::CheckBox >(NoMAD::OBJCOUNT, ninegon, bottomT, shapeComps, "Shape", "CheckBox");
			bottomLElem = std::make_shared< NoGUI::Slider >(NoMAD::OBJCOUNT, tengon, bottomLT, shapeComps, "Shape", "Slider");
			bottomRElem = std::make_shared< NoGUI::Cursorer >(NoMAD::OBJCOUNT, elevengon, ellipse, bottomRT, shapeComps, "Shape", "Cursorer");
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
			leftElem = std::make_shared< NoGUI::Button >(NoMAD::OBJCOUNT, fivegon, leftT, shapeComps, "Shape", "Button");
			topElem = std::make_shared< NoGUI::Hoverable >(NoMAD::OBJCOUNT, sixgon, topT, shapeComps, "Shape", "Hoverable");
			rightElem = std::make_shared< NoGUI::Toggle >(NoMAD::OBJCOUNT, sevengon, rightT, shapeComps, "Shape", "Toggle");
			centerElem = std::make_shared< NoGUI::Trigger >(NoMAD::OBJCOUNT, octagon, centerT, shapeComps, "Shape", "Trigger");
			bottomElem = std::make_shared< NoGUI::CheckBox >(NoMAD::OBJCOUNT, ninegon, bottomT, shapeComps, "Shape", "CheckBox");
			bottomLElem = std::make_shared< NoGUI::Slider >(NoMAD::OBJCOUNT, tengon, bottomLT, shapeComps, "Shape", "Slider");
			bottomRElem = std::make_shared< NoGUI::Cursorer >(NoMAD::OBJCOUNT, elevengon, ellipse, bottomRT, shapeComps, "Shape", "Cursorer");
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
		float scroll = GetMouseWheelMove();
		dataElem->setInner(TextFormat("Angle: %03.02f", centerElem->angle));
		BeginDrawing();
			ClearBackground(BLACK);
			for ( auto elem : elemVec )
			{
				if (!TextIsEqual(elem->getTag(), "Tip"))
				{
					elem->isHover();
					elem->isFocus();
					elem->rotate(1.0f * scroll, NoGUI::Align(0, 0));
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