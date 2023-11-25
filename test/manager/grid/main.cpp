#include "../../../src/GUI.h"

Vector2 window = {1280, 720};

int main(int argc, char ** argv)
{
	bool showGrid = false;
	if ( argc > 2 )
	{
		window.x = TextToInteger(argv[1]);
		window.y = TextToInteger(argv[2]);
	}
	NoGUI::ManagerGrid gui = NoGUI::ManagerGrid(true, window.x / 10, window.y / 10);
	std::shared_ptr< NoGUI::Fill > fill = std::make_shared< NoGUI::Fill >((Color){100, 100, 100, 100});
	std::shared_ptr< NoGUI::Fill > noFill = std::make_shared< NoGUI::Fill >((Color){0, 0, 0, 0});
	std::shared_ptr< NoGUI::Fill > slideFill = std::make_shared< NoGUI::Fill >(LIME);
	std::shared_ptr< NoGUI::Fill > outlineFill = std::make_shared< NoGUI::Fill >(GRAY);
	
	std::shared_ptr< NoGUI::Outline > outline = std::make_shared< NoGUI::Outline >(outlineFill, 2);
	
	std::shared_ptr< NoGUI::nShape > UIRect = std::make_shared< NoGUI::nShape >(4, fill);
	std::shared_ptr< NoGUI::nShape > slider = std::make_shared< NoGUI::nShape >(4, noFill, outline);
	std::shared_ptr< NoGUI::nShape > slide = std::make_shared< NoGUI::nShape >(4, slideFill);
	
	NoGUI::Transform leftPos = NoGUI::Transform((Vector2){0, 5}, (Vector2){1, 5}, NoGUI::Align(-1, 0));
	NoGUI::Transform sliderPos = NoGUI::Transform((Vector2){0.25, 1}, (Vector2){0.75, 0.5}, NoGUI::Align(-1, -1));
	NoGUI::Transform slidePos = NoGUI::Transform((Vector2){0.1, 0}, (Vector2){0.1, 0.5}, NoGUI::Align(-1, 0));
	
	gui.getPage(0)->addComponents("Slider");
	NoGUI::CMultiShape& slideComp = gui.getPage(0)->getComponents("Slider")->addComponent< NoGUI::CMultiShape >();
	slideComp.shapes.push_back(std::make_pair(slide, slidePos));
	
	std::shared_ptr< NoGUI::Element > previewContainer = gui.getPage(0)->addElement(UIRect, leftPos, "Container");
	std::shared_ptr< NoGUI::Element > sliderPreview = gui.getPage(0)->addElement(slider, sliderPos, "Slider");
	
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(window.x, window.y, "test");
	SetTargetFPS(60);
	while ( !WindowShouldClose() )
	{	
		if ( IsKeyPressed(KEY_SPACE) )
		{
			showGrid = !showGrid;
		}
		BeginDrawing();
			ClearBackground(BLACK);
			gui.setCellSize(GetScreenWidth() / 10, GetScreenHeight() / 10);
			gui.update();
			if ( showGrid )
			{
				gui.drawCells(DARKGRAY);
			}
			gui.render();
		EndDrawing();
	}
	
	return 0;
}