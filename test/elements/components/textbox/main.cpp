#include "../../../../src/GUI.h"

int main(int argc, char ** argv)
{
	// initialization
	Vector2 window = {1280, 720};
	Vector2 elemSize = {200, 200};
	std::vector< std::shared_ptr< NoGUI::Element > > elemVec;
	char msg[NoMAD::INBUFF];
	int msgLength = 0;
	TextAppend(msg, "yea yea Supercalifragilisticexpialidociousdoesthemostest yea yea", &msgLength);
	
	InitWindow(window.x, window.y, "test");
	SetTargetFPS(60);
	
	std::shared_ptr< NoGUI::Fill > fill = std::make_shared< NoGUI::Fill >(GRAY);
	std::shared_ptr< NoGUI::Fill > noFill = std::make_shared< NoGUI::Fill >((Color){0, 0, 0, 0});
	std::shared_ptr< NoGUI::Fill > lineFill = std::make_shared< NoGUI::Fill >(BLUE);
	std::shared_ptr< NoGUI::Fill > toggleFill = std::make_shared< NoGUI::Fill >(RED);
	std::shared_ptr< NoGUI::Outline > outline = std::make_shared< NoGUI::Outline >(lineFill, 3);
	std::shared_ptr< NoGUI::nShape > rect = std::make_shared< NoGUI::nShape >(4, fill, outline);
	std::shared_ptr< NoGUI::nShape > dataRect = std::make_shared< NoGUI::nShape >(4, noFill);
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
	NoGUI::Transform topLeftPos = NoGUI::Transform((Vector2){0, 0}, elemSize, topLeft);
	NoGUI::Transform togglePos = NoGUI::Transform((Vector2){0, elemSize.y - 20.0f}, elemSize, topLeft);

	std::shared_ptr< NoGUI::Element > centerElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, centerPos, std::make_shared< NoGUI::CContainer >(), "Test", msg);
	std::shared_ptr< NoGUI::Element > dataElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, dataRect, topLeftPos, std::make_shared< NoGUI::CContainer >(), "Tip");
	std::shared_ptr< NoGUI::Element > toggleElem = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, dataRect, togglePos, std::make_shared< NoGUI::CContainer >(), "Tip", "WRAP: TRUE");
	
	centerElem->components->addComponent< NoGUI::CTextBox >(nullptr, font, 20, topLeft);
	dataElem->components->addComponent< NoGUI::CText >(nullptr, font, 20, topLeft);
	toggleElem->components->addComponent< NoGUI::CText >(toggleFill, font, 20, topLeft);
	
	elemVec.push_back(centerElem);
	elemVec.push_back(dataElem);
	elemVec.push_back(toggleElem);
	
	// main
	while ( !WindowShouldClose() )
	{	
		float translateX = 0.0f;
		float translateY = 0.0f;
		float scroll = GetMouseWheelMove();
		if ( IsKeyPressed(KEY_SPACE) )
		{
			centerElem->components->getComponent< NoGUI::CTextBox >().wrap = !centerElem->components->getComponent< NoGUI::CTextBox >().wrap;
		}
		if ( IsKeyPressed(KEY_LEFT) )
		{
			translateX -= 1.0f;
		}
		else if ( IsKeyPressed(KEY_RIGHT) )
		{
			translateX += 1.0f;
		}
		if ( IsKeyPressed(KEY_DOWN) )
		{
			translateY -= 1.0f;
		}
		else if ( IsKeyPressed(KEY_UP) )
		{
			translateY += 1.0f;
		}
		if ( IsKeyDown(KEY_W) )
		{
			centerElem->components->getComponent< NoGUI::CTextBox >().scrollAmount.y -= 1.0f;
		}
		else if ( IsKeyDown(KEY_S) )
		{
			centerElem->components->getComponent< NoGUI::CTextBox >().scrollAmount.y += 1.0f;
		}
		if ( IsKeyDown(KEY_A) )
		{
			centerElem->components->getComponent< NoGUI::CTextBox >().scrollAmount.x -= 1.0f;
		}
		else if ( IsKeyDown(KEY_D) )
		{
			centerElem->components->getComponent< NoGUI::CTextBox >().scrollAmount.x += 1.0f;
		}
		if ( IsKeyPressed(KEY_Z) ) // top left
		{
			centerElem->components->getComponent< NoGUI::CTextBox >().align = NoGUI::Align(-1, -1);
		}
		else if ( IsKeyPressed(KEY_X) ) // top right
		{
			centerElem->components->getComponent< NoGUI::CTextBox >().align = NoGUI::Align(1, -1);
		}
		else if ( IsKeyPressed(KEY_C) ) // center
		{
			centerElem->components->getComponent< NoGUI::CTextBox >().align = NoGUI::Align(0, 0);
		}
		else if ( IsKeyPressed(KEY_V) ) // top
		{
			centerElem->components->getComponent< NoGUI::CTextBox >().align = NoGUI::Align(0, -1);
		}
		else if ( IsKeyPressed(KEY_B) ) // bottom
		{
			centerElem->components->getComponent< NoGUI::CTextBox >().align = NoGUI::Align(0, 1);
		}
		else if ( IsKeyPressed(KEY_N) ) // bottom left
		{
			centerElem->components->getComponent< NoGUI::CTextBox >().align = NoGUI::Align(-1, 1);
		}
		else if ( IsKeyPressed(KEY_M) ) // bottom right
		{
			centerElem->components->getComponent< NoGUI::CTextBox >().align = NoGUI::Align(1, 1);
		}
		else if ( IsKeyPressed(KEY_COMMA) ) // center left
		{
			centerElem->components->getComponent< NoGUI::CTextBox >().align = NoGUI::Align(-1, 0);
		}
		else if ( IsKeyPressed(KEY_PERIOD) ) // center right
		{
			centerElem->components->getComponent< NoGUI::CTextBox >().align = NoGUI::Align(1, 0);
		}
		dataElem->setInner(TextFormat("Text Size: %01.01f\nHorizontal Spacing: %01.01f\nVertical Spacing: %01.01f", centerElem->components->getComponent< NoGUI::CTextBox >().size, centerElem->components->getComponent< NoGUI::CTextBox >().spacing.x, centerElem->components->getComponent< NoGUI::CTextBox >().spacing.y));
		
		BeginDrawing();
			ClearBackground(BLACK);
			for ( auto elem : elemVec )
			{
				if (!TextIsEqual(elem->getTag(), "Tip"))
				{
					NoGUI::CTextBox& txtComp = elem->components->getComponent< NoGUI::CTextBox >();
					txtComp.spacing.x += translateX;
					txtComp.spacing.y += translateY;
					if ( scroll )
					{
						txtComp.size += 1.0f * scroll;
					}
					if ( txtComp.wrap )
					{
						toggleElem->setInner("WRAP: TRUE");
						toggleFill->col = GREEN; 
					}
					else
					{
						toggleElem->setInner("WRAP: FALSE");
						toggleFill->col = RED; 
					}
				}
				elem->draw();
			}
		EndDrawing();
	}
	
	return 0;
}