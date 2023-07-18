#include <iostream>
#include <vector>

#include "../../../../src/GUI.h"

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
		image.img = std::make_shared< Texture2D >(LoadTexture(argv[1]));
		image.scrollable = true;
		image.crop = NoGUI::Crop::NONE;
	}
	if ( image.img == nullptr )
	{
		image.img = std::make_shared< Texture2D >(LoadTexture("testimg.gif"));
		image.scale = (Vector2){0.5f, 0.5f};
		image.scrollable = true;
		image.crop = NoGUI::Crop::NONE;
	}
	
	std::shared_ptr< NoGUI::Fill > fill = std::make_shared< NoGUI::Fill >();
	std::shared_ptr< NoGUI::Fill > noFill = std::make_shared< NoGUI::Fill >((Color){0, 0, 0, 0});
	std::shared_ptr< NoGUI::Fill > toggleFill = std::make_shared< NoGUI::Fill >(GREEN);
	std::shared_ptr< NoGUI::Fill > lineFill = std::make_shared< NoGUI::Fill >(BLUE);
	std::shared_ptr< NoGUI::Outline > outline = std::make_shared< NoGUI::Outline >(lineFill, 3);
	std::shared_ptr< NoGUI::nShape > tipShape = std::make_shared< NoGUI::nShape >(4, noFill, outline);
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
	NoGUI::Transform centerLeftT = NoGUI::Transform((Vector2){0, window.y / 2}, (Vector2){200, 100}, NoGUI::Align(-1, 0));
	NoGUI::Transform centerRightT = NoGUI::Transform((Vector2){window.x, window.y / 2}, (Vector2){200, 100}, NoGUI::Align(1, 0));
	NoGUI::Transform bottomLT = NoGUI::Transform((Vector2){0, window.y}, elemSize, NoGUI::Align(-1, 1));
	NoGUI::Transform bottomT = NoGUI::Transform((Vector2){window.x / 2, window.y}, elemSize, NoGUI::Align(0, 1));
	NoGUI::Transform bottomRT = NoGUI::Transform((Vector2){window.x, window.y}, elemSize, NoGUI::Align(1, 1));
	
	std::shared_ptr< NoGUI::Element > styleElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, tipShape, centerLeftT, std::make_shared< NoGUI::CContainer >(), "Tip", "NONE");
	std::shared_ptr< NoGUI::Element > scrollElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, tipShape, centerLeftT, std::make_shared< NoGUI::CContainer >(), "Tip", "\nscrolling ENABLED");
	std::shared_ptr< NoGUI::Element > dataElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, tipShape, centerRightT, std::make_shared< NoGUI::CContainer >(), "Tip");
	styleElem->components->addComponent< NoGUI::CText >();
	dataElem->components->addComponent< NoGUI::CText >();
	scrollElem->components->addComponent< NoGUI::CText >(toggleFill, nullptr, 20.0f, NoGUI::Align(), 0.0f, (Vector2){2, 24});
	std::shared_ptr< NoGUI::CContainer > comps = std::make_shared< NoGUI::CContainer >();
	comps->addComponent< NoGUI::CImage >(image);
	std::shared_ptr< NoGUI::Element > leftElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, ellipse, leftT, comps);
	std::shared_ptr< NoGUI::Element > topElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, triangle, topT, comps);
	std::shared_ptr< NoGUI::Element > rightElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, rightT, comps);
	std::shared_ptr< NoGUI::Element > centerElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, fivegon, centerT, comps);
	std::shared_ptr< NoGUI::Element > bottomElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, sixgon, bottomT, comps);
	std::shared_ptr< NoGUI::Element > bottomLElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, sevengon, bottomLT, comps);
	std::shared_ptr< NoGUI::Element > bottomRElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, octagon, bottomRT, comps);
	
	elemVec.push_back(dataElem);
	elemVec.push_back(styleElem);
	elemVec.push_back(scrollElem);
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
		if ( IsKeyPressed(KEY_W) )
		{
			comps->getComponent< NoGUI::CImage >().scale.y += 0.1f;
		}
		if ( IsKeyPressed(KEY_A) )
		{
			comps->getComponent< NoGUI::CImage >().scale.x -= 0.1f;
		}
		if ( IsKeyPressed(KEY_S) )
		{
			comps->getComponent< NoGUI::CImage >().scale.y -= 0.1f;
		}
		if ( IsKeyPressed(KEY_D) )
		{
			comps->getComponent< NoGUI::CImage >().scale.x += 0.1f;
		}
		
		if ( IsKeyPressed(KEY_SPACE) )
		{
			switch (comps->getComponent< NoGUI::CImage >().crop)
			{
				case NoGUI::Crop::NONE:
				{
					comps->getComponent< NoGUI::CImage >().crop = NoGUI::Crop::CUT;
					styleElem->setInner("CUT");
					
					break;
				}
				
				case NoGUI::Crop::FIT:
				{
					comps->getComponent< NoGUI::CImage >().crop = NoGUI::Crop::NONE;
					styleElem->setInner("NONE");
					
					break;
				}
				
				case NoGUI::Crop::CUT:
				{
					comps->getComponent< NoGUI::CImage >().crop = NoGUI::Crop::FIT;
					styleElem->setInner("FIT");
					
					break;
				}
			}
		}
		
		if ( IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_Q) || IsKeyPressed(KEY_E) )
		{
			comps->getComponent< NoGUI::CImage >().scrollable = !(comps->getComponent< NoGUI::CImage >().scrollable);
		}
		
		if ( IsKeyPressed(KEY_UP) )
		{
			comps->getComponent< NoGUI::CImage >().scrollPos.y -= 0.1; // scroll up
		}
		if ( IsKeyPressed(KEY_DOWN) )
		{
			comps->getComponent< NoGUI::CImage >().scrollPos.y += 0.1; // scroll down
		}
		if ( IsKeyPressed(KEY_RIGHT) )
		{
			comps->getComponent< NoGUI::CImage >().scrollPos.x += 0.1; // scroll right
		}
		if ( IsKeyPressed(KEY_LEFT) )
		{
			comps->getComponent< NoGUI::CImage >().scrollPos.x -= 0.1; // scroll left
		}
		dataElem->setInner(TextFormat("Img Size: {%i, %i}\nAngle: %03.02f\nScale: {%02.02f, %02.02f}\nScroll: {%01.02f, %01.02f}", comps->getComponent< NoGUI::CImage >().img->width, comps->getComponent< NoGUI::CImage >().img->height, centerElem->angle, comps->getComponent< NoGUI::CImage >().scale.x, comps->getComponent< NoGUI::CImage >().scale.y, comps->getComponent< NoGUI::CImage >().scrollPos.x, comps->getComponent< NoGUI::CImage >().scrollPos.y));
		if ( comps->getComponent< NoGUI::CImage >().scrollable )
		{
			toggleFill->col = GREEN;
			scrollElem->setInner("\nscrolling ENABLED");
		}
		else
		{
			toggleFill->col = RED;
			scrollElem->setInner("\nscrolling DISABLED");
		}
		
		BeginDrawing();
			ClearBackground(BLACK);
			for ( auto elem : elemVec )
			{
				if (!TextIsEqual(elem->getTag(), "Tip"))
				{
					if ( rLeft )
					{
						elem->rotate(1, elem->origin);
					}
					else if ( rRight )
					{
						elem->rotate(-1, elem->origin);
					}
				}
				elem->draw();
			}
		EndDrawing();
	}
	UnloadTexture(*(image.img));
	
	return 0;
}