#include <iostream>

#include "../../src/GUI.h"

int main(int argc, char ** argv)
{
	// initialization
	Vector2 window = {1280, 720};
	Vector2 elemSize = {100, 50};
	
	std::shared_ptr< NoGUI::Fill > fill = std::make_shared< NoGUI::Fill >();
	std::shared_ptr< NoGUI::nShape > rect = std::make_shared< NoGUI::nShape >(4, fill);
	NoGUI::Transform centerT = NoGUI::Transform((Vector2){window.x / 2, window.y / 2}, elemSize, NoGUI::Align());
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
		if ( IsKeyPressed(KEY_Z) ) // top left
		{
			centerElem->repos(centerElem->pos(), NoGUI::Align(-1, -1), update);
		}
		else if ( IsKeyPressed(KEY_X) ) // top right
		{
			centerElem->repos(centerElem->pos(), NoGUI::Align(1, -1), update);
		}
		else if ( IsKeyPressed(KEY_C) ) // center
		{
			centerElem->repos(centerElem->pos(), NoGUI::Align(), update);
		}
		else if ( IsKeyPressed(KEY_V) ) // top
		{
			centerElem->repos(centerElem->pos(), NoGUI::Align(0, -1), update);
		}
		else if ( IsKeyPressed(KEY_B) ) // bottom
		{
			centerElem->repos(centerElem->pos(), NoGUI::Align(0, 1), update);
		}
		else if ( IsKeyPressed(KEY_N) ) // bottom left
		{
			centerElem->repos(centerElem->pos(), NoGUI::Align(-1, 1), update);
		}
		else if ( IsKeyPressed(KEY_M) ) // bottom right
		{
			centerElem->repos(centerElem->pos(), NoGUI::Align(1, 1), update);
		}
		else if ( IsKeyPressed(KEY_COMMA) ) // center left
		{
			centerElem->repos(centerElem->pos(), NoGUI::Align(-1, 0), update);
		}
		else if ( IsKeyPressed(KEY_PERIOD) ) // center right
		{
			centerElem->repos(centerElem->pos(), NoGUI::Align(1, 0), update);
		}
		else if ( IsKeyPressed(KEY_R) ) // reset
		{
			centerElem->repos((Vector2){window.x / 2, window.y / 2}, NoGUI::Align(), true);
			centerElem->angle = 0;
		}
		else
		{
			if ( IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) )
			{
				centerElem->translate(0, -1);
			}
			if ( IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) )
			{
				centerElem->translate(-1, 0);
			}
			if ( IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) )
			{
				centerElem->translate(0, 1);
			}
			if ( IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) )
			{
				centerElem->translate(1, 0);
			}
		}
		BeginDrawing();
			ClearBackground(BLACK);
			centerElem->angle -= GetMouseWheelMove();
			centerElem->draw();
			DrawCircleV(centerElem->pos(NoGUI::Align(0, 0)), 6, RED);
		EndDrawing();
	}
	
	return 0;
}