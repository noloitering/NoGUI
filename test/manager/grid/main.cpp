#include "../../../src/GUI.h"

Vector2 window = {1280, 720};

int main(int argc, char ** argv)
{
	InitWindow(window.x, window.y, "test");
	SetTargetFPS(60);
	while ( !WindowShouldClose() )
	{	
		BeginDrawing();
			ClearBackground(RAYWHITE);
		EndDrawing();
	}
	
	return 0;
}