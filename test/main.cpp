#include <iostream>

#include "../src/GUI.h"

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
	std::shared_ptr< NoGUI::Fill > testFill = std::make_shared< NoGUI::Fill >(RAYWHITE);
	NoGUI::Shape testShape = (NoGUI::Shape){2, testFill, nullptr};
	InitWindow(1280, 720, "test");
	while ( !WindowShouldClose() )
	{
		BeginDrawing();
			ClearBackground(BLACK);
			NoGUI::DrawShapeCenter((Vector2){640, 360}, (Vector2){100, 50}, testShape, 0);
			NoGUI::DrawShapeLeft((Vector2){0, 0}, (Vector2){100, 50}, testShape, 0);
			NoGUI::DrawShapeRight((Vector2){1280, 0}, (Vector2){100, 50}, testShape, 0);
			NoGUI::DrawShapeTop((Vector2){640, 0}, (Vector2){100, 50}, testShape, 0);
			NoGUI::DrawShapeBottom((Vector2){640, 720}, (Vector2){100, 50}, testShape, 0);
			NoGUI::DrawShapeBottomL((Vector2){0, 720}, (Vector2){100, 50}, testShape, 0);
			NoGUI::DrawShapeBottomR((Vector2){1280, 720}, (Vector2){100, 50}, testShape, 0);
		EndDrawing();
	}
	
	return 0;
}