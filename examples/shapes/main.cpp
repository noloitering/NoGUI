#include "../../src/GUI.h"

Vector2 window = {470, 720};
Vector2 center = {window.x / 2, window.y / 2};
int spacing = 100;
int fps = 60;

int main(int argc, char ** argv)
{
	InitWindow(window.x, window.y, "Shapes");
	SetTargetFPS(fps);
	
	NoGUI::GUIManager manager = NoGUI::GUIManager();
	NoGUI::CText textStyle = NoGUI::CText();
	textStyle.align = NoGUI::TextAlign::CENTER;
	NoGUI::Style elipseStyle = {BLACK, GRAY, (Vector2){center.x, 60}, (Vector2){75, 35}, 0, 4, 0};
	NoGUI::Style pointStyle = {BLACK, GRAY, (Vector2){center.x, elipseStyle.pos.y + spacing}, (Vector2){75, 35}, 1, 4, 0};
	NoGUI::Style lineStyle = {BLACK, GRAY, (Vector2){center.x, pointStyle.pos.y + spacing}, (Vector2){75, 35}, 2, 4, 0};
	NoGUI::Style triStyle = {BLACK, GRAY, (Vector2){center.x, lineStyle.pos.y + spacing}, (Vector2){75, 35}, 3, 4, 0};
	NoGUI::Style rectStyle = {BLACK, GRAY, (Vector2){center.x, triStyle.pos.y + spacing}, (Vector2){75, 35}, 4, 4, 0};
	NoGUI::Style pentaStyle = {BLACK, GRAY, (Vector2){center.x, rectStyle.pos.y + spacing}, (Vector2){75, 35}, 5, 4, 0};
	NoGUI::Style octaStyle = {BLACK, GRAY, (Vector2){center.x, pentaStyle.pos.y + spacing}, (Vector2){75, 35}, 8, 4, 0};
	
	std::shared_ptr< NoGUI::Page > page = manager.getPage();
	if ( page )
	{
		std::cout << "we have a page!" << std::endl; 
	}
	else
	{
		std::cout << "null page" << std::endl;
	}
	
	std::shared_ptr< NoGUI::Element > elipse = manager.addElement< NoGUI::Element >(elipseStyle, "Shape", "Elipse");
	std::shared_ptr< NoGUI::Element > point = manager.addElement< NoGUI::Element >(pointStyle, "Shape", "Point");
	std::shared_ptr< NoGUI::Element > line = manager.addElement< NoGUI::Element >(lineStyle, "Shape", "Line");
	std::shared_ptr< NoGUI::Element > triangle = manager.addElement< NoGUI::Element >(triStyle, "Shape", "Triangle");
	std::shared_ptr< NoGUI::Element > rectangle = manager.addElement< NoGUI::Element >(rectStyle, "Shape", "Rectangle");
	std::shared_ptr< NoGUI::Element > pentagon = manager.addElement< NoGUI::Element >(pentaStyle, "Shape", "Pentagon");
	std::shared_ptr< NoGUI::Element > octagon = manager.addElement< NoGUI::Element >(octaStyle, "Shape", "Octagon");
	
	elipse->components->addComponent< NoGUI::CText >(textStyle);
	point->components->addComponent< NoGUI::CText >(textStyle);
	line->components->addComponent< NoGUI::CText >(textStyle);
	triangle->components->addComponent< NoGUI::CText >(textStyle);
	rectangle->components->addComponent< NoGUI::CText >(textStyle);
	pentagon->components->addComponent< NoGUI::CText >(textStyle);
	octagon->components->addComponent< NoGUI::CText >(textStyle);
	
	while ( !WindowShouldClose() )
	{
		manager.update();
		BeginDrawing();
			ClearBackground(RAYWHITE);
			manager.render();
		EndDrawing();
	}

	return 0;
}