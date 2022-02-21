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
			elemText.owned = false;
		}
		else
		{
			elemText.owned = true;
		}
	}
};


int main(int argc, char ** argv)
{
	InitWindow(window.x, window.y, "Types");
	SetTargetFPS(fps);
	
	EventHandler handler;
	NoGUI::GUIManager manager = NoGUI::GUIManager(true);
	manager.addListener(std::make_shared< EventHandler >(handler));
	
	Color INVISIBLE = (Color){0, 0, 0, 1};
	manager.getPage()->addComponents("Text", std::make_shared< NoGUI::CContainer >());
	manager.getPage()->getComponents("Text")->addComponent< NoGUI::CText >();
	manager.getPage()->getComponents("Text")->getComponent< NoGUI::CText >().align = NoGUI::TextAlign::CENTER;
	
	NoGUI::Style elemStyle = {BLACK, RAYWHITE, (Vector2){center.x, 40}, (Vector2){75, 35}, 4, 4, 0};
	NoGUI::Style elemText = {INVISIBLE, BLACK, (Vector2){center.x, elemStyle.pos.y + elemStyle.radius.y * 2 + 25}, (Vector2){200, 50}, 4, 4, 0};
	NoGUI::Style buttonStyle = {BLACK, RAYWHITE, (Vector2){center.x, elemText.pos.y + spacing}, (Vector2){75, 35}, 4, 4, 0};
	
	std::shared_ptr< NoGUI::Element > button = manager.addElement< NoGUI::Element >(elemStyle, "Placeholder", "Text");
	std::shared_ptr< NoGUI::Element > element = manager.addElement< NoGUI::Trigger >(buttonStyle, "Hide", "Text");
	button->setHoverCol(BLACK);
	
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