#include "../../src/GUI.h"

#include <iostream>

class EventHandler : public NoGUI::Listener
{
	NoGUI::nShape newShape;
	void onNotify(std::shared_ptr< NoGUI::Element > elem, NoGUI::Event event)
	{
		std::cout << "Event recieved!" << std::endl;
		if ( event == NoGUI::Event::ONFOCUS )
		{
			newShape = NoGUI::nShape(0, elem->getShape()->fill, elem->getShape()->outline);
			elem->setShape(std::make_shared< NoGUI::nShape >(newShape));
		}
	}
};

int main(int argc, char ** argv)
{
	Vector2 window = {720, 1280};
	Vector2 center = {window.x / 2, window.y / 2};
	Vector2 buttonSize = {100, 50};
	std::shared_ptr< NoGUI::Fill > buttonFill = std::make_shared< NoGUI::Fill >(GRAY, DARKGRAY);
	std::shared_ptr< NoGUI::Fill > lineFill = std::make_shared< NoGUI::Fill >(GREEN, LIME);
	std::shared_ptr< NoGUI::Fill > textFill = std::make_shared< NoGUI::Fill >(WHITE);
	std::shared_ptr< NoGUI::Outline > outline = std::make_shared< NoGUI::Outline >(lineFill, 3);
	std::shared_ptr< NoGUI::nShape > buttonShape = std::make_shared< NoGUI::nShape >(4, buttonFill, outline);
	NoGUI::Transform buttonPos = NoGUI::Transform(center, buttonSize, NoGUI::Align(0, 0));
	
	NoGUI::GUIManager gui = NoGUI::GUIManager(true);
	std::shared_ptr< NoGUI::CContainer > components = std::make_shared< NoGUI::CContainer >();
	components->addComponent< NoGUI::CText >(textFill, nullptr, 20, NoGUI::Align(-1, 0));
	gui.getPage(0)->addComponents("Button", components);
	std::shared_ptr< NoGUI::Element > button1 = gui.getPage(0)->addElement< NoGUI::Button >(buttonShape, buttonPos, "Button", "1");
	std::shared_ptr< NoGUI::Element > button2 = gui.getPage(0)->addElement< NoGUI::Button >(buttonShape, buttonPos, "Button", "2");
	button2->translate(buttonSize.x, 0);
	
	std::shared_ptr< EventHandler > eventer = std::make_shared< EventHandler >();
	gui.addListener(eventer);
	
	InitWindow(window.x, window.y, "test");
	SetTargetFPS(60);
	while ( !WindowShouldClose() )
	{	
		gui.update();
		BeginDrawing();
			ClearBackground(BLACK);
			gui.render();
		EndDrawing();
	}
	
	return 0;
}