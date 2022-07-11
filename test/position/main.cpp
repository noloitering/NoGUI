#include <iostream>

#include "../../src/GUI.h"

int main(int argc, char ** argv)
{
	// initialization
	Vector2 window = {1280, 720};
	Vector2 elemSize = {100, 50};
	
	std::shared_ptr< NoGUI::Fill > fill = std::make_shared< NoGUI::Fill >();
	std::shared_ptr< NoGUI::Shape > rect = std::make_shared< NoGUI::Shape >(4, fill);
	NoGUI::Transform centerT = NoGUI::Transform((Vector2){window.x / 2, window.y / 2}, elemSize, NoGUI::Align::CENTER);
	std::shared_ptr< NoGUI::Element > centerElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, centerT);
	
	// main
	InitWindow(window.x, window.y, "test");
	SetTargetFPS(60);
	while ( !WindowShouldClose() )
	{
		bool update = !(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT));
		if ( IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
		{
			centerElem->repos(GetMousePosition());
		}
		if ( IsKeyPressed(KEY_Z) )
		{
			centerElem->repos(centerElem->pos(), NoGUI::Align::LEFT, update);
		}
		else if ( IsKeyPressed(KEY_X) )
		{
			centerElem->repos(centerElem->pos(), NoGUI::Align::RIGHT, update);
		}
		else if ( IsKeyPressed(KEY_C) )
		{
			centerElem->repos(centerElem->pos(), NoGUI::Align::CENTER, update);
		}
		else if ( IsKeyPressed(KEY_V) )
		{
			centerElem->repos(centerElem->pos(), NoGUI::Align::TOP, update);
		}
		else if ( IsKeyPressed(KEY_B) )
		{
			centerElem->repos(centerElem->pos(), NoGUI::Align::BOTTOM, update);
		}
		else if ( IsKeyPressed(KEY_N) )
		{
			centerElem->repos(centerElem->pos(), NoGUI::Align::BOTTOML, update);
		}
		else if ( IsKeyPressed(KEY_M) )
		{
			centerElem->repos(centerElem->pos(), NoGUI::Align::BOTTOMR, update);
		}
		else if ( IsKeyPressed(KEY_R) )
		{
			centerElem->repos((Vector2){window.x / 2, window.y / 2}, NoGUI::Align::CENTER, true);
		}
		BeginDrawing();
			ClearBackground(BLACK);
			centerElem->draw();
		EndDrawing();
	}
	
	return 0;
}