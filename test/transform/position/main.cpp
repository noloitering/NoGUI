#include <iostream>

#include "../../../src/GUI.h"

int main(int argc, char ** argv)
{
	// initialization
	Vector2 window = {1280, 720};
	Vector2 elemSize = {100, 50};
	
	std::shared_ptr< NoGUI::Fill > fill = std::make_shared< NoGUI::Fill >();
	std::shared_ptr< NoGUI::Fill > noFill = std::make_shared< NoGUI::Fill >((Color){0, 0, 0, 0});
	std::shared_ptr< NoGUI::nShape > tipShape = std::make_shared< NoGUI::nShape >(4, noFill);
	std::shared_ptr< NoGUI::nShape > rect = std::make_shared< NoGUI::nShape >(4, fill);
	NoGUI::Transform centerT = NoGUI::Transform((Vector2){window.x / 2, window.y / 2}, elemSize, NoGUI::Align());
	NoGUI::Transform leftT = NoGUI::Transform((Vector2){0, 0}, (Vector2){125, 200}, NoGUI::Align(-1, -1));
	std::shared_ptr< NoGUI::Element > centerElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, centerT);
	std::shared_ptr< NoGUI::Element > dataElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, tipShape, leftT, std::make_shared< NoGUI::CContainer >(), "Tip");
	dataElem->components->addComponent< NoGUI::CText >(nullptr, nullptr, 20, NoGUI::Align(0, -1));
	char msg[101];
	const char* originText = "Origin: CENTER\n";
//	char originText[31];
//	TextInsert(originText, "Origin: CENTER\n", 0);
	// main
	InitWindow(window.x, window.y, "test");
	SetTargetFPS(60);
	while ( !WindowShouldClose() )
	{
		int txtPoint = 0;
		bool update = !(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT));
		if (update)
		{
			TextAppend(msg, "REPOSITION\n", &txtPoint);
		}
		else
		{
			TextAppend(msg, "REORIENT\n", &txtPoint);
		}
		if ( IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
		{
			centerElem->repos(GetMousePosition());
		}
		if ( IsKeyPressed(KEY_Z) ) // top left
		{
			centerElem->repos(centerElem->pos(), NoGUI::Align(-1, -1), update);
			if ( update )
			{
				originText = "Origin: TOP LEFT\n";
			}
		}
		else if ( IsKeyPressed(KEY_X) ) // top right
		{
			centerElem->repos(centerElem->pos(), NoGUI::Align(1, -1), update);
			if ( update )
			{
				originText = "Origin: TOP RIGHT\n";
			}
		}
		else if ( IsKeyPressed(KEY_C) ) // center
		{
			centerElem->repos(centerElem->pos(), NoGUI::Align(), update);
			if ( update )
			{
				originText = "Origin: CENTER\n";
			}
		}
		else if ( IsKeyPressed(KEY_V) ) // top
		{
			centerElem->repos(centerElem->pos(), NoGUI::Align(0, -1), update);
			if ( update )
			{
				originText = "Origin: TOP\n";
			}
		}
		else if ( IsKeyPressed(KEY_B) ) // bottom
		{
			centerElem->repos(centerElem->pos(), NoGUI::Align(0, 1), update);
			if ( update )
			{
				originText = "Origin: BOTTOM\n";
			}
		}
		else if ( IsKeyPressed(KEY_N) ) // bottom left
		{
			centerElem->repos(centerElem->pos(), NoGUI::Align(-1, 1), update);
			if ( update )
			{
				originText = "Origin: BOTTOM LEFT\n";
			}
		}
		else if ( IsKeyPressed(KEY_M) ) // bottom right
		{
			centerElem->repos(centerElem->pos(), NoGUI::Align(1, 1), update);
			if ( update )
			{
				originText = "Origin: BOTTOM RIGHT\n";
			}
		}
		else if ( IsKeyPressed(KEY_COMMA) ) // center left
		{
			centerElem->repos(centerElem->pos(), NoGUI::Align(-1, 0), update);
			if ( update )
			{
				originText = "Origin: CENTER LEFT\n";
			}
		}
		else if ( IsKeyPressed(KEY_PERIOD) ) // center right
		{
			centerElem->repos(centerElem->pos(), NoGUI::Align(1, 0), update);
			if ( update )
			{
				originText = "Origin: CENTER RIGHT\n";
			}
		}
		else if ( IsKeyPressed(KEY_R) ) // reset
		{
			centerElem->repos((Vector2){window.x / 2, window.y / 2}, NoGUI::Align(), true);
			centerElem->angle = 0;
			originText = "Origin: CENTER\n";
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
		TextAppend(msg, originText, &txtPoint);
		TextAppend(msg, TextFormat("Position: {%04.01f, %04.01f}\n", centerElem->position.x, centerElem->position.y), &txtPoint);
		TextAppend(msg, TextFormat("Angle: %03.02f\n", centerElem->angle), &txtPoint);
		dataElem->setInner(msg);
		BeginDrawing();
			ClearBackground(BLACK);
			centerElem->angle -= GetMouseWheelMove();
			centerElem->draw();
			dataElem->draw();
			DrawCircleV(centerElem->pos(), 6, RED);
		EndDrawing();
	}
	
	return 0;
}