#include "../../../src/GUI.h"

#include <iostream>

NoGUI::Manager contextMenu = NoGUI::Manager(false);
NoGUI::Manager gui;

class EventHandler : public NoGUI::Listener
{
	void onNotify(std::shared_ptr< NoGUI::Element > elem, NoGUI::Event event)
	{
		if ( TextIsEqual("DropDown", elem->getTag()) )
		{
			switch (event)
			{
				case NoGUI::Event::ONFOCUS:
				{
					contextMenu.setActive(0);
					
					break;
				}
				
				case NoGUI::Event::OFFFOCUS:
				{
					contextMenu.getPage(0)->setActive(false);
					
					break;
				}
				
				default:
				{
					
					break;
				}
			}
		}
		else if ( TextIsEqual("Option", elem->getTag()) )
		{
			switch (event)
			{
				case NoGUI::Event::ONFOCUS:
				{
					NoGUI::ContextPage* options = dynamic_cast< NoGUI::ContextPage* >(contextMenu.getPage(0).get());
					std::shared_ptr< NoGUI::Element > context = options->getContext();
					context->setInner(elem->getInner());
					context->setFocus(false);
					contextMenu.getPage(0)->setActive(false);
					
					break;
				}
				
				default:
				{
					
					break;
				}
			}
		}
		else if ( TextIsEqual("Add", elem->getTag()) )
		{
			switch (event)
			{
				case NoGUI::Event::ONFOCUS:
				{
					NoGUI::ContextPage* options = dynamic_cast< NoGUI::ContextPage* >(contextMenu.getPage(0).get());
					std::shared_ptr< NoGUI::Element > lastOption = options->getElement(options->size() -1);
					std::shared_ptr< NoGUI::Element > input = gui.getPage(0)->getElements("Input").front();
					options->addElement< NoGUI::Button >(lastOption->getShape(), lastOption->radius, "Option", input->getInner());
					input->setInner(TextFormat("Option %i", options->size() + 1));
					
					break;
				}
				
				default:
				{
					
					break;
				}
			}
		}
	}
};

int main(int argc, char ** argv)
{
	Vector2 window = {1280, 720};
	Vector2 elemSize = {100, 50};
	std::shared_ptr< NoGUI::Fill > elemFill = std::make_shared< NoGUI::Fill >(GRAY, DARKGRAY);
	std::shared_ptr< NoGUI::Fill > noFill = std::make_shared< NoGUI::Fill >(BLANK);
	std::shared_ptr< NoGUI::Fill > lineFill = std::make_shared< NoGUI::Fill >(DARKGRAY, RED);
	std::shared_ptr< NoGUI::Fill > textFill = std::make_shared< NoGUI::Fill >(WHITE);
	std::shared_ptr< NoGUI::Outline > lines = std::make_shared< NoGUI::Outline >(lineFill, 2);
	std::shared_ptr< NoGUI::nShape > rect = std::make_shared< NoGUI::nShape >(4, elemFill, lines);
	std::shared_ptr< NoGUI::nShape > inputBox = std::make_shared< NoGUI::nShape >(4, noFill, lines);
	NoGUI::Transform centerPos = NoGUI::Transform((Vector2){window.x / 2, window.y / 2 - elemSize.y * 2}, elemSize);
	NoGUI::Transform addPos = NoGUI::Transform((Vector2){window.x - elemSize.x, centerPos.position.y}, (Vector2){elemSize.y, elemSize.y}, NoGUI::Align(1, 0));
	NoGUI::Transform inputPos = NoGUI::Transform((Vector2){centerPos.pos(NoGUI::Align(1, 0)).x + 10, centerPos.position.y}, (Vector2){(addPos.pos(NoGUI::Align(-1, 0)).x - centerPos.pos(NoGUI::Align(1, 0)).x) / 2 - 10, elemSize.y}, NoGUI::Align(-1, 0));
	
	std::shared_ptr< EventHandler > listener = std::make_shared< EventHandler >();
	gui.addListener(listener);
	std::shared_ptr< NoGUI::CContainer > textComps = std::make_shared< NoGUI::CContainer >();
	textComps->addComponent< NoGUI::CText >(textFill);
	std::shared_ptr< NoGUI::CContainer > inputComps = std::make_shared< NoGUI::CContainer >();
	inputComps->addComponent< NoGUI::CText >(textFill, nullptr, 20.0f, NoGUI::Align(-1, 0));
	inputComps->addComponent< NoGUI::CInput >();
	gui.getPage(0)->addComponents("DropDown", textComps);
	gui.getPage(0)->addComponents("Add", textComps);
	gui.getPage(0)->addComponents("Input", inputComps);
	std::shared_ptr< NoGUI::Element > selector = gui.getPage(0)->addElement< NoGUI::Toggle >(rect, centerPos, "DropDown", "Select Option");
	gui.getPage(0)->addElement(inputBox, inputPos, "Input", "Option 2");
	gui.getPage(0)->addElement< NoGUI::Button >(rect, addPos, "Add", "+");
	std::shared_ptr< NoGUI::ContextPage > contextPg = std::make_shared< NoGUI::ContextPage >(selector, selector->pos(NoGUI::Align(0, 1)), false);
	contextPg->addComponents("Option", textComps);
	contextPg->addElement< NoGUI::Button >(rect, selector->radius, "Option", "Option 1");
	contextMenu.addPage(contextPg);
	contextMenu.addListener(listener);
	
	InitWindow(window.x, window.y, "test");
	SetTargetFPS(60);
	while ( !WindowShouldClose() )
	{
		if ( IsKeyPressed(KEY_UP) )
		{
			Vector2 contextPos = selector->pos(NoGUI::Align(0, -1));
			contextPos.y -= lines->thick / 2;
			contextPg->position = contextPos;
			contextPg->setFlow(NoGUI::Wrap::UP);
		}
		else if ( IsKeyPressed(KEY_DOWN) )
		{
			Vector2 contextPos = selector->pos(NoGUI::Align(0, 1));
			contextPos.y += lines->thick / 2;
			contextPg->position = contextPos;
			contextPg->setFlow(NoGUI::Wrap::DOWN);
		}
		BeginDrawing();
			ClearBackground(BLACK);
			gui.update();
			contextMenu.update();
			contextMenu.render();
			gui.render();
		EndDrawing();
	}
	
	return 0;
}