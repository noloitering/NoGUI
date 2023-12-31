#include "../../../../src/GUI.h"

int main(int argc, char ** argv)
{
	// initialization
	Vector2 window = {1280, 720};
	Vector2 elemSize = {200, 50};
	std::vector< std::shared_ptr< NoGUI::Element > > elemVec;
	
	InitWindow(window.x, window.y, "test");
	SetTargetFPS(60);
	
	std::shared_ptr< NoGUI::Fill > fill = std::make_shared< NoGUI::Fill >(GRAY);
	std::shared_ptr< NoGUI::Fill > noFill = std::make_shared< NoGUI::Fill >(BLANK);
	std::shared_ptr< NoGUI::Fill > lineFill = std::make_shared< NoGUI::Fill >(BLUE, RED);
	std::shared_ptr< NoGUI::Outline > outline = std::make_shared< NoGUI::Outline >(lineFill, 1);
	std::shared_ptr< NoGUI::nShape > rect = std::make_shared< NoGUI::nShape >(4, fill, outline);
	std::shared_ptr< NoGUI::nShape > noRect = std::make_shared< NoGUI::nShape >(4, noFill);
	std::shared_ptr< Font > font = nullptr;
	if ( argc > 1 )
	{
		font = std::make_shared< Font >(LoadFont(argv[1]));
	}
	else
	{
		font = std::make_shared< Font >(GetFontDefault()); 
	}
	
	NoGUI::Transform centerPos = NoGUI::Transform((Vector2){window.x / 2, window.y / 2}, elemSize, NoGUI::Align(0, 0));
	NoGUI::Transform val1Pos = NoGUI::Transform((Vector2){8, 8}, elemSize, NoGUI::Align(-1, -1));
	NoGUI::Transform val2Pos = NoGUI::Transform((Vector2){8, 116}, (Vector2){50, 50}, NoGUI::Align(-1, -1));
	NoGUI::Transform button1Pos = NoGUI::Transform((Vector2){416, 8}, (Vector2){50, 50}, NoGUI::Align(-1, -1));
	NoGUI::Transform button2Pos = NoGUI::Transform((Vector2){116, 116}, (Vector2){50, 50}, NoGUI::Align(-1, -1));
	NoGUI::Transform dataPos = NoGUI::Transform((Vector2){window.x - 8, 8}, elemSize, NoGUI::Align(1, -1));
	std::shared_ptr< NoGUI::Element > centerElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, centerPos, "Test", "", std::make_shared< NoGUI::CContainer >());
	std::shared_ptr< NoGUI::Element > textSetting = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, val1Pos, "TextData", "", std::make_shared< NoGUI::CContainer >());
	std::shared_ptr< NoGUI::Element > capSetting = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, val2Pos, "CapData", "", std::make_shared< NoGUI::CContainer >());
	std::shared_ptr< NoGUI::Element > textButton = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, button1Pos, "TextButton", "set", std::make_shared< NoGUI::CContainer >());
	std::shared_ptr< NoGUI::Element > capButton = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, button2Pos, "CapButton", "set", std::make_shared< NoGUI::CContainer >());
	std::shared_ptr< NoGUI::Element > dataElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, noRect, dataPos, "Data", "", std::make_shared< NoGUI::CContainer >());
	
	centerElem->components->addComponent< NoGUI::CText >(nullptr, font, 20, NoGUI::Align(-1, 0));
	centerElem->components->addComponent< NoGUI::CInput >(5);
	textSetting->components->addComponent< NoGUI::CTextBox >(nullptr, font, 20, NoGUI::Align(-1, 0));
	textSetting->components->addComponent< NoGUI::CInput >(NoMAD::INBUFF);
	capSetting->components->addComponent< NoGUI::CText >(nullptr, font, 20, NoGUI::Align(-1, 0));
	capSetting->components->addComponent< NoGUI::CInput >(4);
	textButton->components->addComponent< NoGUI::CText >(nullptr, font, 20, NoGUI::Align(0, 0));
	capButton->components->addComponent< NoGUI::CText >(nullptr, font, 20, NoGUI::Align(0, 0));
	dataElem->components->addComponent< NoGUI::CText >(nullptr, font, 30, NoGUI::Align(1, -1));
	
	elemVec.push_back(centerElem);
	elemVec.push_back(textSetting);
	elemVec.push_back(capSetting);
	elemVec.push_back(textButton);
	elemVec.push_back(capButton);
	elemVec.push_back(dataElem);
	
	// main
	while ( !WindowShouldClose() )
	{
		dataElem->setInner(TextFormat("INPUT CHARS: %i/%i", centerElem->components->getComponent< NoGUI::CInput >().i, centerElem->components->getComponent< NoGUI::CInput >().cap));
		float scroll = GetMouseWheelMove();
		if ( scroll )
		{
			centerElem->rotate(1.0f * scroll, NoGUI::Align(0, 0));
		}
		BeginDrawing();
			ClearBackground(BLACK);
			for ( auto elem : elemVec )
			{
				elem->isHover();
				if ( TextIsEqual(elem->getTag(), "TextButton") )
				{
					if ( elem->getHover() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
					{
						centerElem->setInner(textSetting->getInner());
						centerElem->components->getComponent< NoGUI::CInput >().i = TextLength(textSetting->getInner());
					}
				}
				if ( TextIsEqual(elem->getTag(), "CapButton") )
				{
					if ( elem->getHover() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
					{
						centerElem->components->getComponent< NoGUI::CInput >().cap = TextToInteger(capSetting->getInner());
					}
				}
				elem->draw();
			}
		EndDrawing();
	}
	
	return 0;
}