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
		NoGUI::CText& elemText = elem->components->getComponent< NoGUI::CText >();
		if ( elemText.owned )
		{
			elem->setInnerWrap(notification);
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
	
	manager.getPage()->addComponents("Base", std::make_shared< NoGUI::CContainer >());
	manager.getPage()->getComponents("Base")->addComponent< NoGUI::CText >(textStyle);
	manager.getPage()->addComponents("Button", std::make_shared< NoGUI::CContainer >());
	manager.getPage()->getComponents("Button")->addComponent< NoGUI::CText >(textStyle);
	manager.getPage()->addComponents("Trigger", std::make_shared< NoGUI::CContainer >());
	manager.getPage()->getComponents("Trigger")->addComponent< NoGUI::CText >(textStyle);
	manager.getPage()->addComponents("Input", std::make_shared< NoGUI::CContainer >());
	manager.getPage()->getComponents("Input")->addComponent< NoGUI::CText >(textStyle);
	std::shared_ptr< NoGUI::Page > labels = manager.addPage(true);
	labels->addComponents("Label", std::make_shared< NoGUI::CContainer >());
	labels->getComponents("Label")->addComponent< NoGUI::CText >(labelText);
	
	NoGUI::Style elemStyle = {BLACK, RAYWHITE, (Vector2){center.x, 40}, (Vector2){75, 35}, 4, 4, 0};
	NoGUI::Style elemText = {INVISIBLE, BLACK, (Vector2){center.x, elemStyle.pos.y + elemStyle.radius.y * 2 + 25}, (Vector2){200, 50}, 4, 4, 0};
	NoGUI::Style buttonStyle = {BLACK, RAYWHITE, (Vector2){center.x, elemText.pos.y + spacing}, (Vector2){75, 35}, 4, 4, 0};
	NoGUI::Style buttonText = {INVISIBLE, BLACK, (Vector2){center.x, buttonStyle.pos.y + buttonStyle.radius.y * 2 + 25}, (Vector2){200, 50}, 4, 4, 0};
	NoGUI::Style inputStyle = {BLACK, RAYWHITE, (Vector2){center.x, buttonText.pos.y + spacing}, (Vector2){75, 35}, 4, 4, 0};
	NoGUI::Style inputText = {INVISIBLE, BLACK, (Vector2){center.x, inputStyle.pos.y + buttonStyle.radius.y * 2 + 25}, (Vector2){200, 50}, 4, 4, 0};
	NoGUI::Style boxStyle = {BLACK, RAYWHITE, (Vector2){center.x, inputText.pos.y + spacing}, (Vector2){75, 35}, 4, 4, 0};
	NoGUI::Style boxText = {INVISIBLE, BLACK, (Vector2){center.x, boxStyle.pos.y + inputStyle.radius.y * 2 + 25}, (Vector2){200, 50}, 4, 4, 0};
	NoGUI::Style triggerStyle = {BLACK, RAYWHITE, (Vector2){center.x, boxText.pos.y + spacing}, (Vector2){75, 35}, 4, 4, 0};
	NoGUI::Style triggerText = {INVISIBLE, BLACK, (Vector2){center.x, triggerStyle.pos.y + boxStyle.radius.y * 2 + 25}, (Vector2){200, 50}, 4, 4, 0};
	
	std::shared_ptr< NoGUI::Element > element = manager.addElement< NoGUI::Element >(elemStyle, "Base", "Element");
	std::shared_ptr< NoGUI::Element > elemLabel = labels->addElement< NoGUI::Element >(elemText, "Label", "Base Class to Inherit from. Focus has to be manually set.");
	std::shared_ptr< NoGUI::Element > button = manager.addElement< NoGUI::Button >(buttonStyle, "Button", "Button");
	button->setHoverCol(BLACK);
	std::shared_ptr< NoGUI::Element > buttonLabel = labels->addElement< NoGUI::Element >(buttonText, "Label", "Focus when pressed (not held). Notify on and off press");
	std::shared_ptr< NoGUI::Element > trigger = manager.addElement< NoGUI::Trigger >(triggerStyle, "Trigger", "Trigger");
	trigger->setHoverCol(BLACK);
	std::shared_ptr< NoGUI::Element > triggerLabel = labels->addElement< NoGUI::Element >(triggerText, "Label", "Focus when held. Notify on and off press");
	std::shared_ptr< NoGUI::Element > input = manager.addElement< NoGUI::Input >(inputStyle, "Input", "Input");
	std::shared_ptr< NoGUI::Element > inputLabel = labels->addElement< NoGUI::Element >(inputText, "Label", "Focus when hovered. Notify on and off hover");
	std::shared_ptr< NoGUI::Element > box = manager.addElement< NoGUI::Toggle >(boxStyle, "Input", "Toggle");
	std::shared_ptr< NoGUI::Element > boxLabel = labels->addElement< NoGUI::Element >(boxText, "Label", "Focus toggles on/off when pressed. Notify on press");
	
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
			NoGUI::CText& elemText = elem->components->getComponent< NoGUI::CText >();
			if ( elemText.owned )
			{
				elem->setInnerWrap(std::vector< std::string >());
			}
		}
	}

	return 0;
}