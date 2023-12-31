#include "../../../src/GUI.h"

#include <iostream>

Vector2 window = {1280, 720};
NoGUI::ManagerGrid gui;

class EventHandler : public NoGUI::Listener
{
	void onNotify(std::shared_ptr< NoGUI::Element > elem, NoGUI::Event event)
	{
		if ( TextIsEqual("PreviewX", elem->getTag()) )
		{
			switch ( event )
			{
				case NoGUI::Event::ONFOCUS:
				{
					// create new Element
					Vector2 mousePos = GetMousePosition();
					Vector2 cellSize = gui.getCellSize();
					// align to mouse position
					Vector2 pos = {mousePos.x / cellSize.x, mousePos.y / cellSize.y};
					NoGUI::Transform transform = NoGUI::Transform(pos, elem->radius);
					std::shared_ptr< NoGUI::Element > newElem = gui.getPage(0)->addElement< NoGUI::Trigger >(elem->getShape(), transform, "SliderX");
					// add slider components
					newElem->components = std::make_shared< NoGUI::CContainer >();
					NoGUI::CMultiShape& slide = newElem->components->addComponent< NoGUI::CMultiShape >();
					NoGUI::Transform newSlidePos = NoGUI::Transform((Vector2){0, 0}, (Vector2){0, newElem->radius.y}, NoGUI::Align(-1, 0));
					slide.shapes.push_back(std::make_pair(elem->components->getComponent< NoGUI::CMultiShape >().shapes.front().first, newSlidePos));
					// dont trigger slider while positioning
					newElem->setActive(false);
					
					break;
				}
				
				case NoGUI::Event::FOCUSING:
				{
					// position new element to mouse position
					Vector2 mousePos = GetMousePosition();
					Vector2 cellSize = gui.getCellSize();
					std::shared_ptr< NoGUI::Element > elemToAdd = gui.getPage(0)->getElements("SliderX").back();
					elemToAdd->repos((Vector2){mousePos.x / cellSize.x, mousePos.y / cellSize.y});
					if ( IsMouseButtonReleased(MOUSE_LEFT_BUTTON) )
					{
						// drop and activate element
						elem->setFocus(false);
						elemToAdd->setActive(true);
					}
					
					break;
				}
				
				// TODO: setFocus does not trigger event
//				case NoGUI::Event::OFFFOCUS:
//				{
//					std::cout << "placing slider" << std::endl;
//					std::shared_ptr< NoGUI::Element > elemToAdd = gui.getPage(0)->getElements("Slider").back();
//					elemToAdd->setActive(true);
//					
//					break;
//				}
				
				default:
				{
					
					break;
				}
			}
		}
		else if ( TextIsEqual("PreviewY", elem->getTag()) )
		{
			switch ( event )
			{
				case NoGUI::Event::ONFOCUS:
				{
					// create new Element
					Vector2 mousePos = GetMousePosition();
					Vector2 cellSize = gui.getCellSize();
					// align to mouse position
					Vector2 pos = {mousePos.x / cellSize.x, mousePos.y / cellSize.y};
					NoGUI::Transform transform = NoGUI::Transform(pos, elem->radius);
					std::shared_ptr< NoGUI::Element > newElem = gui.getPage(0)->addElement< NoGUI::Trigger >(elem->getShape(), transform, "SliderY");
					// add slider components
					newElem->components = std::make_shared< NoGUI::CContainer >();
					NoGUI::CMultiShape& slide = newElem->components->addComponent< NoGUI::CMultiShape >();
					NoGUI::Transform newSlidePos = NoGUI::Transform((Vector2){0, 0}, (Vector2){newElem->radius.x, 0}, NoGUI::Align(0, 1));
					slide.shapes.push_back(std::make_pair(elem->components->getComponent< NoGUI::CMultiShape >().shapes.front().first, newSlidePos));
					// dont trigger slider while positioning
					newElem->setActive(false);
					
					break;
				}
				
				case NoGUI::Event::FOCUSING:
				{
					// position new element to mouse position
					Vector2 mousePos = GetMousePosition();
					Vector2 cellSize = gui.getCellSize();
					std::shared_ptr< NoGUI::Element > elemToAdd = gui.getPage(0)->getElements("SliderY").back();
					elemToAdd->repos((Vector2){mousePos.x / cellSize.x, mousePos.y / cellSize.y});
					if ( IsMouseButtonReleased(MOUSE_LEFT_BUTTON) )
					{
						// drop and activate element
						elem->setFocus(false);
						elemToAdd->setActive(true);
					}
					
					break;
				}
				
				// TODO: setFocus does not trigger event
//				case NoGUI::Event::OFFFOCUS:
//				{
//					std::cout << "placing slider" << std::endl;
//					std::shared_ptr< NoGUI::Element > elemToAdd = gui.getPage(0)->getElements("Slider").back();
//					elemToAdd->setActive(true);
//					
//					break;
//				}
				
				default:
				{
					
					break;
				}
			}
		}
		else if ( TextIsEqual("CPreviewX", elem->getTag()) )
		{
			switch ( event )
			{
				case NoGUI::Event::ONFOCUS:
				{
					// create new Element
					Vector2 mousePos = GetMousePosition();
					Vector2 cellSize = gui.getCellSize();
					// align to mouse position
					Vector2 pos = {mousePos.x / cellSize.x, mousePos.y / cellSize.y};
					NoGUI::Transform transform = NoGUI::Transform(pos, elem->radius);
					std::shared_ptr< NoGUI::Element > newElem = gui.getPage(0)->addElement< NoGUI::Trigger >(elem->getShape(), transform, "CSliderX");
					// add slider components
					newElem->components = std::make_shared< NoGUI::CContainer >();
					NoGUI::CMultiShape& cursor = newElem->components->addComponent< NoGUI::CMultiShape >(true);
					Vector2 cursorRadius = elem->components->getComponent< NoGUI::CMultiShape >().shapes.front().second.radius;
					float cursorY = elem->components->getComponent< NoGUI::CMultiShape >().shapes.front().second.position.y;
					NoGUI::Transform newSlidePos = NoGUI::Transform((Vector2){0, cursorY}, (Vector2){cursorRadius}, NoGUI::Align(-1, 0));
					cursor.shapes.push_back(std::make_pair(elem->components->getComponent< NoGUI::CMultiShape >().shapes.front().first, newSlidePos));
					// dont trigger slider while positioning
					newElem->setActive(false);
					
					break;
				}
				
				case NoGUI::Event::FOCUSING:
				{
					// position new element to mouse position
					Vector2 mousePos = GetMousePosition();
					Vector2 cellSize = gui.getCellSize();
					std::shared_ptr< NoGUI::Element > elemToAdd = gui.getPage(0)->getElements("CSliderX").back();
					elemToAdd->repos((Vector2){mousePos.x / cellSize.x, mousePos.y / cellSize.y});
					if ( IsMouseButtonReleased(MOUSE_LEFT_BUTTON) )
					{
						// drop and activate element
						elem->setFocus(false);
						elemToAdd->setActive(true);
					}
					
					break;
				}
				
				// TODO: setFocus does not trigger event
//				case NoGUI::Event::OFFFOCUS:
//				{
//					std::cout << "placing slider" << std::endl;
//					std::shared_ptr< NoGUI::Element > elemToAdd = gui.getPage(0)->getElements("Slider").back();
//					elemToAdd->setActive(true);
//					
//					break;
//				}
				
				default:
				{
					
					break;
				}
			}
		}
		else if ( TextIsEqual("CPreviewY", elem->getTag()) )
		{
			switch ( event )
			{
				case NoGUI::Event::ONFOCUS:
				{
					// create new Element
					Vector2 mousePos = GetMousePosition();
					Vector2 cellSize = gui.getCellSize();
					// align to mouse position
					Vector2 pos = {mousePos.x / cellSize.x, mousePos.y / cellSize.y};
					NoGUI::Transform transform = NoGUI::Transform(pos, elem->radius, NoGUI::Align(0, 0), 90);
					std::shared_ptr< NoGUI::Element > newElem = gui.getPage(0)->addElement< NoGUI::Trigger >(elem->getShape(), transform, "CSliderY");
					// add slider components
					newElem->components = std::make_shared< NoGUI::CContainer >();
					NoGUI::CMultiShape& cursor = newElem->components->addComponent< NoGUI::CMultiShape >(true);
					Vector2 cursorRadius = elem->components->getComponent< NoGUI::CMultiShape >().shapes.front().second.radius;
//					float cursorY = elem->components->getComponent< NoGUI::CMultiShape >().shapes.front().second.position.y;
					NoGUI::Transform newSlidePos = NoGUI::Transform((Vector2){0, -0.05}, (Vector2){cursorRadius}, NoGUI::Align(1, 0));
					cursor.shapes.push_back(std::make_pair(elem->components->getComponent< NoGUI::CMultiShape >().shapes.front().first, newSlidePos));
					// dont trigger slider while positioning
					newElem->setActive(false);
					
					break;
				}
				
				case NoGUI::Event::FOCUSING:
				{
					// position new element to mouse position
					Vector2 mousePos = GetMousePosition();
					Vector2 cellSize = gui.getCellSize();
					std::shared_ptr< NoGUI::Element > elemToAdd = gui.getPage(0)->getElements("CSliderY").back();
					elemToAdd->repos((Vector2){mousePos.x / cellSize.x, mousePos.y / cellSize.y});
					if ( IsMouseButtonReleased(MOUSE_LEFT_BUTTON) )
					{
						// drop and activate element
						elem->setFocus(false);
						elemToAdd->setActive(true);
					}
					
					break;
				}
				
				// TODO: setFocus does not trigger event
//				case NoGUI::Event::OFFFOCUS:
//				{
//					std::cout << "placing slider" << std::endl;
//					std::shared_ptr< NoGUI::Element > elemToAdd = gui.getPage(0)->getElements("Slider").back();
//					elemToAdd->setActive(true);
//					
//					break;
//				}
				
				default:
				{
					
					break;
				}
			}
		}
		else if ( TextIsEqual("SliderX", elem->getTag()) )
		{
			if ( event == NoGUI::Event::FOCUSING )
			{
				// resize slider
				NoGUI::CMultiShape& sliderShapes = elem->components->getComponent< NoGUI::CMultiShape >();
				Vector2 mousePos = GetMousePosition();
				Vector2 cellSize = gui.getCellSize();
				Vector2 slideRadius = {(mousePos.x / cellSize.x - elem->pos(NoGUI::Align(-1, 0)).x) / 2, sliderShapes.shapes.front().second.radius.y};
				sliderShapes.shapes.front().second.resize(slideRadius);
				// reposition slider since multishapes have a center origin
				sliderShapes.shapes.front().second.repos((Vector2){slideRadius.x, sliderShapes.shapes.front().second.position.y});
			}
		}
		else if ( TextIsEqual("SliderY", elem->getTag()) )
		{
			if ( event == NoGUI::Event::FOCUSING )
			{
				// resize slider
				NoGUI::CMultiShape& sliderShapes = elem->components->getComponent< NoGUI::CMultiShape >();
				Vector2 mousePos = GetMousePosition();
				Vector2 cellSize = gui.getCellSize();
				Vector2 slideRadius = {sliderShapes.shapes.front().second.radius.x, (elem->pos(NoGUI::Align(0, 1)).y - mousePos.y / cellSize.y) / 2};
				sliderShapes.shapes.front().second.resize(slideRadius);
				// reposition slider since multishapes have a center origin
				sliderShapes.shapes.front().second.repos((Vector2){sliderShapes.shapes.front().second.position.x, slideRadius.y * -1});
			}
		}
		else if ( TextIsEqual("CSliderX", elem->getTag()) )
		{
			if ( event == NoGUI::Event::FOCUSING )
			{
				// resize slider
				NoGUI::CMultiShape& cursorShapes = elem->components->getComponent< NoGUI::CMultiShape >();
				Vector2 mousePos = GetMousePosition();
				Vector2 cellSize = gui.getCellSize();
				Vector2 cursorPos = {mousePos.x / cellSize.x - elem->pos(NoGUI::Align(-1, 0)).x, cursorShapes.shapes.front().second.position.y};
				if ( cursorPos.x < elem->width() && cursorPos.x > 0 )
				{
					cursorShapes.shapes.front().second.repos(cursorPos);
				}
			}
		}
		else if ( TextIsEqual("CSliderY", elem->getTag()) )
		{
			if ( event == NoGUI::Event::FOCUSING )
			{
				// resize slider
				NoGUI::CMultiShape& cursorShapes = elem->components->getComponent< NoGUI::CMultiShape >();
				Vector2 mousePos = GetMousePosition();
				Vector2 cellSize = gui.getCellSize();
				// TODO: transform.pos() does not work at an angle on the grid. The commented out code should work
//				Vector2 minPos = elem->pos(NoGUI::Align(1, 0));
//				Vector2 cursorPos = {mousePos.y / cellSize.y - minPos.y, cursorShapes.shapes.front().second.position.y};
				Vector2 center = Vector2Multiply(elem->pos(NoGUI::Align()), gui.getCellSize());
				Vector2 offset = {elem->radius.x * cellSize.x, 0};
				Vector2 minPos = Vector2Add(center, Vector2Rotate(offset, elem->angle * DEG2RAD));
				Vector2 cursorPos = {(mousePos.y - minPos.y) / cellSize.y, cursorShapes.shapes.front().second.position.y};
				cursorPos.x *= (cellSize.y / cellSize.x);
				if ( cursorPos.x > elem->width() * -1 && cursorPos.x < 0 )
				{
					cursorShapes.shapes.front().second.repos(cursorPos);
				}
			}
		}
	}
};

