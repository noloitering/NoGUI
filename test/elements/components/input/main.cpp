#include "../../../../src/GUI.h"

int main(int argc, char ** argv)
{
	// initialization
	Vector2 window = {1280, 720};
	Vector2 elemSize = {200, 200};
	std::vector< std::shared_ptr< NoGUI::Element > > elemVec;
	char msg[NoMAD::INBUFF];
	int msgLength = 0;
	TextAppend(msg, "test a really long string like a really looong string. Like unbelievably long. Like dang that's some long text being all long and stuff. SUPER long", &msgLength);
	
	InitWindow(window.x, window.y, "test");
	SetTargetFPS(60);
	
	std::shared_ptr< NoGUI::Fill > fill = std::make_shared< NoGUI::Fill >(GRAY);
	std::shared_ptr< NoGUI::Fill > noFill = std::make_shared< NoGUI::Fill >((Color){0, 0, 0, 0});
	std::shared_ptr< NoGUI::Fill > lineFill = std::make_shared< NoGUI::Fill >(BLUE);
	std::shared_ptr< NoGUI::Outline > outline = std::make_shared< NoGUI::Outline >(lineFill, 3);
	std::shared_ptr< NoGUI::nShape > rect = std::make_shared< NoGUI::nShape >(4, fill, outline);
	std::shared_ptr< Font > font = nullptr;
	if ( argc > 1 )
	{
		font = std::make_shared< Font >(LoadFont(argv[1]));
	}
	else
	{
		font = std::make_shared< Font >(GetFontDefault());
	}
	
	NoGUI::Align center = NoGUI::Align(0, 0);
	NoGUI::Align topLeft = NoGUI::Align(-1, -1);
	
	NoGUI::Transform centerPos = NoGUI::Transform((Vector2){window.x / 2, window.y / 2}, elemSize, center);

	std::shared_ptr< NoGUI::Element > centerElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, centerPos, std::make_shared< NoGUI::CContainer >(), "Test", msg);
	
	centerElem->components->addComponent< NoGUI::CText >(nullptr, font, 20, topLeft, NoGUI::Wrap::DOWN, NoGUI::Crop::CUT);
	
	elemVec.push_back(centerElem);
	
	// main
	while ( !WindowShouldClose() )
	{	
		if ( IsKeyPressed(KEY_Z) ) // top left
		{
			centerElem->components->getComponent< NoGUI::CText >().align = NoGUI::Align(-1, -1);
		}
		else if ( IsKeyPressed(KEY_X) ) // top right
		{
			centerElem->components->getComponent< NoGUI::CText >().align = NoGUI::Align(1, -1);
		}
		else if ( IsKeyPressed(KEY_C) ) // center
		{
			centerElem->components->getComponent< NoGUI::CText >().align = NoGUI::Align(0, 0);
		}
		else if ( IsKeyPressed(KEY_V) ) // top
		{
			centerElem->components->getComponent< NoGUI::CText >().align = NoGUI::Align(0, -1);
		}
		else if ( IsKeyPressed(KEY_B) ) // bottom
		{
			centerElem->components->getComponent< NoGUI::CText >().align = NoGUI::Align(0, 1);
		}
		else if ( IsKeyPressed(KEY_N) ) // bottom left
		{
			centerElem->components->getComponent< NoGUI::CText >().align = NoGUI::Align(-1, 1);
		}
		else if ( IsKeyPressed(KEY_M) ) // bottom right
		{
			centerElem->components->getComponent< NoGUI::CText >().align = NoGUI::Align(1, 1);
		}
		else if ( IsKeyPressed(KEY_COMMA) ) // center left
		{
			centerElem->components->getComponent< NoGUI::CText >().align = NoGUI::Align(-1, 0);
		}
		else if ( IsKeyPressed(KEY_PERIOD) ) // center right
		{
			centerElem->components->getComponent< NoGUI::CText >().align = NoGUI::Align(1, 0);
		}

		BeginDrawing();
			ClearBackground(BLACK);
			for ( auto elem : elemVec )
			{
				elem->draw();
			}
		EndDrawing();
	}
	
	return 0;
}