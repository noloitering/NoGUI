#include <iostream>

#include "../../src/GUI.h"

int main(int argc, char ** argv)
{
	// default
	NoMAD::GameObj testObj = NoMAD::GameObj();
	// getters
	std::cout << "id: " << testObj.getId() << " (" << testObj.getTag() << ")" << std::endl;
	std::cout << testObj.getInner() << std::endl;
	// setters
	testObj.setTag("Test");
	testObj.setInner("Test Object");
	std::cout << "id: " << testObj.getId() << " (" << testObj.getTag() << ")" << std::endl;
	std::cout << testObj.getInner() << std::endl;
	// overflow
	testObj.setTag("THIS STRING OF CHARACTERS IS OVER 50 CHARACTERS LONG MY GUY");
	std::cout << testObj.getTag() << std::endl;
	// id counter
	NoMAD::GameObj newObj = NoMAD::GameObj();
	std::cout << "id: " << newObj.getId() << " (" << newObj.getTag() << ")" << std::endl;
	std::cout << newObj.getInner() << std::endl;
	// shapes
	int rotation = 0;
	std::shared_ptr< NoGUI::Fill > testFill = std::make_shared< NoGUI::Fill >(RAYWHITE);
	std::shared_ptr< NoGUI::Fill > outlineFill = std::make_shared< NoGUI::Fill >(GRAY);
	std::shared_ptr< NoGUI::Outline > testOutline = std::make_shared< NoGUI::Outline >(outlineFill, 10);
	NoGUI::nShape ellipse = (NoGUI::nShape){0, testFill, testOutline};
	NoGUI::nShape line = (NoGUI::nShape){2, testFill, testOutline};
	NoGUI::nShape triangle = (NoGUI::nShape){3, testFill, testOutline};
	NoGUI::nShape rectangle = (NoGUI::nShape){4, testFill, testOutline};
	NoGUI::nShape octagon = (NoGUI::nShape){8, testFill, testOutline};
	InitWindow(1280, 720, "test");
	SetTargetFPS(60);
	while ( !WindowShouldClose() )
	{
		if ( argc > 1 )
		{
			if ( strcasecmp(argv[1], "circle") == 0 )
			{
				BeginDrawing();
					ClearBackground(BLACK);
					NoGUI::DrawShape(ellipse, (Vector2){640, 360}, (Vector2){100, 100}, (Vector2){0, 0}, rotation);
					NoGUI::DrawShape(ellipse, (Vector2){0, 0}, (Vector2){100, 100}, (Vector2){-100, -100}, rotation);
					NoGUI::DrawShape(ellipse, (Vector2){1280, 0}, (Vector2){100, 100}, (Vector2){100, -100}, rotation);
					NoGUI::DrawShape(ellipse, (Vector2){640, 0}, (Vector2){100, 100}, (Vector2){0, -100}, rotation);
					NoGUI::DrawShape(ellipse, (Vector2){640, 720}, (Vector2){100, 100}, (Vector2){0, 100}, rotation);
					NoGUI::DrawShape(ellipse, (Vector2){0, 720}, (Vector2){100, 100}, (Vector2){-100, 100}, rotation);
					NoGUI::DrawShape(ellipse, (Vector2){1280, 720}, (Vector2){100, 100}, (Vector2){100, 100}, rotation);
				EndDrawing();
			}
			else if ( strcasecmp(argv[1], "ellipse") == 0 )
			{
				BeginDrawing();
					ClearBackground(BLACK);
					NoGUI::DrawShape(ellipse, (Vector2){640, 360}, (Vector2){100, 50}, (Vector2){0, 0}, rotation);
					NoGUI::DrawShape(ellipse, (Vector2){0, 0}, (Vector2){100, 50}, (Vector2){-100, -50}, rotation);
					NoGUI::DrawShape(ellipse, (Vector2){1280, 0}, (Vector2){100, 50}, (Vector2){100, -50}, rotation);
					NoGUI::DrawShape(ellipse, (Vector2){640, 0}, (Vector2){100, 50}, (Vector2){0, -50}, rotation);
					NoGUI::DrawShape(ellipse, (Vector2){640, 720}, (Vector2){100, 50}, (Vector2){0, 50}, rotation);
					NoGUI::DrawShape(ellipse, (Vector2){0, 720}, (Vector2){100, 50}, (Vector2){-100, 50}, rotation);
					NoGUI::DrawShape(ellipse, (Vector2){1280, 720}, (Vector2){100, 50}, (Vector2){100, 50}, rotation);
				EndDrawing();
			}
			else if ( strcasecmp(argv[1], "line") == 0 )
			{
				BeginDrawing();
					ClearBackground(BLACK);
					NoGUI::DrawShape(line, (Vector2){640, 360}, (Vector2){100, 50}, (Vector2){0, 0}, rotation);
					NoGUI::DrawShape(line, (Vector2){0, 0}, (Vector2){100, 50}, (Vector2){-100, -50}, rotation);
					NoGUI::DrawShape(line, (Vector2){1280, 0}, (Vector2){100, 50}, (Vector2){100, -50}, rotation);
					NoGUI::DrawShape(line, (Vector2){640, 0}, (Vector2){100, 50}, (Vector2){0, -50}, rotation);
					NoGUI::DrawShape(line, (Vector2){640, 720}, (Vector2){100, 50}, (Vector2){0, 50}, rotation);
					NoGUI::DrawShape(line, (Vector2){0, 720}, (Vector2){100, 50}, (Vector2){-100, 50}, rotation);
					NoGUI::DrawShape(line, (Vector2){1280, 720}, (Vector2){100, 50}, (Vector2){100, 50}, rotation);
				EndDrawing();
			}
			else if ( strcasecmp(argv[1], "tri") == 0 )
			{
				BeginDrawing();
					ClearBackground(BLACK);
					NoGUI::DrawShape(triangle, (Vector2){640, 360}, (Vector2){100, 100}, (Vector2){0, 0}, rotation);
					NoGUI::DrawShape(triangle, (Vector2){0, 0}, (Vector2){100, 100}, (Vector2){-100, -100}, rotation);
					NoGUI::DrawShape(triangle, (Vector2){1280, 0}, (Vector2){100, 100}, (Vector2){100, -100}, rotation);
					NoGUI::DrawShape(triangle, (Vector2){640, 0}, (Vector2){100, 100}, (Vector2){0, -100}, rotation);
					NoGUI::DrawShape(triangle, (Vector2){640, 720}, (Vector2){100, 100}, (Vector2){0, 100}, rotation);
					NoGUI::DrawShape(triangle, (Vector2){0, 720}, (Vector2){100, 100}, (Vector2){-100, 100}, rotation);
					NoGUI::DrawShape(triangle, (Vector2){1280, 720}, (Vector2){100, 100}, (Vector2){100, 100}, rotation);
				EndDrawing();
			}
			else if ( strcasecmp(argv[1], "triangle") == 0 )
			{
				BeginDrawing();
					ClearBackground(BLACK);
					NoGUI::DrawShape(triangle, (Vector2){640, 360}, (Vector2){100, 50}, (Vector2){0, 0}, rotation);
					NoGUI::DrawShape(triangle, (Vector2){0, 0}, (Vector2){100, 50}, (Vector2){-100, -50}, rotation);
					NoGUI::DrawShape(triangle, (Vector2){1280, 0}, (Vector2){100, 50}, (Vector2){100, -50}, rotation);
					NoGUI::DrawShape(triangle, (Vector2){640, 0}, (Vector2){100, 50}, (Vector2){0, -50}, rotation);
					NoGUI::DrawShape(triangle, (Vector2){640, 720}, (Vector2){100, 50}, (Vector2){-100, -50}, rotation);
					NoGUI::DrawShape(triangle, (Vector2){0, 720}, (Vector2){100, 50}, (Vector2){-100, 50}, rotation);
					NoGUI::DrawShape(triangle, (Vector2){1280, 720}, (Vector2){100, 50}, (Vector2){100, 50}, rotation);
				EndDrawing();
			}
			else if ( strcasecmp(argv[1], "square") == 0 )
			{
				BeginDrawing();
					ClearBackground(BLACK);
					NoGUI::DrawShape(rectangle, (Vector2){640, 360}, (Vector2){100, 100}, (Vector2){0, 0}, rotation);
					NoGUI::DrawShape(rectangle, (Vector2){0, 0}, (Vector2){100, 100}, (Vector2){-100, -100}, rotation);
					NoGUI::DrawShape(rectangle, (Vector2){1280, 0}, (Vector2){100, 100}, (Vector2){100, -100}, rotation);
					NoGUI::DrawShape(rectangle, (Vector2){640, 0}, (Vector2){100, 100}, (Vector2){0, -100}, rotation);
					NoGUI::DrawShape(rectangle, (Vector2){640, 720}, (Vector2){100, 100}, (Vector2){0, 100}, rotation);
					NoGUI::DrawShape(rectangle, (Vector2){0, 720}, (Vector2){100, 100}, (Vector2){-100, 100}, rotation);
					NoGUI::DrawShape(rectangle, (Vector2){1280, 720}, (Vector2){100, 100}, (Vector2){100, 100}, rotation);
				EndDrawing();
			}
			else if ( strcasecmp(argv[1], "rectangle") == 0 )
			{
				BeginDrawing();
					ClearBackground(BLACK);
					NoGUI::DrawShape(rectangle, (Vector2){640, 360}, (Vector2){100, 50}, (Vector2){0, 0}, rotation);
					NoGUI::DrawShape(rectangle, (Vector2){0, 0}, (Vector2){100, 50}, (Vector2){-100, -50}, rotation);
					NoGUI::DrawShape(rectangle, (Vector2){1280, 0}, (Vector2){100, 50}, (Vector2){100, -50}, rotation);
					NoGUI::DrawShape(rectangle, (Vector2){640, 0}, (Vector2){100, 50}, (Vector2){0, -50}, rotation);
					NoGUI::DrawShape(rectangle, (Vector2){640, 720}, (Vector2){100, 50}, (Vector2){0, 50}, rotation);
					NoGUI::DrawShape(rectangle, (Vector2){0, 720}, (Vector2){100, 50}, (Vector2){-100, 50}, rotation);
					NoGUI::DrawShape(rectangle, (Vector2){1280, 720}, (Vector2){100, 50}, (Vector2){100, 50}, rotation);
				EndDrawing();
			}
			else if ( strcasecmp(argv[1], "poly") == 0 )
			{
				NoGUI::nShape fivegon = (NoGUI::nShape){5, testFill, testOutline};
				NoGUI::nShape sixgon = (NoGUI::nShape){6, testFill, testOutline};
				NoGUI::nShape sevengon = (NoGUI::nShape){7, testFill, testOutline};
				NoGUI::nShape ninegon = (NoGUI::nShape){9, testFill, testOutline};
				NoGUI::nShape tengon = (NoGUI::nShape){10, testFill, testOutline};
				NoGUI::nShape elevengon = (NoGUI::nShape){11, testFill, testOutline};
				BeginDrawing();
					ClearBackground(BLACK);
					NoGUI::DrawShape(octagon, (Vector2){640, 360}, (Vector2){100, 100}, (Vector2){0, 0}, rotation);
					NoGUI::DrawShape(fivegon, (Vector2){0, 0}, (Vector2){100, 100}, (Vector2){-100, -100}, rotation);
					NoGUI::DrawShape(sevengon, (Vector2){1280, 0}, (Vector2){100, 100}, (Vector2){100, -100}, rotation);
					NoGUI::DrawShape(sixgon, (Vector2){640, 0}, (Vector2){100, 100}, (Vector2){0, -100}, rotation);
					NoGUI::DrawShape(tengon, (Vector2){640, 720}, (Vector2){100, 100}, (Vector2){0, 100}, rotation);
					NoGUI::DrawShape(ninegon, (Vector2){0, 720}, (Vector2){100, 100}, (Vector2){-100, 100}, rotation);
					NoGUI::DrawShape(elevengon, (Vector2){1280, 720}, (Vector2){100, 100}, (Vector2){100, 100}, rotation);
				EndDrawing();
			}
			else if ( strcasecmp(argv[1], "polygon") == 0 )
			{
				NoGUI::nShape fivegon = (NoGUI::nShape){5, testFill, testOutline};
				NoGUI::nShape sixgon = (NoGUI::nShape){6, testFill, testOutline};
				NoGUI::nShape sevengon = (NoGUI::nShape){7, testFill, testOutline};
				NoGUI::nShape ninegon = (NoGUI::nShape){9, testFill, testOutline};
				NoGUI::nShape tengon = (NoGUI::nShape){10, testFill, testOutline};
				NoGUI::nShape elevengon = (NoGUI::nShape){11, testFill, testOutline};
				BeginDrawing();
					ClearBackground(BLACK);
					NoGUI::DrawShape(octagon, (Vector2){640, 360}, (Vector2){100, 50}, (Vector2){0, 0}, rotation);
					NoGUI::DrawShape(fivegon, (Vector2){0, 0}, (Vector2){100, 50}, (Vector2){-100, -50}, rotation);
					NoGUI::DrawShape(sevengon, (Vector2){1280, 0}, (Vector2){100, 50}, (Vector2){100, -50},  rotation);
					NoGUI::DrawShape(sixgon, (Vector2){640, 0}, (Vector2){100, 50}, (Vector2){0, -50}, rotation);
					NoGUI::DrawShape(tengon, (Vector2){640, 720}, (Vector2){100, 50}, (Vector2){0, 50}, rotation);
					NoGUI::DrawShape(ninegon, (Vector2){0, 720}, (Vector2){100, 50}, (Vector2){-100, 50}, rotation);
					NoGUI::DrawShape(elevengon, (Vector2){1280, 720}, (Vector2){100, 50}, (Vector2){100, 50}, rotation);
				EndDrawing();
			}
			else
			{
				std::cout << "Sorry! " << argv[1] << " is not a valid command" << std::endl;
				std::cout << "TIP: REMEMBER TO USE LOWER CASE" << std::endl;
				CloseWindow();
			}
		}
		else
		{
			BeginDrawing();
				ClearBackground(BLACK);
				NoGUI::DrawShape(ellipse, (Vector2){640, 360}, (Vector2){100, 50}, (Vector2){0, 0}, rotation);
				NoGUI::DrawShape(line, (Vector2){0, 0}, (Vector2){100, 50}, (Vector2){-100, -50}, rotation);
				NoGUI::DrawShape(rectangle, (Vector2){1280, 0}, (Vector2){100, 50}, (Vector2){100, -50}, rotation);
				NoGUI::DrawShape(triangle, (Vector2){640, 0}, (Vector2){100, 50}, (Vector2){0, -50}, rotation);
				NoGUI::DrawShape(octagon, (Vector2){640, 720}, (Vector2){100, 50}, (Vector2){0, 50}, rotation);
				NoGUI::DrawShape(rectangle, (Vector2){0, 720}, (Vector2){100, 100}, (Vector2){-100, 100}, rotation);
				NoGUI::DrawShape(ellipse, (Vector2){1280, 720}, (Vector2){100, 100}, (Vector2){100, 100}, rotation);
			EndDrawing();
		}
		if ( IsMouseButtonDown(MOUSE_LEFT_BUTTON) )
		{
			rotation++;
		}
		else if ( IsMouseButtonDown(MOUSE_RIGHT_BUTTON) )
		{
			rotation--;
		}
	}
	
	return 0;
}