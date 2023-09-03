#include <iostream>

#include "../../../src/GUI.h"

int main(int argc, char ** argv)
{
	// initialization
//	bool shape = false;
//	bool drawLines =  true;
//	bool start = true;
//	int sides = 3;

	Vector2 window = {1280, 720};
	Vector2 elemSize = {100, 100};
	
	std::shared_ptr< NoGUI::Fill > fill = std::make_shared< NoGUI::Fill >(RAYWHITE);
	std::shared_ptr< NoGUI::Fill > noFill = std::make_shared< NoGUI::Fill >((Color){0, 0, 0, 0});
	std::shared_ptr< NoGUI::Fill > lineFill = std::make_shared< NoGUI::Fill >(GRAY);
	std::shared_ptr< NoGUI::Outline > outline = std::make_shared< NoGUI::Outline >(lineFill, 5, NoGUI::Wrap::AROUND);
	std::shared_ptr< NoGUI::nShape > tipShape = std::make_shared< NoGUI::nShape >(4, noFill, outline);
	std::shared_ptr< NoGUI::nShape > polygon = std::make_shared< NoGUI::nShape >(0, fill, outline);
	
	NoGUI::Transform centerT = NoGUI::Transform((Vector2){window.x / 2, window.y / 2}, elemSize, NoGUI::Align());
	NoGUI::Transform centerLeftT = NoGUI::Transform((Vector2){0, window.y / 2}, (Vector2){200, 100}, NoGUI::Align(-1, 0));
//	NoGUI::Transform centerRightT = NoGUI::Transform((Vector2){window.x, window.y / 2}, (Vector2){200, 100}, NoGUI::Align(1, 0));
	
//	std::shared_ptr< NoGUI::Element > scrollElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, tipShape, centerLeftT, std::make_shared< NoGUI::CContainer >(), "Tip", "\nscrolling ENABLED");
	std::shared_ptr< NoGUI::Element > centerElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, polygon, centerT);
	std::shared_ptr< NoGUI::Element > dataElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, tipShape, centerLeftT, std::make_shared< NoGUI::CContainer >(), "Tip");
	dataElem->components->addComponent< NoGUI::CText >();
	
	// main
	InitWindow(window.x, window.y, "test");
	SetTargetFPS(60);
	while ( !WindowShouldClose() )
	{
		if ( IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
		{
			polygon->n++;
		}
		
		if ( IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) )
		{
			if ( polygon->n > 0 )
			{
				polygon->n--;
			}
		}
		
		if ( IsKeyPressed(KEY_O) )
		{
			if ( polygon->outline )
			{
				polygon->outline = nullptr;
			}
			else
			{
				polygon->outline = outline;
			}
		}
		dataElem->setInner(TextFormat("Sides: %i\nThickness: %i\nWrap Mode: AROUND\n", polygon->n, outline->thick));
		BeginDrawing();
			ClearBackground(BLACK);
			centerElem->draw();
			dataElem->draw();
		EndDrawing();
	}
	
	return 0;
}