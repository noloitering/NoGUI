#include <iostream>
#include <vector>

#include "../../src/GUI.h"

int main(int argc, char ** argv)
{
	// initialization
	Vector2 window = {1280, 720};
	Vector2 elemSize = {100, 50};
	std::vector< std::shared_ptr< NoGUI::Element > > elemVec;
	
	std::shared_ptr< NoGUI::Fill > fill = std::make_shared< NoGUI::Fill >();
	std::shared_ptr< NoGUI::Shape > ellipse = std::make_shared< NoGUI::Shape >(0, fill, nullptr);
	std::shared_ptr< NoGUI::Shape > line = std::make_shared< NoGUI::Shape >(2, fill, nullptr);
	std::shared_ptr< NoGUI::Shape > triangle = std::make_shared< NoGUI::Shape >(3, fill, nullptr);
	std::shared_ptr< NoGUI::Shape > rect = std::make_shared< NoGUI::Shape >(4, fill, nullptr);
	std::shared_ptr< NoGUI::Shape > octagon = std::make_shared< NoGUI::Shape >(8, fill, nullptr);
	
	NoGUI::Transform leftT = NoGUI::Transform((Vector2){0, 0}, elemSize, NoGUI::Align::LEFT);
	NoGUI::Transform topT = NoGUI::Transform((Vector2){window.x / 2, 0}, elemSize, NoGUI::Align::TOP);
	NoGUI::Transform rightT = NoGUI::Transform((Vector2){window.x, 0}, elemSize, NoGUI::Align::RIGHT);
	NoGUI::Transform centerT = NoGUI::Transform((Vector2){window.x / 2, window.y / 2}, elemSize, NoGUI::Align::CENTER);
	NoGUI::Transform bottomLT = NoGUI::Transform((Vector2){0, window.y}, elemSize, NoGUI::Align::BOTTOML);
	NoGUI::Transform bottomT = NoGUI::Transform((Vector2){window.x / 2, window.y}, elemSize, NoGUI::Align::BOTTOM);
	NoGUI::Transform bottomRT = NoGUI::Transform((Vector2){window.x, window.y}, elemSize, NoGUI::Align::BOTTOMR);
	
	std::shared_ptr< NoGUI::Element > leftElem;
	std::shared_ptr< NoGUI::Element > topElem;
	std::shared_ptr< NoGUI::Element > rightElem;
	std::shared_ptr< NoGUI::Element > centerElem;
	std::shared_ptr< NoGUI::Element > bottomElem;
	std::shared_ptr< NoGUI::Element > bottomLElem;
	std::shared_ptr< NoGUI::Element > bottomRElem;
	if ( argc > 1 )
	{
		if ( strcmp(argv[1], "circle") == 0 )
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
		else if ( strcmp(argv[1], "ellipse") == 0 )
		{
			leftElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ellipse, leftT);
			topElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ellipse, topT);
			rightElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ellipse, rightT);
			centerElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ellipse, centerT);
			bottomElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ellipse, bottomT);
			bottomLElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ellipse, bottomLT);
			bottomRElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ellipse, bottomRT);
		}
		else if ( strcmp(argv[1], "line") == 0 )
		{
			leftElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, line, leftT);
			topElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, line, topT);
			rightElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, line, rightT);
			centerElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, line, centerT);
			bottomElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, line, bottomT);
			bottomLElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, line, bottomLT);
			bottomRElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, line, bottomRT);
		}
		else if ( strcmp(argv[1], "tri") == 0 )
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
		else if ( strcmp(argv[1], "triangle") == 0 )
		{
			leftElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, triangle, leftT);
			topElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, triangle, topT);
			rightElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, triangle, rightT);
			centerElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, triangle, centerT);
			bottomElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, triangle, bottomT);
			bottomLElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, triangle, bottomLT);
			bottomRElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, triangle, bottomRT);
		}
		else if ( strcmp(argv[1], "square") == 0 )
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
		else if ( strcmp(argv[1], "rectangle") == 0 )
		{
			leftElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, leftT);
			topElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, topT);
			rightElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, rightT);
			centerElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, centerT);
			bottomElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, bottomT);
			bottomLElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, bottomLT);
			bottomRElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, bottomRT);
		}
		else if ( strcmp(argv[1], "polygon") == 0 )
		{
			std::shared_ptr< NoGUI::Shape > fivegon = std::make_shared< NoGUI::Shape >(5, fill, nullptr);
			std::shared_ptr< NoGUI::Shape > sixgon = std::make_shared< NoGUI::Shape >(6, fill, nullptr);
			std::shared_ptr< NoGUI::Shape > sevengon = std::make_shared< NoGUI::Shape >(7, fill, nullptr);
			std::shared_ptr< NoGUI::Shape > ninegon = std::make_shared< NoGUI::Shape >(9, fill, nullptr);
			std::shared_ptr< NoGUI::Shape > tengon = std::make_shared< NoGUI::Shape >(10, fill, nullptr);
			std::shared_ptr< NoGUI::Shape > elevengon = std::make_shared< NoGUI::Shape >(11, fill, nullptr);
			leftElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, leftT);
			topElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, topT);
			rightElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, rightT);
			centerElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, centerT);
			bottomElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, bottomT);
			bottomLElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, bottomLT);
			bottomRElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, bottomRT);
		}
	}
	else
	{
		bottomT.radius.x = elemSize.y;
		bottomLT.radius.x = elemSize.y;
		bottomRT.radius.x = elemSize.y;
		leftElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ellipse, leftT);
		topElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, line, topT);
		rightElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, rightT);
		centerElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, triangle, centerT);
		bottomElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, octagon, bottomT);
		bottomLElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, bottomLT);
		bottomRElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ellipse, bottomRT);
	}
	
	elemVec.push_back(leftElem);
	elemVec.push_back(topElem);
	elemVec.push_back(rightElem);
	elemVec.push_back(centerElem);
	elemVec.push_back(bottomLElem);
	elemVec.push_back(bottomElem);
	elemVec.push_back(bottomRElem);
	
	std::cout << "number of elements: " << NoMAD::OBJCOUNT << std::endl;
	std::cout << "elem vector size: " << elemVec.size() << std::endl;
	
	// main
	InitWindow(window.x, window.y, "test");
	SetTargetFPS(60);
	while ( !WindowShouldClose() )
	{
		bool plustate = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
		bool minustate = IsMouseButtonDown(MOUSE_RIGHT_BUTTON);
		BeginDrawing();
			ClearBackground(BLACK);
			for ( auto elem : elemVec )
			{
				if ( plustate )
				{
					elem->rotate(1, elem->origin());
				}
				else if ( minustate )
				{
					elem->rotate(-1, elem->origin());
				}
				elem->draw();
			}
		EndDrawing();
	}
	
	return 0;
}