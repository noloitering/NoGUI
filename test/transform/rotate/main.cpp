#include <iostream>

#include "../../../src/GUI.h"

int main(int argc, char ** argv)
{
	// initialization
	Vector2 window = {1280, 720};
	Vector2 elemSize = {100, 50};
	int rotation = 0;
	char msg[51];
	
	std::shared_ptr< NoGUI::Fill > fill = std::make_shared< NoGUI::Fill >();
	std::shared_ptr< NoGUI::Fill > noFill = std::make_shared< NoGUI::Fill >((Color){0, 0, 0, 0});
	std::shared_ptr< NoGUI::nShape > tipShape = std::make_shared< NoGUI::nShape >(4, noFill);
	std::shared_ptr< NoGUI::nShape > rect = std::make_shared< NoGUI::nShape >(4, fill);
	std::shared_ptr< NoGUI::nShape > circle = std::make_shared< NoGUI::nShape >(0, fill);
	
	NoGUI::Transform topT = NoGUI::Transform((Vector2){window.x / 2, 50}, elemSize, NoGUI::Align(0, -1));
	NoGUI::Transform centerT = NoGUI::Transform((Vector2){window.x / 2, window.y / 2}, (Vector2){25, 25}, NoGUI::Align());
	NoGUI::Transform leftT = NoGUI::Transform((Vector2){0, 0}, (Vector2){125, 200}, NoGUI::Align(-1, -1));
	
	std::shared_ptr< NoGUI::Element > topElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, topT);
	std::shared_ptr< NoGUI::Element > centerElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, circle, centerT);
	std::shared_ptr< NoGUI::Element > dataElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, tipShape, leftT, std::make_shared< NoGUI::CContainer >(), "Tip");
	dataElem->components->addComponent< NoGUI::CText >(nullptr, nullptr, 20, NoGUI::Align(0, -1));
	
	// main
	InitWindow(window.x, window.y, "test");
	SetTargetFPS(60);
	while ( !WindowShouldClose() )
	{
		int txtPoint = 0;
		if ( IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT) )
		{
			TextAppend(msg, "Reorient\n", &txtPoint);
		}
		else
		{
			TextAppend(msg, "Rotate\n", &txtPoint);
		}
		TextAppend(msg, TextFormat("Angle: %03.02f", topElem->angle), &txtPoint);
		dataElem->setInner(msg);
		BeginDrawing();
			ClearBackground(BLACK);
			dataElem->draw();
			topElem->draw();
			centerElem->draw();
			DrawCircleV(topElem->pos(NoGUI::Align(0, 0)), 6, RED);
			DrawCircleV(topElem->pos(NoGUI::Align(-1, 0)), 6, RED);
			DrawCircleV(topElem->pos(NoGUI::Align(1, 0)), 6, RED);
			DrawCircleV(topElem->pos(NoGUI::Align(0, -1)), 6, RED);
			DrawCircleV(topElem->pos(NoGUI::Align(0, 1)), 6, RED);
		EndDrawing();
		if ( IsMouseButtonDown(MOUSE_LEFT_BUTTON) )
		{
			if ( IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT) )
			{
				topElem->reorient(rotation, centerElem->pos());
				rotation++;
			}
			else
			{
				topElem->rotate(1, centerElem->pos());
			}
		}
		else if ( IsMouseButtonDown(MOUSE_RIGHT_BUTTON) )
		{
			if ( IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT) )
			{
				topElem->reorient(rotation, centerElem->pos());
				rotation--;
			}
			else
			{
				topElem->rotate(-1, centerElem->pos());
			}
		}
		else if ( IsKeyPressed(KEY_R) )
		{
			topElem->reorient(0, NoGUI::Align(0, -1));
			topElem->repos((Vector2){window.x / 2, 50});
		}
		else if ( IsKeyPressed(KEY_Z) )
		{
			if ( IsMouseButtonDown(KEY_LEFT_SHIFT) || IsMouseButtonDown(KEY_RIGHT_SHIFT) )
			{
				topElem->reorient(90, centerElem->pos());
				rotation = 90;
			}
			else
			{
				topElem->rotate(90, centerElem->pos());
			}
		}
		else if ( IsKeyPressed(KEY_X) )
		{
			if ( IsMouseButtonDown(KEY_LEFT_SHIFT) || IsMouseButtonDown(KEY_RIGHT_SHIFT) )
			{
				topElem->reorient(180, centerElem->pos());
				rotation = 180;
			}
			else
			{
				topElem->rotate(180, centerElem->pos());
			}
		}
		else if ( IsKeyPressed(KEY_C) )
		{
			if ( IsMouseButtonDown(KEY_LEFT_SHIFT) || IsMouseButtonDown(KEY_RIGHT_SHIFT) )
			{
				topElem->reorient(270, centerElem->pos());
				rotation = 270;
			}
			else
			{
				topElem->rotate(270, centerElem->pos());
			}
		}
		else if ( IsKeyPressed(KEY_V) )
		{
			if ( IsMouseButtonDown(KEY_LEFT_SHIFT) || IsMouseButtonDown(KEY_RIGHT_SHIFT) )
			{
				topElem->reorient(360, centerElem->pos());
				rotation = 360;
			}
			else
			{
				topElem->rotate(360, centerElem->pos());
			}
		}
	}
	
	return 0;
}