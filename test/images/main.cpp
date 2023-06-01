#include <iostream>
#include <vector>

#include "../../src/GUI.h"

int main(int argc, char ** argv)
{
	// initialization
	Vector2 window = {1280, 720};
	Vector2 elemSize = {100, 100};
	std::vector< std::shared_ptr< NoGUI::Element > > elemVec;
	NoGUI::CImage image;
	bool rLeft = false;
	bool rRight = false;
	float scroll = 0;
	
	InitWindow(window.x, window.y, "test");
	SetTargetFPS(60);
	
	if ( argc > 1 )
	{
		// TODO: load texture
	}
	if ( image.img == nullptr )
	{
		image.img = std::make_shared< Texture2D >(LoadTexture("testimg.gif"));
		image.scale = (Vector2){0.5f, 0.5f};
		image.crop = NoGUI::Crop::NONE;
	}
	
	std::shared_ptr< NoGUI::Fill > fill = std::make_shared< NoGUI::Fill >();
	std::shared_ptr< NoGUI::Fill > lineFill = std::make_shared< NoGUI::Fill >(BLUE);
	std::shared_ptr< NoGUI::Outline > outline = std::make_shared< NoGUI::Outline >(lineFill, 3);
	std::shared_ptr< NoGUI::nShape > ellipse = std::make_shared< NoGUI::nShape >(0, fill, outline);
	std::shared_ptr< NoGUI::nShape > triangle = std::make_shared< NoGUI::nShape >(3, fill, outline);
	std::shared_ptr< NoGUI::nShape > rect = std::make_shared< NoGUI::nShape >(4, fill, outline);
	std::shared_ptr< NoGUI::nShape > fivegon = std::make_shared< NoGUI::nShape >(4, fill, outline);
	std::shared_ptr< NoGUI::nShape > sixgon = std::make_shared< NoGUI::nShape >(6, fill, outline);
	std::shared_ptr< NoGUI::nShape > sevengon = std::make_shared< NoGUI::nShape >(5, fill, outline);
	std::shared_ptr< NoGUI::nShape > octagon = std::make_shared< NoGUI::nShape >(8, fill, outline);
	
	NoGUI::Transform leftT = NoGUI::Transform((Vector2){0, 0}, elemSize, NoGUI::Align(-1, -1));
	NoGUI::Transform topT = NoGUI::Transform((Vector2){window.x / 2, 0}, elemSize, NoGUI::Align(0, -1));
	NoGUI::Transform rightT = NoGUI::Transform((Vector2){window.x, 0}, elemSize, NoGUI::Align(1, -1));
	NoGUI::Transform centerT = NoGUI::Transform((Vector2){window.x / 2, window.y / 2}, elemSize, NoGUI::Align());
	NoGUI::Transform bottomLT = NoGUI::Transform((Vector2){0, window.y}, elemSize, NoGUI::Align(-1, 1));
	NoGUI::Transform bottomT = NoGUI::Transform((Vector2){window.x / 2, window.y}, elemSize, NoGUI::Align(0, 1));
	NoGUI::Transform bottomRT = NoGUI::Transform((Vector2){window.x, window.y}, elemSize, NoGUI::Align(1, 1));
	
	std::shared_ptr< NoGUI::CContainer > comps = std::make_shared< NoGUI::CContainer >();
	comps->addComponent< NoGUI::CImage >(image);
	std::shared_ptr< NoGUI::Element > leftElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ellipse, leftT, comps);
	std::shared_ptr< NoGUI::Element > topElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, triangle, topT, comps);
	std::shared_ptr< NoGUI::Element > rightElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, rightT, comps);
	std::shared_ptr< NoGUI::Element > centerElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, fivegon, centerT, comps);
	std::shared_ptr< NoGUI::Element > bottomElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, sixgon, bottomT, comps);
	std::shared_ptr< NoGUI::Element > bottomLElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, sevengon, bottomLT, comps);
	std::shared_ptr< NoGUI::Element > bottomRElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, octagon, bottomRT, comps);
	
	elemVec.push_back(leftElem);
	elemVec.push_back(topElem);
	elemVec.push_back(rightElem);
	elemVec.push_back(centerElem);
	elemVec.push_back(bottomLElem);
	elemVec.push_back(bottomElem);
	elemVec.push_back(bottomRElem);
	
	// main
	while ( !WindowShouldClose() )
	{
		rLeft = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
		rRight = IsMouseButtonDown(MOUSE_RIGHT_BUTTON);
		scroll = GetMouseWheelMove();
		
		if ( scroll )
		{
			std::cout << scroll << std::endl;
			comps->getComponent< NoGUI::CImage >().scale.x += 0.1f * scroll;
			comps->getComponent< NoGUI::CImage >().scale.y += 0.1f * scroll;
		}
		
		if ( IsKeyPressed(KEY_SPACE) )
		{
			switch (comps->getComponent< NoGUI::CImage >().crop)
			{
				case NoGUI::Crop::NONE:
				{
//					image.crop = NoGUI::Crop::FIT;
					comps->getComponent< NoGUI::CImage >().crop = NoGUI::Crop::FIT;
					
					break;
				}
				
				case NoGUI::Crop::FIT:
				{
					comps->getComponent< NoGUI::CImage >().crop = NoGUI::Crop::CUT;
					
					break;
				}
				
				case NoGUI::Crop::CUT:
				{
					comps->getComponent< NoGUI::CImage >().crop = NoGUI::Crop::SCROLL;
					
					break;
				}
				
				case NoGUI::Crop::SCROLL:
				{
					comps->getComponent< NoGUI::CImage >().crop = NoGUI::Crop::NONE;
					
					break;
				}
			}
		}
		
		BeginDrawing();
			ClearBackground(BLACK);
			for ( auto elem : elemVec )
			{
				if ( rLeft )
				{
//					elem->rotate(1, NoGUI::Align(0, 0));
					elem->rotate(1, elem->origin);
				}
				else if ( rRight )
				{
//					elem->rotate(-1, NoGUI::Align(0, 0));
					elem->rotate(-1, elem->origin);
				}
				elem->draw();
			}
		EndDrawing();
	}
	UnloadTexture(*(image.img));
	
	return 0;
}