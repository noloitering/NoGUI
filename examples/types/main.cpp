#include "../../src/GUI.h"

Vector2 window = {470, 1080};
Vector2 center = {window.x / 2, window.y / 2};
Color focusCol = GRAY;
Color backCol = BLACK;
std::vector< std::string > notification(1, "Notify!");
int spacing = 100;
int fps = 10;

class EventHandler : public NoGUI::Listener
{
	void onNotify(std::shared_ptr< NoGUI::Element > elem)
	{
//		std::vector< std::string > notification;
//		notification.push_back("Notify!");
		NoGUI::CText& elemText = elem->getComponent< NoGUI::CText >();
		if ( elemText.owned )
		{
			elemText.contents = notification;
		}
		if ( elem->getFocus() )
		{
			elem->recol(focusCol, focusCol);
		}
		else
		{
			elem->recol(backCol, backCol);
		}
	}
};


int main(int argc, char ** argv)
{
	InitWindow(window.x, window.y, "Types");
	SetTargetFPS(fps);
	
	EventHandler handler;
	NoGUI::GUIManager manager = NoGUI::GUIManager();
	manager.addListener(std::make_shared< EventHandler >(handler));
	Color INVISIBLE = (Color){0, 0, 0, 1};
	
	NoGUI::CText textStyle = NoGUI::CText();
	textStyle.align = NoGUI::TextAlign::CENTER;
	NoGUI::CText labelText = NoGUI::CText();
	labelText.align = NoGUI::TextAlign::TOP;
	labelText.wrap = NoGUI::TextWrap::DOWN;
	labelText.margin.y = 2;
	
	manager.getPage(0)->addComponent< NoGUI::CText >(textStyle);
	std::shared_ptr< NoGUI::Page > labels = manager.addPage(true);
	labels->addComponent< NoGUI::CText >(labelText);
	
	NoGUI::Style elemStyle = {BLACK, RAYWHITE, (Vector2){center.x, 40}, (Vector2){75, 35}, 4, 4, 0};
	NoGUI::Style elemText = {INVISIBLE, BLACK, (Vector2){center.x, elemStyle.pos.y + elemStyle.radius.y * 2 + 25}, (Vector2){200, 50}, 4, 4, 0};
	NoGUI::Style buttonStyle = {BLACK, RAYWHITE, (Vector2){center.x, elemText.pos.y + spacing}, (Vector2){75, 35}, 4, 4, 0};
	NoGUI::Style buttonText = {INVISIBLE, BLACK, (Vector2){center.x, buttonStyle.pos.y + buttonStyle.radius.y * 2 + 25}, (Vector2){200, 50}, 4, 4, 0};
	NoGUI::Style inputStyle = {BLACK, RAYWHITE, (Vector2){center.x, buttonText.pos.y + spacing}, (Vector2){75, 35}, 4, 4, 0};
	NoGUI::Style inputText = {INVISIBLE, BLACK, (Vector2){center.x, inputStyle.pos.y + buttonStyle.radius.y * 2 + 25}, (Vector2){200, 50}, 4, 4, 0};
	NoGUI::Style boxStyle = {BLACK, RAYWHITE, (Vector2){center.x, inputText.pos.y + spacing}, (Vector2){75, 35}, 4, 4, 0};
	NoGUI::Style boxText = {INVISIBLE, BLACK, (Vector2){center.x, boxStyle.pos.y + inputStyle.radius.y * 2 + 25}, (Vector2){200, 50}, 4, 4, 0};
	
	std::shared_ptr< NoGUI::Element > element = manager.addElement< NoGUI::Element >(elemStyle, "Element", "Base");
	std::shared_ptr< NoGUI::Element > elemLabel = labels->addElement< NoGUI::Element >(elemText, "Base Class to Inherit from. Focus has to be manually set.", "Label");
	std::shared_ptr< NoGUI::Element > button = manager.addElement< NoGUI::Button >(buttonStyle, "Button", "Button");
	button->setHoverCol(BLACK);
	std::shared_ptr< NoGUI::Element > buttonLabel = labels->addElement< NoGUI::Element >(buttonText, "Focused when pressed (not held).", "Label");
	std::shared_ptr< NoGUI::Element > input = manager.addElement< NoGUI::Input >(inputStyle, "Input", "Input");
	std::shared_ptr< NoGUI::Element > inputLabel = labels->addElement< NoGUI::Element >(inputText, "Focus when hovered. Notify on and off hover", "Label");
	std::shared_ptr< NoGUI::Element > box = manager.addElement< NoGUI::Toggle >(boxStyle, "Toggle", "Input");
	std::shared_ptr< NoGUI::Element > boxLabel = labels->addElement< NoGUI::Element >(boxText, "Focus toggles on/off when pressed. Notify on press", "Label");
	
	while ( !WindowShouldClose() )
	{
		manager.update();
		BeginDrawing();
			ClearBackground(GRAY);
			manager.render();
		EndDrawing();
		// reset to inner
		for (auto elem : manager.getPage(0)->getElements())
		{
			NoGUI::CText& elemText = elem->getComponent< NoGUI::CText >();
			if ( elemText.owned )
			{
				elemText.contents.clear();
			}
		}
	}

	return 0;
}