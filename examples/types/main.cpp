#include "../../src/GUI.h"

Vector2 window = {470, 720};
Vector2 center = {window.x / 2, window.y / 2};
int spacing = 100;
int fps = 60;

int main(int argc, char ** argv)
{
	InitWindow(window.x, window.y, "Shapes");
	SetTargetFPS(fps);
	
	NoGUI::GUIManager manager = NoGUI::GUIManager();
	NoGUI::CText textStyle = NoGUI::CText();
	textStyle.align = NoGUI::TextAlign::CENTER;
	NoGUI::Style elemStyle = {BLACK, GRAY, (Vector2){center.x, 60}, (Vector2){75, 35}, 4, 4, 0};
	NoGUI::Style buttonStyle = {BLACK, GRAY, (Vector2){center.x, elemStyle.pos.y + spacing}, (Vector2){75, 35}, 4, 4, 0};
	
	std::shared_ptr< NoGUI::Element > element = manager.addElement< NoGUI::Element >(elemStyle, "Base", "Base");
	std::shared_ptr< NoGUI::Element > button = manager.addElement< NoGUI::Button >(buttonStyle, "Button", "Button");
	
	element->addComponent< NoGUI::CText >(textStyle);
	button->addComponent< NoGUI::CText >(textStyle);
	
	while ( !WindowShouldClose() )
	{
		manager.update();
		BeginDrawing();
			ClearBackground(RAYWHITE);
			manager.render();
		EndDrawing();
	}

	return 0;
}