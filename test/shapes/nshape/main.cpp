#include <iostream>

#include "../../../src/GUI.h"

int main(int argc, char ** argv)
{
	const int shapeAmount = 7;
	Vector2 elemSize = {100, 50};
	// default
	NoMAD::GameObj testObj = NoMAD::GameObj();
	// getters
	std::cout << "id: " << testObj.getId() << " (" << testObj.getTag() << ")" << std::endl;
	std::cout << testObj.getInner() << std::endl;
	// setters
//	testObj.setTag("Test");
	testObj.setInner("Test Object");
	std::cout << "id: " << testObj.getId() << " (" << testObj.getTag() << ")" << std::endl;
	std::cout << testObj.getInner() << std::endl;
	// overflow
	NoMAD::GameObj newObj = NoMAD::GameObj(NoMAD::OBJCOUNT, "THIS STRING OF CHARACTERS IS OVER 50 CHARACTERS LONG MY GUY");
	std::cout << "id: " << newObj.getId() << " (" << newObj.getTag() << ")" << std::endl;
	std::cout << newObj.getInner() << std::endl;
	// shapes
	int rotation = 0;
	std::shared_ptr< NoGUI::Fill > testFill = std::make_shared< NoGUI::Fill >(RAYWHITE);
	std::shared_ptr< NoGUI::Fill > outlineFill = std::make_shared< NoGUI::Fill >(GRAY);
	std::shared_ptr< NoGUI::Fill > noFill = std::make_shared< NoGUI::Fill >((Color){0, 0, 0, 0});
	std::shared_ptr< NoGUI::Outline > testOutline = std::make_shared< NoGUI::Outline >(outlineFill, 10);
	NoGUI::nShape shapeArray[shapeAmount];
	NoGUI::nShape tipShape = NoGUI::nShape(4, noFill, testOutline);
	NoGUI::nShape ellipse = (NoGUI::nShape){0, testFill, testOutline};
	NoGUI::nShape line = (NoGUI::nShape){2, testFill, testOutline};
	NoGUI::nShape triangle = (NoGUI::nShape){3, testFill, testOutline};
	NoGUI::nShape rectangle = (NoGUI::nShape){4, testFill, testOutline};
	NoGUI::nShape octagon = (NoGUI::nShape){8, testFill, testOutline};
	NoGUI::Transform dataT = NoGUI::Transform((Vector2){0, 360}, (Vector2){elemSize.x * 2, elemSize.x}, NoGUI::Align(-1, 0));
	NoGUI::Transform shapeT = NoGUI::Transform((Vector2){1280, 360}, (Vector2){elemSize.x * 2, elemSize.x}, NoGUI::Align(1, 0));
	NoGUI::CText dataText = NoGUI::CText();
	const char* shapeMsg = "";
	NoGUI::CText shapeText = NoGUI::CText();
	Vector2 posArray[shapeAmount];
	Vector2 originArray[shapeAmount];
	posArray[0] = (Vector2){0, 0};
	posArray[1] = (Vector2){640, 0};
	posArray[2] = (Vector2){1280, 0};
	posArray[3] = (Vector2){640, 360};
	posArray[4] = (Vector2){0, 720};
	posArray[5] = (Vector2){640, 720};
	posArray[6] = (Vector2){1280, 720};
	
	if ( argc > 1 )
	{
		if ( strcasecmp(argv[1], "circle") == 0 )
		{
			shapeMsg = "circle";
			elemSize = (Vector2){100, 100};
			for (int i=0; i < shapeAmount; i++)
			{
				shapeArray[i] = ellipse;
			}
		}
		else if ( strcasecmp(argv[1], "ellipse") == 0 )
		{
			shapeMsg = "ellipse";
			for (int i=0; i < shapeAmount; i++)
			{
				shapeArray[i] = ellipse;
			}
		}
		else if ( strcasecmp(argv[1], "line") == 0 )
		{
			shapeMsg = "line";
			for (int i=0; i < shapeAmount; i++)
			{
				shapeArray[i] = line;
			}
		}
		else if ( strcasecmp(argv[1], "tri") == 0 )
		{
			shapeMsg = "tri";
			elemSize = (Vector2){100, 100};
			for (int i=0; i < shapeAmount; i++)
			{
				shapeArray[i] = triangle;
			}
		}
		else if ( strcasecmp(argv[1], "triangle") == 0 )
		{
			shapeMsg = "triangle";
			for (int i=0; i < shapeAmount; i++)
			{
				shapeArray[i] = triangle;
			}
		}
		else if ( strcasecmp(argv[1], "square") == 0 )
		{
			shapeMsg = "square";
			elemSize = (Vector2){100, 100};
			for (int i=0; i < shapeAmount; i++)
			{
				shapeArray[i] = rectangle;
			}
		}
		else if ( strcasecmp(argv[1], "rectangle") == 0 )
		{
			shapeMsg = "rectangle";
			for (int i=0; i < shapeAmount; i++)
			{
				shapeArray[i] = rectangle;
			}
		}
		else if ( strcasecmp(argv[1], "poly") == 0 )
		{
			shapeMsg = "poly";
			NoGUI::nShape fivegon = (NoGUI::nShape){5, testFill, testOutline};
			NoGUI::nShape sixgon = (NoGUI::nShape){6, testFill, testOutline};
			NoGUI::nShape sevengon = (NoGUI::nShape){7, testFill, testOutline};
			NoGUI::nShape ninegon = (NoGUI::nShape){9, testFill, testOutline};
			NoGUI::nShape tengon = (NoGUI::nShape){10, testFill, testOutline};
			NoGUI::nShape elevengon = (NoGUI::nShape){11, testFill, testOutline};
			shapeArray[0] = fivegon;
			shapeArray[1] = sixgon;
			shapeArray[2] = sevengon;
			shapeArray[3] = octagon;
			shapeArray[4] = tengon;
			shapeArray[5] = ninegon;
			shapeArray[6] = elevengon;
		}
		else if ( strcasecmp(argv[1], "polygon") == 0 )
		{
			shapeMsg = "polygon";
			NoGUI::nShape fivegon = (NoGUI::nShape){5, testFill, testOutline};
			NoGUI::nShape sixgon = (NoGUI::nShape){6, testFill, testOutline};
			NoGUI::nShape sevengon = (NoGUI::nShape){7, testFill, testOutline};
			NoGUI::nShape ninegon = (NoGUI::nShape){9, testFill, testOutline};
			NoGUI::nShape tengon = (NoGUI::nShape){10, testFill, testOutline};
			NoGUI::nShape elevengon = (NoGUI::nShape){11, testFill, testOutline};
			shapeArray[0] = octagon;
			shapeArray[1] = fivegon;
			shapeArray[2] = sevengon;
			shapeArray[3] = sixgon;
			shapeArray[4] = tengon;
			shapeArray[5] = ninegon;
			shapeArray[6] = elevengon;
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
		shapeArray[0] = line;
		shapeArray[1] = triangle;
		shapeArray[2] = rectangle;
		shapeArray[3] = ellipse;
		shapeArray[4] = rectangle;
		shapeArray[5] = octagon;
		shapeArray[6] = ellipse;
	}
	
	originArray[0] = (Vector2){-1 * elemSize.x, -1 * elemSize.y};
	originArray[1] = (Vector2){0, -1 * elemSize.y};
	originArray[2] = (Vector2){elemSize.x, -1 * elemSize.y};
	originArray[3] = (Vector2){0, 0}; 
	originArray[4] = (Vector2){-1 * elemSize.x, elemSize.y}; 
	originArray[5] = (Vector2){0, elemSize.y};
	originArray[6] = (Vector2){elemSize.x, elemSize.y};
	
	InitWindow(1280, 720, "test");
	SetTargetFPS(60);
	while ( !WindowShouldClose() )
	{
		if ( IsMouseButtonDown(MOUSE_LEFT_BUTTON) )
		{
			rotation++;
		}
		else if ( IsMouseButtonDown(MOUSE_RIGHT_BUTTON) )
		{
			rotation--;
		}
		BeginDrawing();
			ClearBackground(BLACK);
			NoGUI::DrawShape(tipShape, dataT);
			NoGUI::DrawShape(tipShape, shapeT);
			NoGUI::DrawCText(TextFormat("Angle: %i", rotation), dataText, dataT);
			NoGUI::DrawCText(shapeMsg, shapeText, shapeT);
			for (int i=0; i < shapeAmount; i++)
			{
				NoGUI::DrawShape(shapeArray[i], posArray[i], elemSize, originArray[i], rotation);
			}
		EndDrawing();
	}
	
	return 0;
}