int main(int argc, char ** argv)
{
	bool showGrid = false; // grid toggle on space press
	if ( argc > 2 )
	{
		window.x = TextToInteger(argv[1]);
		window.y = TextToInteger(argv[2]);
	}
	gui = NoGUI::ManagerGrid(true, window.x / 10, window.y / 10);
	std::shared_ptr< EventHandler > eventHandler = std::make_shared< EventHandler >();
	gui.addListener(eventHandler);
	
	std::shared_ptr< NoGUI::Fill > fill = std::make_shared< NoGUI::Fill >((Color){100, 100, 100, 100});
	std::shared_ptr< NoGUI::Fill > noFill = std::make_shared< NoGUI::Fill >(BLANK);
	std::shared_ptr< NoGUI::Fill > slideFill = std::make_shared< NoGUI::Fill >(LIME);
	std::shared_ptr< NoGUI::Fill > outlineFill = std::make_shared< NoGUI::Fill >(GRAY);
	std::shared_ptr< NoGUI::Fill > cursorFill = std::make_shared< NoGUI::Fill >(BLUE);
	std::shared_ptr< NoGUI::Fill > textFill = std::make_shared< NoGUI::Fill >();
	
	std::shared_ptr< NoGUI::Outline > outline = std::make_shared< NoGUI::Outline >(outlineFill, 2);
	
	std::shared_ptr< NoGUI::nShape > UIRect = std::make_shared< NoGUI::nShape >(4, fill);
	std::shared_ptr< NoGUI::nShape > slider = std::make_shared< NoGUI::nShape >(4, noFill, outline);
	std::shared_ptr< NoGUI::nShape > labelRect = std::make_shared< NoGUI::nShape >(4, noFill);
	std::shared_ptr< NoGUI::nShape > slide = std::make_shared< NoGUI::nShape >(4, slideFill);
	std::shared_ptr< NoGUI::nShape > line = std::make_shared< NoGUI::nShape >(2, outlineFill);
	std::shared_ptr< NoGUI::nShape > triangle = std::make_shared< NoGUI::nShape >(3, cursorFill);
	
	NoGUI::Transform leftPos = NoGUI::Transform((Vector2){0, 5}, (Vector2){1, 6}, NoGUI::Align(-1, 0));
	NoGUI::Transform topLeftPos = NoGUI::Transform((Vector2){2, 0}, (Vector2){1, 0.5}, NoGUI::Align(-1, -1));
	NoGUI::Transform xSliderPos = NoGUI::Transform((Vector2){0.25, 1}, (Vector2){0.75, 0.5}, NoGUI::Align(-1, -1));
	NoGUI::Transform xSlidePos = NoGUI::Transform((Vector2){0.1, 0}, (Vector2){0.1, 0.5}, NoGUI::Align(-1, 0));
	NoGUI::Transform ySliderPos = NoGUI::Transform((Vector2){1, 3}, (Vector2){0.3, 1.3}, NoGUI::Align(0, -1));
//	NoGUI::Transform ySliderPos = NoGUI::Transform((Vector2){1.25, 3}, (Vector2){0.75, 0.5}, NoGUI::Align(-1, -1), 90);
	NoGUI::Transform ySlidePos = NoGUI::Transform((Vector2){0, -0.2}, (Vector2){0.3, 0.2}, NoGUI::Align(0, 1));
	NoGUI::Transform xCursorerPos = NoGUI::Transform((Vector2){0.25, 7}, (Vector2){0.75, 0.1}, NoGUI::Align(-1, -1));
	NoGUI::Transform xCursorPos = NoGUI::Transform((Vector2){0, -0.05}, (Vector2){0.1, 0.2});
	NoGUI::Transform yCursorerPos = NoGUI::Transform((Vector2){1, 8}, (Vector2){0.75, 0.1}, NoGUI::Align(-1, -1), 90);
//	NoGUI::Transform yCursorerPos = NoGUI::Transform((Vector2){1, 8}, (Vector2){1, 0.06}, NoGUI::Align(-1, -1), 90);
	NoGUI::Transform yCursorPos = NoGUI::Transform((Vector2){0, -0.1}, (Vector2){0.1, 0.2});
	
	std::shared_ptr< NoGUI::CContainer > labelCContainer = gui.getPage(0)->addComponents("Label");
	labelCContainer->addComponent< NoGUI::CText >(textFill, nullptr, 32, NoGUI::Align(-1, -1));
	std::shared_ptr< NoGUI::CContainer > slideXCContainer = gui.getPage(0)->addComponents("PreviewX");
	NoGUI::CMultiShape& slideXComp = slideXCContainer->addComponent< NoGUI::CMultiShape >();
	slideXComp.shapes.push_back(std::make_pair(slide, xSlidePos));
	std::shared_ptr< NoGUI::CContainer > slideYCContainer = gui.getPage(0)->addComponents("PreviewY");
	NoGUI::CMultiShape& slideYComp = slideYCContainer->addComponent< NoGUI::CMultiShape >();
	slideYComp.shapes.push_back(std::make_pair(slide, ySlidePos));
	std::shared_ptr< NoGUI::CContainer > cursorXCContainer = gui.getPage(0)->addComponents("CPreviewX");
	NoGUI::CMultiShape& cursorXComp = cursorXCContainer->addComponent< NoGUI::CMultiShape >(true);
	cursorXComp.shapes.push_back(std::make_pair(triangle, xCursorPos));
	std::shared_ptr< NoGUI::CContainer > cursorYCContainer = gui.getPage(0)->addComponents("CPreviewY");
	NoGUI::CMultiShape& cursorYComp = cursorYCContainer->addComponent< NoGUI::CMultiShape >(true);
	cursorYComp.shapes.push_back(std::make_pair(triangle, yCursorPos));
	
	std::shared_ptr< NoGUI::Element > resLabel = gui.getPage(0)->addElement(labelRect, topLeftPos, "Label");
	std::shared_ptr< NoGUI::Element > previewContainer = gui.getPage(0)->addElement(UIRect, leftPos, "Container");
	std::shared_ptr< NoGUI::Element > xSliderPreview = gui.getPage(0)->addElement< NoGUI::Toggle >(slider, xSliderPos, "PreviewX");
	std::shared_ptr< NoGUI::Element > ySliderPreview = gui.getPage(0)->addElement< NoGUI::Toggle >(slider, ySliderPos, "PreviewY");
	std::shared_ptr< NoGUI::Element > xCursorerPreview = gui.getPage(0)->addElement< NoGUI::Toggle >(line, xCursorerPos, "CPreviewX");
	std::shared_ptr< NoGUI::Element > yCursorerPreview = gui.getPage(0)->addElement< NoGUI::Toggle >(line, yCursorerPos, "CPreviewY");
	
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
			int cellSizeX = gui.getCellSize().x;
			int cellSizeY = gui.getCellSize().y;
			resLabel->setInner(TextFormat("%i, %i\nCell Size: %i, %i", GetScreenWidth(), GetScreenHeight(), cellSizeX, cellSizeY));
			if ( showGrid )
			{
				gui.drawCells(DARKGRAY);
			}
			// if ( gui.getPage(0)->getElements("CSliderX").size() )
			// {
				// std::shared_ptr< NoGUI::Element > elem = gui.getPage(0)->getElements("CSliderX").front();
				// elem->angle -= GetMouseWheelMove();

				// DrawCircleV(Vector2Multiply(Vector2Subtract(elem->pos(), elem->offset()), gui.getCellSize()), 7, RED);				
				// DrawCircleV(Vector2Multiply(elem->pos(NoGUI::Align(-1, 0)), gui.getCellSize()), 7, WHITE);
				// DrawCircleV(Vector2Multiply(elem->pos(NoGUI::Align(1, 0)), gui.getCellSize()), 7, WHITE);
			// }
			gui.render();
		EndDrawing();
	}
	
	return 0;
}