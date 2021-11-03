#include "../../src/GUI.h"

Vector2 window = {470, 720};
Vector2 center = {window.x / 2, window.y / 2};
int spacing = 100;
int fps = 60;

int main(int argc, char ** argv)
{
	InitWindow(window.x, window.y, "Types");
	SetTargetFPS(fps);
	
	NoGUI::GUIManager manager = NoGUI::GUIManager();
	Color INVISIBLE = (Color){0, 0, 0, 1};
	
	NoGUI::CText textStyle = NoGUI::CText();
	textStyle.align = NoGUI::TextAlign::CENTER;
	NoGUI::CText labelText = NoGUI::CText();
	labelText.align = NoGUI::TextAlign::TOP;
	labelText.wrap = NoGUI::TextWrap::DOWN;
	labelText.margin.y = 2;
	
	NoGUI::Style elemStyle = {BLACK, RAYWHITE, (Vector2){center.x, 40}, (Vector2){75, 35}, 4, 4, 0};
	NoGUI::Style elemText = {INVISIBLE, BLACK, (Vector2){center.x, elemStyle.pos.y + elemStyle.radius.y * 2 + 25}, (Vector2){200, 50}, 4, 4, 0};
	NoGUI::Style buttonStyle = {BLACK, RAYWHITE, (Vector2){center.x, elemText.pos.y + spacing}, (Vector2){75, 35}, 4, 4, 0};
	NoGUI::Style buttonText = {INVISIBLE, BLACK, (Vector2){center.x, buttonStyle.pos.y + buttonStyle.radius.y * 2 + 25}, (Vector2){200, 50}, 4, 4, 0};
	NoGUI::Style inputStyle = {BLACK, RAYWHITE, (Vector2){center.x, buttonText.pos.y + spacing}, (Vector2){75, 35}, 4, 4, 0};
	NoGUI::Style inputText = {INVISIBLE, BLACK, (Vector2){center.x, inputStyle.pos.y + buttonStyle.radius.y * 2 + 25}, (Vector2){200, 50}, 4, 4, 0};
	
	std::shared_ptr< NoGUI::Element > element = manager.addElement< NoGUI::Element >(elemStyle, "Base", "Base");
	std::shared_ptr< NoGUI::Element > elemLabel = manager.addElement< NoGUI::Element >(elemText, "Base Class to Inherit from. Focus has to be manually set.", "Label");
	std::shared_ptr< NoGUI::Element > button = manager.addElement< NoGUI::Button >(buttonStyle, "Button", "Button");
	std::shared_ptr< NoGUI::Element > buttonLabel = manager.addElement< NoGUI::Element >(buttonText, "Focused when pressed (not held).", "Label");
	std::shared_ptr< NoGUI::Element > input = manager.addElement< NoGUI::Input >(inputStyle, "Input", "Input");
	std::shared_ptr< NoGUI::Element > inputLabel = manager.addElement< NoGUI::Element >(inputText, "Focus when hovered. Notify on and off hover", "Label");
	
	elemLabel->addComponent< NoGUI::CText >(labelText);
	buttonLabel->addComponent< NoGUI::CText >(labelText);
	inputLabel->addComponent< NoGUI::CText >(labelText);
	element->addComponent< NoGUI::CText >(textStyle);
	button->addComponent< NoGUI::CText >(textStyle);
	input->addComponent< NoGUI::CText >(textStyle);
	
	while ( !WindowShouldClose() )
	{
		manager.update();
		BeginDrawing();
			ClearBackground(GRAY);
			manager.render();
		EndDrawing();
	}

	return 0;
}