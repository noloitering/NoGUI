#include "../../../src/GUI.h"

Vector2 window = {1280, 720};

int main(int argc, char ** argv)
{
	bool showGrid = false;
	if ( argc > 2 )
	{
		window.x = TextToInteger(argv[1]);
		window.y = TextToInteger(argv[2]);
	}
	NoGUI::ManagerGrid gui = NoGUI::ManagerGrid(true, window.x / 10, window.y / 10);
	std::shared_ptr< NoGUI::Fill > fill = std::make_shared< NoGUI::Fill >(GRAY);
	std::shared_ptr< NoGUI::nShape > shape = std::make_shared< NoGUI::nShape >(4, fill);
	NoGUI::Transform centerPos = NoGUI::Transform((Vector2){5, 5}, (Vector2){1, 1}, NoGUI::Align());
	gui.getPage(0)->addElement(shape, centerPos);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(window.x, window.y, "test");
	SetTargetFPS(60);
	while ( !WindowShouldClose() )
	{	
		if ( IsKeyPressed(KEY_SPACE) )
		{
			showGrid = !showGrid;
		}
		BeginDrawing();
			ClearBackground(BLACK);
			gui.setCellSize(GetScreenWidth() / 10, GetScreenHeight() / 10);
			gui.update();
			if ( showGrid )
			{
				gui.drawCells(DARKGRAY);
			}
			gui.render();
		EndDrawing();
	}
	
	return 0;
}