#include "../../../src/GUI.h"

Vector2 window = {1280, 720};
enum class TransformState {IDLE, REPOSITION, SCALEX, SCALEY, SCALEXY, ROTATE};

void DrawGrid(int cellSize, Rectangle area)
{
	for (int x=area.x; x < (area.x + area.width); x+=cellSize)
	{
		DrawLine(x, area.y, x, area.y + area.height, GRAY);
	}
	for (int y=0; y < (area.y + area.height); y+=cellSize)
	{
		DrawLine(area.x, y, area.x + area.width, y, GRAY);
	}
}

void SnapToGrid(int cellSize, NoGUI::Transform& transform)
{
	transform.position.x = (int)transform.position.x;
	transform.position.y = (int)transform.position.y;
	float remX = (int)transform.position.x % cellSize;
	float remY = (int)transform.position.y % cellSize;
	switch (transform.origin.x)
	{
		case NoGUI::XAlign::LEFT:
		{
			if ( remX != 0 )
			{
				transform.position.x -= remX;
			}
			
			break;
		}
		
		case NoGUI::XAlign::CENTER:
		{
			if ( remX != 0 )
			{
				transform.position.x -= remX;
			}
			
			break;
		}
		
		case NoGUI::XAlign::RIGHT:
		{
			if ( remX != 0 )
			{
				transform.position.x += remX;
			}
			
			break;
		}
	}
	switch (transform.origin.y)
	{
		case NoGUI::YAlign::TOP:
		{
			if ( remY != 0 )
			{
				transform.position.y -= remY;
			}
			
			break;
		}
		
		case NoGUI::YAlign::CENTER:
		{
			if ( remY != 0 )
			{
				transform.position.y -= remY;
			}
			
			break;
		}
		
		case NoGUI::YAlign::BOTTOM:
		{
			if ( remY != 0 )
			{
				transform.position.y += remY;
			}
			
			break;
		}
	}
}

void DrawHandles(const NoGUI::Transform& transform)
{
	float circRadius = 6;
	Color handlesCol = BLUE;
	DrawCircleV(transform.pos(NoGUI::Align(-1, -1)), circRadius, handlesCol);
	DrawCircleV(transform.pos(NoGUI::Align(-1, 0)), circRadius, handlesCol);
	DrawCircleV(transform.pos(NoGUI::Align(-1, 1)), circRadius, handlesCol);
	DrawCircleV(transform.pos(NoGUI::Align(0, 1)), circRadius, handlesCol);
	DrawCircleV(transform.pos(NoGUI::Align(1, 1)), circRadius, handlesCol);
	DrawCircleV(transform.pos(NoGUI::Align(1, 0)), circRadius, handlesCol);
	DrawCircleV(transform.pos(NoGUI::Align(1, -1)), circRadius, handlesCol);
	DrawCircleV(transform.pos(NoGUI::Align(0, -1)), circRadius, handlesCol);
}

Vector2 GetHandlesCollision(Vector2 point, const NoGUI::Transform& transform)
{
	float circRadius = 9;
	if ( CheckCollisionPointCircle(point, transform.pos(NoGUI::Align(-1, -1)), circRadius) )
	{
		
		return (Vector2){-transform.radius.x, -transform.radius.y};
	}
	else if ( CheckCollisionPointCircle(point, transform.pos(NoGUI::Align(-1, 0)), circRadius) )
	{
		
		return (Vector2){-transform.radius.x, 0.0f};
	}
	else if ( CheckCollisionPointCircle(point, transform.pos(NoGUI::Align(-1, 1)), circRadius) )
	{
		
		return (Vector2){-transform.radius.x, transform.radius.y};;
	}
	else if ( CheckCollisionPointCircle(point, transform.pos(NoGUI::Align(0, 1)), circRadius) )
	{
		
		return (Vector2){0, transform.radius.y};
	}
	else if ( CheckCollisionPointCircle(point, transform.pos(NoGUI::Align(1, 1)), circRadius) )
	{
		
		return (Vector2){transform.radius.x, transform.radius.y};
	}
	else if ( CheckCollisionPointCircle(point, transform.pos(NoGUI::Align(1, 0)), circRadius) )
	{
		
		return (Vector2){transform.radius.x, 0.0f};
	}
	else if ( CheckCollisionPointCircle(point, transform.pos(NoGUI::Align(1, -1)), circRadius) )
	{
		
		return (Vector2){transform.radius.x, -transform.radius.y};;
	}
	else if ( CheckCollisionPointCircle(point, transform.pos(NoGUI::Align(0, -1)), circRadius) )
	{
		
		return (Vector2){0.0f, -transform.radius.y};
	}
	
	
	return (Vector2){0.0f, 0.0f};
}

bool CheckCollisionPointRotationCircle(Vector2 point, const NoGUI::Transform& transform)
{
	bool collision = false;
	Vector2 centerPos = transform.pos(NoGUI::Align(0, 0));
	// create ring around element based on its radius
	float innerRadius = (transform.radius.x > transform.radius.y) ? transform.radius.x * 2 : transform.radius.y * 2;
	float outerRadius = (transform.radius.x > transform.radius.y) ? transform.radius.x * 3 : transform.radius.y * 3;
	if ( !CheckCollisionPointCircle(point, centerPos, innerRadius) && CheckCollisionPointCircle(point, centerPos, outerRadius) )
	{
		collision = true;
	}
	
	return collision;
}

void onPropertyPress(std::shared_ptr< NoGUI::Page > properties, std::shared_ptr< NoGUI::Page > colpg, std::shared_ptr< NoGUI::Page > shapepg, std::shared_ptr< NoGUI::Page > elempg)
{
	// TODO: simplify this
	std::vector< std::shared_ptr< NoGUI::Element > > propertyToggles = properties->getElements("Tab");
	std::shared_ptr< NoGUI::Element > coloursButton = nullptr;
	std::shared_ptr< NoGUI::Element > shapesButton = nullptr;
	std::shared_ptr< NoGUI::Element > elementsButton = nullptr;
	for (auto elem : propertyToggles)
	{
		if ( TextIsEqual(elem->getInner(), "Colours") )
		{
			coloursButton = elem;
		}
		else if ( TextIsEqual(elem->getInner(), "Shapes") )
		{
			shapesButton = elem;
		}
		else if ( TextIsEqual(elem->getInner(), "Elements") )
		{
			elementsButton = elem;
		}
	}
	std::shared_ptr< NoGUI::Element > addCol = colpg->getElements("Add").front();
	std::shared_ptr< NoGUI::Element > addShape = shapepg->getElements("Add").front();
	std::shared_ptr< NoGUI::Element > addElem = elempg->getElements("Add").front();
	if ( coloursButton->getFocus() )
	{
		// display user colours
		colpg->setEnabled(true);
		// position buttons
		if ( shapesButton->getFocus() || elementsButton->getFocus() )
		{
			shapesButton->position.y = addCol->pos(NoGUI::Align(0, 1)).y + addCol->getShape()->outline->thick + shapesButton->getShape()->outline->thick;
		}
		else
		{
			shapesButton->position.y = window.y - (shapesButton->height() + shapesButton->getShape()->outline->thick) * (propertyToggles.size() - (shapesButton->getId() - coloursButton->getId()));
		}
	}
	else
	{
		colpg->setEnabled(false);
		shapesButton->position.y = coloursButton->pos(NoGUI::Align(0, 1)).y + coloursButton->getShape()->outline->thick;
	}
	if ( shapesButton->getFocus() )
	{
		// display user shapes
		shapepg->setEnabled(true);
		// position info
		std::vector< std::shared_ptr< NoGUI::Element > > previews = shapepg->getElements("Shape");
		std::vector< std::shared_ptr< NoGUI::Element > > containers = shapepg->getElements("Container");
		std::vector< std::shared_ptr< NoGUI::Element > > labels = shapepg->getElements("Label");
		std::vector< std::shared_ptr< NoGUI::Element > > inputs = shapepg->getElements("Input");
		std::vector< std::shared_ptr< NoGUI::Element > > colours = shapepg->getElements("DropDown");
		std::vector< std::shared_ptr< NoGUI::Element > > names = shapepg->getElements("Name");
		Vector2 startPos = {addCol->pos(NoGUI::Align(-1, 0)).x, shapesButton->pos(NoGUI::Align(0, 1)).y + 8 };
		addShape->repos((Vector2){startPos.x, startPos.y + containers.size() * (addShape->height() + 4)});
		for (size_t i=0; i < previews.size(); i++)
		{
			containers.at(i)->repos((Vector2){startPos.x, startPos.y + (containers.at(i)->height() + 4) *i});
			previews.at(i)->repos(containers.at(i)->pos(NoGUI::Align(0, 0)));		
		}
		for (auto name : names)
		{
			std::shared_ptr< NoGUI::Element > container;
			for (auto container : containers)
			{
				if ( TextToInteger(container->getInner()) == (int)name->getId() )
				{
					name->repos((Vector2){name->position.x, container->pos(NoGUI::Align(0, 0)).y});
				}
			}
		}
		for (size_t i=0; i < labels.size(); i++)
		{
			std::shared_ptr< NoGUI::Element > label = labels.at(i);
			std::shared_ptr< NoGUI::Element > input = inputs.at(i);
			std::shared_ptr< NoGUI::Element > colour = colours.at(i);
			std::shared_ptr< NoGUI::Element > container;
			if ( i % 2 == 0 )
			{
				container = shapepg->getElement(label->getId() + 6);
			}
			else
			{
				container = shapepg->getElement(label->getId() + 3);
			}
			label->repos((Vector2){label->position.x, container->pos(label->origin).y});
			input->repos((Vector2){label->pos(NoGUI::Align(1, -1)).x, label->pos(input->origin).y});
			colour->repos((Vector2){colours.at(i)->position.x, input->pos(colour->origin).y});
		}
		if ( elementsButton->getFocus() )
		{
			elementsButton->position.y = (addShape->pos(NoGUI::Align(0, 1)).y + shapesButton->getShape()->outline->thick * 2);
		}
	}
	else
	{
		shapepg->setEnabled(false);
		if ( !coloursButton->getFocus() || (coloursButton->getFocus() && elementsButton->getFocus()) )
		{
			elementsButton->position.y = shapesButton->pos(NoGUI::Align(0, 1)).y + shapesButton->getShape()->outline->thick;
		}
	}
	if ( elementsButton->getFocus() )
	{
		// display user elements
		elempg->setEnabled(true);
		// position info
		std::vector< std::shared_ptr< NoGUI::Element > > labels = elempg->getElements("Label");
		std::vector< std::shared_ptr< NoGUI::Element > > shapes = elempg->getElements("DropDown");
		std::vector< std::shared_ptr< NoGUI::Element > > inputs = elempg->getElements("Input");
		std::vector< std::shared_ptr< NoGUI::Element > > containers = elempg->getElements("Container");
		std::vector< std::shared_ptr< NoGUI::Element > > previews = elempg->getElements("Preview");
		std::vector< std::shared_ptr< NoGUI::Element > > values = elempg->getElements("Value");
		float containerY = elementsButton->pos(NoGUI::Align(0, 1)).y + 8;
		float labelY = elementsButton->pos(NoGUI::Align(0, -1)).y + 4 - labels.front()->height();
		
		for (size_t i=0; i < values.size(); i++)
		{
			values.at(i)->repos((Vector2){values.at(i)->position.x, containerY + values.at(i)->height() + 2});
			if ( i % 2 == 0 )
			{
				std::shared_ptr< NoGUI::Element > container = containers.at(i / 2);
				std::shared_ptr< NoGUI::Element > preview = previews.at(i / 2);
				container->repos((Vector2){container->position.x, containerY});
				preview->repos((Vector2){preview->position.x, container->pos(NoGUI::Align(0, 0)).y});
			}
			else
			{
				labelY += containers.at(i / 2)->height() + 4;
				containerY += containers.at(i / 2)->height() + 4;
			}
		}
		Vector2 inputPos = {window.x - 300, labelY + labels.front()->height()};
		for (size_t i=0; i < labels.size(); i++)
		{
			if ( i % 3 == 0 )
			{
				labelY += labels.at(i)->height() * 2;
			}
			labels.at(i)->repos((Vector2){labels.at(i)->position.x, labelY});
		}
		for (size_t i=0; i < shapes.size(); i++)
		{
			shapes.at(i)->repos((Vector2){inputPos.x, inputPos.y + shapes.at(i)->height() * (i + 2)});
		}
		for (size_t i=0; i < inputs.size(); i++)
		{
			if ( i % 2 == 0 )
			{
				inputPos.x = window.x - inputs.at(i)->width() * 2;
				inputPos.y += inputs.at(i)->height() * 2;
			}
			inputs.at(i)->repos(inputPos);
			inputPos.x += inputs.at(i)->width();
		}
		addElem->repos((Vector2){window.x - 150, inputPos.y + labels.front()->height() + 8});
	}
	else
	{
		elempg->setEnabled(false);
		if ( shapesButton->getFocus() || coloursButton->getFocus() )
		{
			elementsButton->position.y = window.y - (elementsButton->height() + elementsButton->getShape()->outline->thick) * (propertyToggles.size() - (elementsButton->getId() - coloursButton->getId()));
		}
	}
}

int main(int argc, char ** argv)
{
	Vector2 labelRadius = {100, 25};
	Vector2 propertyButtonRadius = {100, 12};
	Vector2 shapeLabelRadius = {50, 15};
	int cellSize = 16;
	size_t currPage = 0;
	size_t colCounter = 0;
	size_t colIndex = 0;
	size_t shapeCounter = 0;
	size_t shapeIndex = 0;
	TransformState action = TransformState::IDLE;
	if ( argc > 1 )
	{
		cellSize = TextToInteger(argv[1]);
	}
	Rectangle screenSpace = {0, 0, window.x, window.y};
	std::vector< std::shared_ptr< NoGUI::Fill > > userCols;
	std::vector< std::shared_ptr< NoGUI::nShape > > userShapes;
	
	// UI Colours
	std::shared_ptr< NoGUI::Fill > noFill = std::make_shared< NoGUI::Fill >(BLANK);
	std::shared_ptr< NoGUI::Fill > textFill = std::make_shared< NoGUI::Fill >(WHITE);
	std::shared_ptr< NoGUI::Fill > containerGray = std::make_shared< NoGUI::Fill >((Color){100, 100, 100, 200});
	std::shared_ptr< NoGUI::Fill > innerGray = std::make_shared< NoGUI::Fill >(GRAY, DARKGRAY);
	std::shared_ptr< NoGUI::Fill > outlineRed = std::make_shared< NoGUI::Fill >(MAROON);
	std::shared_ptr< NoGUI::Fill > outlineBlack = std::make_shared< NoGUI::Fill >(BLACK);
	std::shared_ptr< NoGUI::Fill > colourGreen = std::make_shared< NoGUI::Fill >(LIME, DARKGREEN);
	std::shared_ptr< NoGUI::Fill > shapeBlue = std::make_shared< NoGUI::Fill >(SKYBLUE, DARKBLUE);
	std::shared_ptr< NoGUI::Fill > elementYellow = std::make_shared< NoGUI::Fill >(GOLD, ORANGE);
	// UI Outlines
	std::shared_ptr< NoGUI::Outline > UIOutline = std::make_shared< NoGUI::Outline >(outlineRed, 4);
	std::shared_ptr< NoGUI::Outline > pageButtonOutline = std::make_shared< NoGUI::Outline >(containerGray, 2);
	std::shared_ptr< NoGUI::Outline > pageSelectOutline = std::make_shared< NoGUI::Outline >(containerGray, 4);
	std::shared_ptr< NoGUI::Outline > colourOutline = std::make_shared< NoGUI::Outline >(colourGreen, 4, NoGUI::Wrap::DOWN);
	std::shared_ptr< NoGUI::Outline > shapeOutline = std::make_shared< NoGUI::Outline >(shapeBlue, 4, NoGUI::Wrap::DOWN);
	std::shared_ptr< NoGUI::Outline > elementOutline = std::make_shared< NoGUI::Outline >(elementYellow, 4, NoGUI::Wrap::DOWN);
	std::shared_ptr< NoGUI::Outline > propertyOutline = std::make_shared< NoGUI::Outline >(outlineBlack, 1);
	// UI Shapes
	std::shared_ptr< NoGUI::nShape > UIRect = std::make_shared< NoGUI::nShape >(4, containerGray, UIOutline);
	std::shared_ptr< NoGUI::nShape > pageRect = std::make_shared< NoGUI::nShape >(4, innerGray, pageButtonOutline);
	std::shared_ptr< NoGUI::nShape > pageRectSelect = std::make_shared< NoGUI::nShape >(4, innerGray, pageSelectOutline);
	std::shared_ptr< NoGUI::nShape > labelShape = std::make_shared< NoGUI::nShape >(4, noFill);
	std::shared_ptr< NoGUI::nShape > colourShape = std::make_shared< NoGUI::nShape >(4, containerGray, colourOutline);
	std::shared_ptr< NoGUI::nShape > shapeShape = std::make_shared< NoGUI::nShape >(4, containerGray, shapeOutline);
	std::shared_ptr< NoGUI::nShape > elementShape = std::make_shared< NoGUI::nShape >(4, containerGray, elementOutline);
	std::shared_ptr< NoGUI::nShape > propertyRect = std::make_shared< NoGUI::nShape >(4, containerGray, propertyOutline);
	// UI Transforms
	NoGUI::Transform pagesPos = NoGUI::Transform((Vector2){-200, 0}, (Vector2){100, window.y / 2}, NoGUI::Align(-1, -1));
	NoGUI::Transform pagesTogglePos = NoGUI::Transform((Vector2){pagesPos.pos(NoGUI::Align(1, 0)).x, pagesPos.pos(NoGUI::Align(1, 0)).y}, (Vector2){25, 50}, NoGUI::Align(-1, 0));
	NoGUI::Transform initialPagePos = NoGUI::Transform((Vector2){pagesPos.pos(NoGUI::Align(0, 0)).x, 20}, (Vector2){64, 64}, NoGUI::Align(0, -1));
	NoGUI::Transform pageLabelPos = NoGUI::Transform(initialPagePos.pos(NoGUI::Align(0, 1)), labelRadius, NoGUI::Align(0, -1));
	NoGUI::Transform addPagePos = NoGUI::Transform((Vector2){pageLabelPos.pos().x, pageLabelPos.pos(NoGUI::Align(0, 1)).y}, (Vector2){64, 64}, NoGUI::Align(0, -1));
	NoGUI::Transform colourButtonPos = NoGUI::Transform((Vector2){window.x, 0}, propertyButtonRadius, NoGUI::Align(1, -1));
	NoGUI::Transform shapeButtonPos = NoGUI::Transform((Vector2){window.x, colourButtonPos.height() + colourOutline->thick}, propertyButtonRadius, NoGUI::Align(1, -1));
	NoGUI::Transform elementButtonPos = NoGUI::Transform(shapeButtonPos.pos(NoGUI::Align(1, 1)), propertyButtonRadius, NoGUI::Align(1, -1));
	elementButtonPos.translate(0, shapeOutline->thick); // wrap functionality not implemented yet
	NoGUI::Transform propertyPos = NoGUI::Transform((Vector2){window.x, 0}, (Vector2){propertyButtonRadius.x, window.y}, NoGUI::Align(1, 1));
	NoGUI::Transform colPos = NoGUI::Transform((Vector2){colourButtonPos.position.x - 8, colourButtonPos.pos(NoGUI::Align(0, 1)).y + 24 + propertyButtonRadius.y * 2}, (Vector2){propertyButtonRadius.x * 1.5f - 8, propertyButtonRadius.y + 4}, NoGUI::Align(1, -1));
	NoGUI::Transform colRLabelPos = NoGUI::Transform((Vector2){propertyPos.pos(NoGUI::Align(-1, 0)).x - propertyButtonRadius.x + 20, colourButtonPos.pos(NoGUI::Align(0, 1)).y + 8}, (Vector2){12, colPos.radius.y}, NoGUI::Align(-1, -1));
	NoGUI::Transform colRPos = NoGUI::Transform((Vector2){colRLabelPos.pos(NoGUI::Align(1, 0)).x, colRLabelPos.pos().y}, (Vector2){20, colPos.radius.y}, NoGUI::Align(-1, -1));
	NoGUI::Transform colGLabelPos = NoGUI::Transform((Vector2){colRPos.pos(NoGUI::Align(1, 0)).x, colRLabelPos.pos().y}, (Vector2){12, colPos.radius.y}, NoGUI::Align(-1, -1));
	NoGUI::Transform colGPos = NoGUI::Transform((Vector2){colGLabelPos.pos(NoGUI::Align(1, 0)).x, colRLabelPos.pos().y}, (Vector2){20, colPos.radius.y}, NoGUI::Align(-1, -1));
	NoGUI::Transform colBLabelPos = NoGUI::Transform((Vector2){colGPos.pos(NoGUI::Align(1, 0)).x, colRLabelPos.pos().y}, (Vector2){12, colPos.radius.y}, NoGUI::Align(-1, -1));
	NoGUI::Transform colBPos = NoGUI::Transform((Vector2){colBLabelPos.pos(NoGUI::Align(1, 0)).x, colRLabelPos.pos().y}, (Vector2){20, colPos.radius.y}, NoGUI::Align(-1, -1));
	NoGUI::Transform colALabelPos = NoGUI::Transform((Vector2){colBPos.pos(NoGUI::Align(1, 0)).x, colRLabelPos.pos().y}, (Vector2){12, colPos.radius.y}, NoGUI::Align(-1, -1));
	NoGUI::Transform colAPos = NoGUI::Transform((Vector2){colALabelPos.pos(NoGUI::Align(1, 0)).x, colRLabelPos.pos().y}, (Vector2){20, colPos.radius.y}, NoGUI::Align(-1, -1));
	NoGUI::Transform shapePos = NoGUI::Transform((Vector2){colRLabelPos.position.x - 12, colPos.pos(NoGUI::Align(0, 1)).y + shapeButtonPos.height()}, (Vector2){30, colPos.radius.y * 2}, NoGUI::Align(-1, -1));
	NoGUI::Transform elemShapePos = NoGUI::Transform((Vector2){colRLabelPos.position.x, shapePos.pos(NoGUI::Align(0, 1)).y + elementButtonPos.height()}, shapeLabelRadius, NoGUI::Align(-1, -1));
	NoGUI::Transform elemTagPos = NoGUI::Transform((Vector2){elemShapePos.position.x + elemShapePos.width(), elemShapePos.position.y}, elemShapePos.radius, elemShapePos.origin);
	NoGUI::Transform elemInnerPos = NoGUI::Transform((Vector2){elemTagPos.position.x + elemTagPos.width(), elemTagPos.position.y}, elemTagPos.radius, elemTagPos.origin);
	NoGUI::Transform addElemPos = NoGUI::Transform(colPos.position, shapePos.radius, NoGUI::Align(0, -1));
	
	NoGUI::Manager gui = NoGUI::Manager(false);
	NoGUI::Manager userGUI = NoGUI::Manager(true);
	// page manager
	std::shared_ptr< NoGUI::Page > pagepg = gui.addPage(true);
	std::shared_ptr< NoGUI::CContainer > pageToggleComps = pagepg->addComponents("Button");
	std::shared_ptr< NoGUI::CContainer > pageLabelComps = pagepg->addComponents("Label");
	std::shared_ptr< NoGUI::CContainer > pageComps = pagepg->addComponents("Page");
	pageToggleComps->addComponent< NoGUI::CText >(outlineRed, nullptr, 20, NoGUI::Align(), NoGUI::Wrap::DOWN, 90.0f);
	pageLabelComps->addComponent< NoGUI::CText >(textFill);
	pageComps->addComponent< NoGUI::CText >(textFill, nullptr, 40);
	std::shared_ptr< NoGUI::Element > pageContainer = pagepg->addElement(UIRect, pagesPos, "Container");
	std::shared_ptr< NoGUI::Element > pagesToggle = pagepg->addElement(UIRect, pagesTogglePos, "Button", "Pages");
	std::shared_ptr< NoGUI::Element > initialPage = pagepg->addElement(pageRectSelect, initialPagePos, "Page", "0");
	std::shared_ptr< NoGUI::Element > initialPageLabel = pagepg->addElement(labelShape, pageLabelPos, "Label", "Page 0");
	std::shared_ptr< NoGUI::Element > addPage = pagepg->addElement(pageRect, addPagePos, "Page", "+");
	// editor buttons
	std::shared_ptr< NoGUI::Page > builderpg = gui.addPage(true);
	std::shared_ptr< NoGUI::CContainer > builderToggleComps = builderpg->addComponents("Tab");
	builderToggleComps->addComponent< NoGUI::CText >(textFill);
	std::shared_ptr< NoGUI::Element > coloursContainer = builderpg->addElement(propertyRect, propertyPos, "Colours");
	std::shared_ptr< NoGUI::Element > coloursButton = builderpg->addElement(colourShape, colourButtonPos, "Tab", "Colours");
	std::shared_ptr< NoGUI::Element > shapesButton = builderpg->addElement(shapeShape, shapeButtonPos, "Tab", "Shapes");
	std::shared_ptr< NoGUI::Element > elementsButton = builderpg->addElement(elementShape, elementButtonPos, "Tab", "Elements");
	// colours editor
	std::shared_ptr< NoGUI::Page > colpg = gui.addPage(false);
	std::shared_ptr< NoGUI::CContainer > addColComps = colpg->addComponents("Add");
	std::shared_ptr< NoGUI::CContainer > colLabelComps = colpg->addComponents("Label");
	std::shared_ptr< NoGUI::CContainer > colInputComps = colpg->addComponents("Input");
	std::shared_ptr< NoGUI::CContainer > colNameComps = colpg->addComponents("Name");
	addColComps->addComponent< NoGUI::CText >(textFill);
	colLabelComps->addComponent< NoGUI::CText >(textFill);
	colInputComps->addComponent< NoGUI::CText >(textFill);
	colInputComps->addComponent< NoGUI::CInput >(3);
	colNameComps->addComponent< NoGUI::CText >(textFill, nullptr, 20.0f, NoGUI::Align(-1, 0));
	colNameComps->addComponent< NoGUI::CInput >(NoMAD::TAGBUFF);
	std::shared_ptr< NoGUI::Element > rLabel = colpg->addElement(labelShape, colRLabelPos, "Label", "r:");
	std::shared_ptr< NoGUI::Element > rInput = colpg->addElement(pageRect, colRPos, "Input", "0");
	std::shared_ptr< NoGUI::Element > gLabel = colpg->addElement(labelShape, colGLabelPos, "Label", "g:");
	std::shared_ptr< NoGUI::Element > gInput = colpg->addElement(pageRect, colGPos, "Input", "0");
	std::shared_ptr< NoGUI::Element > bLabel = colpg->addElement(labelShape, colBLabelPos, "Label", "b:");
	std::shared_ptr< NoGUI::Element > bInput = colpg->addElement(pageRect, colBPos, "Input", "0");
	std::shared_ptr< NoGUI::Element > aLabel = colpg->addElement(labelShape, colALabelPos, "Label", "a:");
	std::shared_ptr< NoGUI::Element > aInput = colpg->addElement(pageRect, colAPos, "Input", "255");
	std::shared_ptr< NoGUI::Element > addCol = colpg->addElement(pageRect, colPos, "Add", "+");
	// shapes editor
	std::shared_ptr< NoGUI::Page > shapepg = gui.addPage(false);
	std::shared_ptr< NoGUI::CContainer > shapeLabelComps = shapepg->addComponents("Label");
	std::shared_ptr< NoGUI::CContainer > shapeInputComps = shapepg->addComponents("Input");
	std::shared_ptr< NoGUI::CContainer > shapeColComps = shapepg->addComponents("DropDown");
	std::shared_ptr< NoGUI::CContainer > addShapeComps = shapepg->addComponents("Add");
	std::shared_ptr< NoGUI::CContainer > previewComps = shapepg->addComponents("Shape");
	std::shared_ptr< NoGUI::CContainer > nameComps = shapepg->addComponents("Name");
	shapeLabelComps->addComponent< NoGUI::CText >(textFill, nullptr, 20.0f, NoGUI::Align(-1, 0));
	shapeInputComps->addComponent< NoGUI::CText >(textFill);
	shapeColComps->addComponent< NoGUI::CText >(textFill);
	shapeInputComps->addComponent< NoGUI::CInput >(4);
	addShapeComps->addComponent< NoGUI::CText >(textFill);
	previewComps->addComponent< NoGUI::CText >(textFill, nullptr, 50.0f);
	nameComps->addComponent< NoGUI::CText >(textFill, nullptr, 20.0f, NoGUI::Align(-1, 0));
	nameComps->addComponent< NoGUI::CInput >(NoMAD::TAGBUFF);
	std::shared_ptr< NoGUI::Element > addShape = shapepg->addElement(pageRect, shapePos, "Add", "+");
	// elements editor
	std::shared_ptr< NoGUI::Page > elempg = gui.addPage(false);
	std::shared_ptr< NoGUI::CContainer > elemLabelComps = elempg->addComponents("Label");
	std::shared_ptr< NoGUI::CContainer > elemShapeComps = elempg->addComponents("DropDown");
	std::shared_ptr< NoGUI::CContainer > elemInputComps = elempg->addComponents("Input");
	std::shared_ptr< NoGUI::CContainer > addElemComps = elempg->addComponents("Add");
	std::shared_ptr< NoGUI::CContainer > elemNameComps = elempg->addComponents("Name");
	std::shared_ptr< NoGUI::CContainer > elemValueComps = elempg->addComponents("Value");
	elemLabelComps->addComponent< NoGUI::CText >(textFill, nullptr, 20.0f, NoGUI::Align(-1, 0));
	elemInputComps->addComponent< NoGUI::CText >(textFill);
	elemShapeComps->addComponent< NoGUI::CText >(textFill);
	elemInputComps->addComponent< NoGUI::CInput >(NoMAD::TAGBUFF);
	addElemComps->addComponent< NoGUI::CText >(textFill);
	elemNameComps->addComponent< NoGUI::CText >(textFill, nullptr, 20.0f, NoGUI::Align(-1, 0));
	elemValueComps->addComponent< NoGUI::CText >(textFill, nullptr, 20.0f, NoGUI::Align(-1, 0));
	elempg->addElement(labelShape, elemShapePos, "Label", "Shape:");
	std::shared_ptr< NoGUI::Element > shapeSelection = elempg->addElement(pageRect, elemShapePos, "DropDown");
	elempg->addElement(labelShape, elemTagPos, "Label", "Tag:");
	elempg->addElement(pageRect, elemTagPos, "Input", "Default");
	elempg->addElement(labelShape, elemInnerPos, "Label", "Inner:");
	elempg->addElement(pageRect, elemInnerPos, "Input");
	std::shared_ptr< NoGUI::Element > addElem = elempg->addElement(pageRect, addElemPos, "Add", "+");
	// colours dropdown
	std::shared_ptr< NoGUI::Page > colSelector = std::make_shared< NoGUI::Page >(false);
	gui.addPage(colSelector);
	// shapes dropdown
	std::shared_ptr< NoGUI::Page > shapeSelector = std::make_shared< NoGUI::Page >(false);
	gui.addPage(shapeSelector);
	// Page options
	std::shared_ptr< NoGUI::CContainer > optionComps = std::make_shared< NoGUI::CContainer >();
	optionComps->addComponent< NoGUI::CText >(textFill);
	NoGUI::CMap contextComps = NoGUI::CMap("Option", optionComps);
	std::shared_ptr< NoGUI::Page > contextMenu = gui.addPage(contextComps.getMap());
	NoGUI::Transform optionPos = NoGUI::Transform(window, shapeLabelRadius, NoGUI::Align(-1, -1));
	std::shared_ptr< NoGUI::Element > deleteOption = contextMenu->addElement(pageRect, optionPos, "Option", "delete");
	std::shared_ptr< NoGUI::Element > clearOption = contextMenu->addElement(pageRect, optionPos, "Option", "clear");
	
	InitWindow(window.x, window.y, "test");
	SetTargetFPS(60);
	while ( !WindowShouldClose() )
	{	
		BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawGrid(cellSize, screenSpace);
			gui.update();
			userGUI.update();
			userGUI.render();
			std::vector< std::shared_ptr< NoGUI::Element > > pageElems = pagepg->getElements("Page");
			std::vector< std::shared_ptr< NoGUI::Element > > propertyToggles = builderpg->getElements("Tab");
			if ( pagesToggle->isHover() && IsMouseButtonReleased(MOUSE_LEFT_BUTTON) )
			{
				if ( pageContainer->position.x < 0 )
				{
					for ( auto pageElem : pagepg->getElements() )
					{
						pageElem->translate(pageContainer->width(), 0);
					}
				}
				else
				{
					for ( auto pageElem : pagepg->getElements() )
					{
						pageElem->translate(pageContainer->width() * -1, 0);
					}
				}
			}
			for (auto elem : pageElems)
			{
				if ( elem->isHover() )
				{
					if ( IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
					{
						if ( TextIsEqual("+", elem->getInner()) )
						{
							// add page
							size_t pageNum = pageElems.size() - 1;
							currPage = pageNum;
							userGUI.addPage();
							userGUI.setEnabled(currPage);
							std::shared_ptr< NoGUI::Element > newPage = pagepg->addElement(pageRectSelect, *(addPage), "Page", TextFormat("%i", pageNum));
							addPage->translate(0, newPage->height() + pageLabelPos.height());
							NoGUI::Transform newTransform = NoGUI::Transform(newPage->pos(NoGUI::Align(0, 1)), labelRadius, NoGUI::Align(0, -1));
							std::shared_ptr< NoGUI::Element > newlabel = pagepg->addElement(labelShape, newTransform, "Label", TextFormat("Page %i", pageNum));
						}
						else
						{
							// set active page
							size_t pageNum = TextToInteger(elem->getInner());
							currPage = pageNum;
							userGUI.setEnabled(currPage);
							elem->setShape(pageRectSelect);
						}
					}
					else if ( IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) )
					{
						// page options/context menu
						if ( !TextIsEqual("+", elem->getInner()) )
						{
							contextMenu->setEnabled(true);
							std::vector< std::shared_ptr< NoGUI::Element > > menu = contextMenu->getElements();
							for (size_t i=0; i < menu.size(); i++)
							{
								menu[i]->repos((Vector2){(float)GetMouseX(), GetMouseY() + menu[i]->height() * i});
							}
						}
					}
				}
				if ( TextToInteger(elem->getInner()) != (int)currPage )
				{
					// not active shape
					elem->setShape(pageRect);
				}
			}
			bool dropdown = false;
			for (auto toggle : propertyToggles)
			{
				if ( toggle->isHover() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
				{
					toggle->setFocus(!toggle->getFocus());
					onPropertyPress(builderpg, colpg, shapepg, elempg);
				}
				if ( toggle->isFocus() )
				{
					dropdown = true;
				}
			}
			if ( dropdown )
			{
				// pop out editor
				coloursContainer->position.y = window.y;
				for (auto elem : builderpg->getElements())
				{
					elem->resize((Vector2){propertyButtonRadius.x * 1.5f, elem->radius.y});
				}
			}
			else
			{
				// pop in editor
				coloursContainer->position.y = 0;
				for (auto elem : builderpg->getElements())
				{
					elem->resize((Vector2){propertyButtonRadius.x, elem->radius.y});
				}
			}
			if ( colpg->getActive() )
			{
				for (auto elem : colpg->getElements())
				{
					elem->isHover();
					if ( TextIsEqual("x", elem->getInner()) )
					{
						if ( elem->getActive() && elem->getHover() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
						{
							// Remove Colour
							size_t index = TextToInteger(elem->getTag());
							std::shared_ptr< NoGUI::Fill > colToDel = userCols.at(index);
							std::vector< std::shared_ptr< NoGUI::Element > > colours = colpg->getElements("Colour");
							std::vector< std::shared_ptr< NoGUI::Element > > names = colpg->getElements("Name");
							std::vector< std::shared_ptr< NoGUI::Element > > options = colSelector->getElements();
							for (size_t i=0; i < colours.size(); i++)
							{
								if ( colours[i]->getShape()->fill == colToDel )
								{
									colours[i]->kill();
									names[i]->kill();
									options.at(i)->kill();
									elem->kill();
									// translate remaining entries back up
									index++;
									while (index < userCols.size())
									{
										std::vector< std::shared_ptr< NoGUI::Element > > delButtons = colpg->getElements(TextFormat("%i", index));
										for (auto delButton : delButtons)
										{
											delButton->setEnabled(false); // deactivate delete buttons for a frame to avoid domino effect when deleting
											delButton->translate(0, colours[i]->height() * -1 - 4);
										}
										index++;
									}
									for (auto input : colpg->getElements("Input"))
									{
										input->translate(0, colours[i]->height() * -1 - 4);
									}
									for (auto label : colpg->getElements("Label"))
									{
										label->translate(0, colours[i]->height() * -1 - 4);
									}
									addCol->translate(0, colours[i]->height() * -1 - 4);
									while (i < colours.size())
									{
										colours[i]->translate(0, colours[i]->height() * -1 - 4);
										names[i]->translate(0, colours[i]->height() * -1 - 4);
										i++;
									}
									
									break;
								}
							}
							if ( shapepg->getActive() )
							{
								shapesButton->translate(0, (addCol->height() + 4) * -1);
								for (auto elem : shapepg->getElements())
								{
									elem->translate(0, (addCol->height() + 4) * -1);
								}
							}
							if ( elempg->getActive() )
							{
								elementsButton->translate(0, addCol->height() + 4);
								for (auto elem : elempg->getElements())
								{
									elem->translate(0, addCol->height() + 4);
								}
							}
						}
					}
					// reactivate delete buttons
					elem->setEnabled(true);
				}
				std::vector< std::shared_ptr< NoGUI::Element > > colNames = colpg->getElements("Name");
				for (size_t i=0; i < colNames.size(); i++)
				{
					if ( colNames[i]->getHover() )
					{
						// update colours dropdown
						std::vector< std::shared_ptr< NoGUI::Element > > options = colSelector->getElements();
						options.at(i)->setInner(colNames[i]->getInner());
					}
				}
				if ( addCol->getHover() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
				{
					// add colour
					unsigned char red = TextToInteger(rInput->getInner());
					unsigned char green = TextToInteger(gInput->getInner());
					unsigned char blue = TextToInteger(bInput->getInner());
					unsigned char alpha = TextToInteger(aInput->getInner());
					userCols.push_back(std::make_shared< NoGUI::Fill >((Color){red, green, blue, alpha}));
					std::shared_ptr< NoGUI::nShape > colShape = std::make_shared< NoGUI::nShape >(4, userCols.back());
					NoGUI::Transform newColPos = *(bInput);
					NoGUI::Transform namePos = *(rInput);
					NoGUI::Transform deletePos = *(aInput);
					namePos.radius.x = coloursContainer->radius.x / 2;
					colpg->addElement(colShape, newColPos, "Colour");
					colpg->addElement(labelShape, namePos, "Name", TextFormat("Colour%i", colCounter));
					std::shared_ptr< NoGUI::Element > delButton = colpg->addElement(pageRect, deletePos, TextFormat("%i", colCounter), "x");
					delButton->components = addColComps;
					// translate inputs down
					for (auto label : colpg->getElements("Label"))
					{
						label->translate(0, label->height() + 4);
					}
					std::vector< std::shared_ptr< NoGUI::Element > > inputs = colpg->getElements("Input");
					for (size_t i=0; i < inputs.size(); i++)
					{
						std::shared_ptr< NoGUI::Element > input = inputs.at(i);
						input->translate(0, input->height() + 4);
						if (i != inputs.size() - 1)
						{
							input->setInner("0");
						}
						else
						{
							input->setInner("255");
						}
					}
					addCol->translate(0, addCol->height() + 4);
					if ( shapepg->getActive() || elempg->getActive() )
					{
						shapesButton->translate(0, addCol->height() + 4);
						for (auto elem : shapepg->getElements())
						{
							elem->translate(0, addCol->height() + 4);
						}
					}
					if ( elempg->getActive() )
					{
						// translate elements down
						elementsButton->translate(0, addCol->height() + 4);
						for (auto elem : elempg->getElements())
						{
							elem->translate(0, addCol->height() + 4);
						}
					}
					NoGUI::Transform selectPos = NoGUI::Transform(window, shapeLabelRadius, NoGUI::Align(-1, -1));
					std::shared_ptr< NoGUI::Element > selection = colSelector->addElement(pageRect, selectPos, TextFormat("%i", colSelector->size()), TextFormat("Colour%i", colCounter));
					selection->components = shapeColComps;
					colCounter++;
				}
			}
			if ( shapepg->getActive() )
			{
				for (auto elem : shapepg->getElements())
				{
					elem->isHover();
					if ( TextIsEqual("DropDown", elem->getTag()) )
					{
						if ( elem->getHover() )
						{
							if ( IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
							{
								elem->setFocus(true);
							}
						}
						else
						{
							elem->setFocus(false);
						}
					}
				}
				// colour dropdown
				bool makeSelection = false;
				if ( colSelector->getActive() )
				{
					for (auto selection : colSelector->getElements())
					{
						if ( selection->isHover() )
						{
							makeSelection = true;
							if ( IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
							{
								// get preview and set colour
								if ( colIndex % 2 == 0 )
								{
									std::shared_ptr< NoGUI::Element > preview = shapepg->getElement(shapepg->getElements("DropDown").at(colIndex)->getId() + 5);
									preview->getShape()->fill = userCols.at(TextToInteger(selection->getTag()));
								}
								else
								{
									std::shared_ptr< NoGUI::Element > preview = shapepg->getElement(shapepg->getElements("DropDown").at(colIndex)->getId() + 2);
									preview->getShape()->outline->fill = userCols.at(TextToInteger(selection->getTag()));
								}
							}
						}
					}
				}
				std::vector< std::shared_ptr< NoGUI::Element > > previews = shapepg->getElements("Shape");
				std::vector< std::shared_ptr< NoGUI::Element > > inputs = shapepg->getElements("Input");
				std::vector< std::shared_ptr< NoGUI::Element > > colours = shapepg->getElements("DropDown");
				std::vector< std::shared_ptr< NoGUI::Element > > names = shapepg->getElements("Name");
				for (size_t i=0; i < colours.size(); i++)
				{
					std::shared_ptr< NoGUI::Element > colour = colours.at(i);
					if ( colour->getFocus() )
					{
						colIndex = i;
						colSelector->setEnabled(true);
						makeSelection = true;
						std::vector< std::shared_ptr< NoGUI::Element > > options = colSelector->getElements();
						for (size_t option=0; option < options.size(); option++)
						{
							options.at(option)->repos((Vector2){colour->position.x, colour->pos(NoGUI::Align(0, -1)).y + colour->height() * (option + 1)});
						}
					
						break;
					}
				}
				if ( !makeSelection )
				{
					colSelector->setEnabled(false);
				}
				for (auto preview : previews)
				{
					double fullRotateTime = 0.05;
					int step = GetTime() / fullRotateTime;
					int angle = step % 360;
					preview->angle = (float)angle;
					if ( preview->getHover() )
					{
						if ( !preview->getFocus() )
						{
							preview->setInner("+");
							if ( IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
							{
								// add shape
								preview->setFocus(true);
								std::shared_ptr< NoGUI::Element > container = shapepg->getElement(preview->getId() - 1);
								NoGUI::Transform namePos = NoGUI::Transform((Vector2){shapesButton->pos(NoGUI::Align()).x + container->radius.x + 16, preview->position.y}, (Vector2){shapesButton->radius.x - container->radius.x - 8, shapesButton->radius.y}, NoGUI::Align(0, 0));
								std::shared_ptr< NoGUI::Element > newName = shapepg->addElement(labelShape, namePos, "Name", TextFormat("Shape%i", shapeCounter));
								container->setInner(TextFormat("%i", newName->getId()));
								userShapes.push_back(preview->getShape());
								NoGUI::Transform selectPos = NoGUI::Transform(window, shapeLabelRadius, NoGUI::Align(-1, -1));
								std::shared_ptr< NoGUI::Element > selection = shapeSelector->addElement(pageRect, selectPos, TextFormat("%i", shapeSelector->size()), TextFormat("Shape%i", shapeCounter));
								selection->components = shapeColComps;
								shapeCounter++;
								// remove inputs
								shapepg->removeElement(preview->getId() - 2);
								shapepg->removeElement(preview->getId() - 3);
								shapepg->removeElement(preview->getId() - 4);
								shapepg->removeElement(preview->getId() - 5);
								shapepg->removeElement(preview->getId() - 6);
								shapepg->removeElement(preview->getId() - 7);
							}
						}
					}
					else
					{
						preview->setInner("");
					}
				}
				if ( inputs.size() )
				{
					for (size_t i=0; i < inputs.size(); i++)
					{
						std::shared_ptr< NoGUI::Element > input = inputs.at(i);
						if ( input->getHover() )
						{
							// adjust preview
							if ( i % 2 == 0 ) // nInput
							{
								std::shared_ptr< NoGUI::Element > preview = shapepg->getElement(input->getId() + 6);
								preview->getShape()->n = TextToInteger(input->getInner());
							}
							else // thickInput
							{
								std::shared_ptr< NoGUI::Element > preview = shapepg->getElement(input->getId() + 3);
								preview->getShape()->outline->thick = TextToInteger(input->getInner());
							}
						}
					}
				}
				std::vector< std::shared_ptr< NoGUI::Element > > shapeNames = shapepg->getElements("Name");
				for (size_t i=0; i < shapeNames.size(); i++)
				{
					if ( shapeNames[i]->getHover() )
					{
						// update shapes dropdown
						std::vector< std::shared_ptr< NoGUI::Element > > options = shapeSelector->getElements();
						options.at(i)->setInner(shapeNames[i]->getInner());
					}
				}
				if ( addShape->getHover() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
				{
					NoGUI::Transform nLabelPos = NoGUI::Transform((Vector2){addShape->pos(NoGUI::Align(1, 0)).x + 4, addShape->pos(NoGUI::Align(0, -1)).y}, shapeLabelRadius, NoGUI::Align(-1, -1));
					NoGUI::Transform nInputPos = NoGUI::Transform((Vector2){nLabelPos.pos(NoGUI::Align(1, 0)).x, addShape->pos(NoGUI::Align(0, -1)).y}, (Vector2){12, shapeLabelRadius.y}, NoGUI::Align(-1, -1));
					NoGUI::Transform shapeColPos = NoGUI::Transform((Vector2){nInputPos.pos(NoGUI::Align(1, 0)).x + 4, addShape->pos(NoGUI::Align(0, -1)).y}, shapeLabelRadius, NoGUI::Align(-1, -1));
					NoGUI::Transform thickLabelPos = NoGUI::Transform((Vector2){nLabelPos.position.x, addShape->pos(NoGUI::Align(0, 1)).y}, shapeLabelRadius, NoGUI::Align(-1, 1));
					NoGUI::Transform thickInputPos = NoGUI::Transform((Vector2){nLabelPos.pos(NoGUI::Align(1, 0)).x, addShape->pos(NoGUI::Align(0, 1)).y}, (Vector2){12, shapeLabelRadius.y}, NoGUI::Align(-1, 1));
					NoGUI::Transform outlineColPos = NoGUI::Transform((Vector2){nInputPos.pos(NoGUI::Align(1, 0)).x + 4, addShape->pos(NoGUI::Align(0, 1)).y}, shapeLabelRadius, NoGUI::Align(-1, 1));
					shapepg->addElement(labelShape, nLabelPos, "Label", "sides:");
					std::shared_ptr< NoGUI::Element > nInput = shapepg->addElement(pageRect, nInputPos, "Input", "4");
					shapepg->addElement(pageRect, shapeColPos, "DropDown", "Colour");
					shapepg->addElement(labelShape, thickLabelPos, "Label", "thickness:");
					std::shared_ptr< NoGUI::Element > thicknessInput = shapepg->addElement(pageRect, thickInputPos, "Input", "2");
					shapepg->addElement(pageRect, outlineColPos, "DropDown", "Colour");
					shapepg->addElement(pageRect, *(addShape), "Container");
					std::shared_ptr< NoGUI::Outline > previewLines;
					std::shared_ptr< NoGUI::nShape > shapePreview;
					if ( userCols.size() )
					{
						previewLines = std::make_shared< NoGUI::Outline >(userCols.front(), TextToInteger(thicknessInput->getInner()));
						shapePreview = std::make_shared< NoGUI::nShape >(TextToInteger(nInput->getInner()), userCols.front(), previewLines);
					}
					else
					{
						previewLines = std::make_shared< NoGUI::Outline >(noFill, TextToInteger(thicknessInput->getInner()));
						shapePreview = std::make_shared< NoGUI::nShape >(TextToInteger(nInput->getInner()), noFill, previewLines);
					}
					NoGUI::Transform previewPos = NoGUI::Transform(addShape->pos(NoGUI::Align(0, 0)), (Vector2){addShape->radius.x / 1.5f, addShape->radius.x / 1.5f}, NoGUI::Align(0, 0));
					shapepg->addElement(shapePreview, previewPos, "Shape");
					addShape->translate(0, addShape->height() + 4);
					if ( elempg->getActive() )
					{
						elementsButton->translate(0, addShape->height() + 4);
						for (auto elem : elempg->getElements())
						{
							elem->translate(0, addShape->height() + 4);
						}
					}
				}
			}
			if ( elempg->getActive() )
			{
				for (auto elem : elempg->getElements())
				{
					elem->isHover();
				}
				if ( shapeSelection->getHover() )
				{
					if ( IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
					{
						shapeSelection->setFocus(true);
					}
				}
				else
				{
					shapeSelection->setFocus(false);
				}
				// Shape dropdown
				bool makeSelection = false;
				if ( shapeSelector->getActive() )
				{
					for (size_t i=0; i < shapeSelector->getElements().size(); i++)
					{
						std::shared_ptr< NoGUI::Element > selection = shapeSelector->getElements().at(i);
						if ( selection->isHover() )
						{
							makeSelection = true;
							if ( IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
							{
								shapeIndex = i;
								shapeSelection->setInner(selection->getInner());
							}
						}
					}
				}
				std::vector< std::shared_ptr< NoGUI::Element > > shapes = elempg->getElements("DropDown");
				for (size_t i=0; i < shapes.size(); i++)
				{
					std::shared_ptr< NoGUI::Element > shape = shapes.at(i);
					if ( shape->getFocus() )
					{
						shapeSelector->setEnabled(true);
						makeSelection = true;
						std::vector< std::shared_ptr< NoGUI::Element > > options = shapeSelector->getElements();
						for (size_t option=0; option < options.size(); option++)
						{
							options.at(option)->repos((Vector2){shape->position.x, shape->pos(NoGUI::Align(0, -1)).y + shape->height() * (option + 1)});
						}
					
						break;
					}
				}
				if ( !makeSelection )
				{
					shapeSelector->setEnabled(false);
				}
				for (auto preview : elempg->getElements("Preview"))
				{
					if ( preview->getHover() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
					{
						// add to userGUI
						if ( userGUI.size() > currPage )
						{
							NoGUI::Transform newPos = NoGUI::Transform(GetMousePosition(), (Vector2){cellSize * 2.0f, cellSize * 2.0f}, NoGUI::Align(0, 0));
							std::shared_ptr< NoGUI::Page > activePage = userGUI.getPage(currPage);
							for (auto pageElem : activePage->getElements())
							{
								pageElem->setFocus(false);
							}
							std::shared_ptr< NoGUI::Element > newElem = activePage->addElement(preview->getShape(), newPos, preview->getTag(), preview->getInner());
							newElem->setFocus(true);
							action = TransformState::REPOSITION;
						}
					}
				}
				if ( addElem->getHover() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
				{
					Vector2 containerSize = {30, (propertyButtonRadius.y + 4) * 2};
					// replace shape label and dropdown with preview
					NoGUI::Transform containerPos = NoGUI::Transform(window, containerSize, NoGUI::Align(-1, -1));
					for (auto label : elempg->getElements("Label"))
					{
						if (label->getInner()[0] == 'S')
						{
							containerPos.repos(label->pos(NoGUI::Align(-1, -1)));
							shapeSelection->translate(0, containerSize.y * 2 + 4);
						}
						label->translate(0, containerSize.y * 2 + 4);
					}
					for (auto input : elempg->getElements("Input"))
					{
						elempg->addElement(labelShape, *(input), "Value", input->getInner());
						input->translate(0, containerSize.y * 2 + 4);
					}
					elempg->addElement(pageRect, containerPos, "Container", TextFormat("%i", shapeIndex));
					NoGUI::Transform previewPos = NoGUI::Transform(containerPos.pos(NoGUI::Align(0, 0)), (Vector2){containerPos.radius.x / 1.5f, containerPos.radius.x / 1.5f}, NoGUI::Align(0, 0));
					elempg->addElement(userShapes.at(shapeIndex), previewPos, "Preview", TextFormat("%i", shapeIndex));
					addElem->translate(0, containerSize.y * 2 + 4);
				}
			}
			if ( contextMenu->getActive() )
			{
				for (auto elem : contextMenu->getElements())
				{
					elem->isHover();
				}
				if ( IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
				{
					// get context
					std::shared_ptr< NoGUI::Element > context = nullptr;
					std::shared_ptr< NoGUI::Element > frontOption = contextMenu->getElements().front();
					Vector2 frontOptionTopLeft = frontOption->pos(NoGUI::Align(-1, -1));
					Rectangle frontOptionBBox = {frontOptionTopLeft.x, frontOptionTopLeft.y, frontOption->width(), frontOption->height()};
					for (auto page : pageElems)
					{
						if ( context == nullptr )
						{
							Vector2 pageTopLeft = page->pos(NoGUI::Align(-1, -1));
							Rectangle PageBBox = {pageTopLeft.x, pageTopLeft.y, page->width(), page->height()};
							if ( CheckCollisionRecs(PageBBox, frontOptionBBox) )
							{
								context = page;
								
								break;
							}
						}
					}
					for (auto elem : contextMenu->getElements())
					{
						if ( elem->getHover() )
						{
							if ( TextIsEqual("delete", elem->getInner()) )
							{
								// delete page
								if ( context->getInner()[0] != '+' )
								{
									for (auto page : pageElems)
									{
										if ( page->getInner()[0] != '+' && page->getId() > context->getId() )
										{
											page->setInner(TextFormat("%i", TextToInteger(page->getInner()) - 1));
											page->translate(0, (page->height() + pageLabelPos.height()) * -1);
										}
									}
									context->kill();
									userGUI.removePage(TextToInteger(context->getInner()));
									pagepg->getElements("Label").back()->kill();
									// translate addPage button
									addPage->translate(0, (pageElems.at(1)->height() + pageLabelPos.height()) * -1);
								}
							}
							else if ( TextIsEqual("clear", elem->getInner()) )
							{
								// clear elements in page
								if ( context->getInner()[0] != '+' )
								{
									userGUI.getPage(TextToInteger(context->getInner()))->clearElements();
									userGUI.getPage(TextToInteger(context->getInner()))->update();
								}
							}
						}
					}
					contextMenu->setEnabled(false);
				}
			}
			for (auto pg : userGUI.getPages())
			{
				if ( pg->getActive() )
				{	
					SetMouseCursor(MOUSE_CURSOR_DEFAULT);
					// find currently selected element
					std::shared_ptr< NoGUI::Element > actionElem = nullptr;
					for (auto elem : pg->getElements())
					{
						elem->isHover();
						if ( elem->getFocus() )
						{
							actionElem = elem;
						}
						else if ( elem->getHover() )
						{
							SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
						}
					}
					// update currently selected element on mouse click
					if ( IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
					{
						for (auto elem : pg->getElements())
						{
							elem->setFocus(false);
							if ( elem->getHover() )
							{
								elem->setFocus(true);
								actionElem = elem;
							}
						}
					}
					if ( actionElem )
					{
						// mouse cursor stuff
						Vector2 mousePos = GetMousePosition();
						Vector2 handlePoint = GetHandlesCollision(mousePos, *(actionElem));
						bool rotateCollider = CheckCollisionPointRotationCircle(mousePos, *(actionElem));
						if (handlePoint.x > 0 )
						{
							if ( handlePoint.y > 0)
							{
								SetMouseCursor(MOUSE_CURSOR_RESIZE_NWSE);
							}
							else if ( handlePoint.y < 0 )
							{
								SetMouseCursor(MOUSE_CURSOR_RESIZE_NESW);
							}
							else
							{
								SetMouseCursor(MOUSE_CURSOR_RESIZE_EW);
							}
						}
						else if (handlePoint.x < 0)
						{
							if ( handlePoint.y > 0)
							{
								SetMouseCursor(MOUSE_CURSOR_RESIZE_NESW);
							}
							else if ( handlePoint.y < 0 )
							{
								SetMouseCursor(MOUSE_CURSOR_RESIZE_NWSE);
							}
							else
							{
								SetMouseCursor(MOUSE_CURSOR_RESIZE_EW);
							}
						}
						else if (handlePoint.y != 0)
						{
							SetMouseCursor(MOUSE_CURSOR_RESIZE_NS);
						}
						if ( rotateCollider )
						{
							SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);
						}
						// update action state
						if ( IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
						{
							if ( handlePoint.x != 0 )
							{
								actionElem->setFocus(true);
								action = TransformState::SCALEX;
								if ( handlePoint.y != 0 )
								{
									action = TransformState::SCALEXY;
								}
							}
							else if ( handlePoint.y != 0 )
							{
								actionElem->setFocus(true);
								action = TransformState::SCALEY;
							}
							else if ( actionElem->getHover() )
							{
								action = TransformState::REPOSITION;
							}
							else if ( rotateCollider )
							{
								actionElem->setFocus(true);
								action = TransformState::ROTATE;
							}
							else
							{
								action = TransformState::IDLE;
							}
						}
						if ( IsMouseButtonReleased(MOUSE_LEFT_BUTTON) )
						{
							action = TransformState::IDLE;
						}
						// perform action depending on state
						switch (action)
						{
							case TransformState::IDLE:
							{
								DrawHandles(*(actionElem));
								
								break;
							}
							
							case TransformState::REPOSITION:
							{
								SetMouseCursor(MOUSE_CURSOR_RESIZE_ALL);
								actionElem->repos(GetMousePosition());
								SnapToGrid(cellSize, *(actionElem));
								
								break;
							}
							
							case TransformState::SCALEX:
							{
								SetMouseCursor(MOUSE_CURSOR_RESIZE_EW);
								Vector2 mousePos =  GetMousePosition();
								Vector2 centerPos = actionElem->pos(NoGUI::Align(0, 0));
								int newRadius = actionElem->radius.x;
								if ( mousePos.x > centerPos.x )
								{
									newRadius = mousePos.x - centerPos.x;
								}
								else
								{
									newRadius = centerPos.x - mousePos.x;
								}
								
								if ( newRadius % cellSize == 0 )
								{
									actionElem->radius.x = newRadius;
								}
								
								break;
							}
							
							case TransformState::SCALEY:
							{
								SetMouseCursor(MOUSE_CURSOR_RESIZE_NS);
								Vector2 mousePos =  GetMousePosition();
								Vector2 centerPos = actionElem->pos(NoGUI::Align(0, 0));
								int newRadius = actionElem->radius.y;
								if ( mousePos.y > centerPos.y )
								{
									newRadius = mousePos.y - centerPos.y;
								}
								else
								{
									newRadius = centerPos.y - mousePos.y;
								}
								
								if ( newRadius % cellSize == 0 )
								{
									actionElem->radius.y = newRadius;
								}
								
								break;
							}
							
							case TransformState::SCALEXY:
							{
								unsigned int cursor = 0;
								int cursorDeterminant = 1;
								Vector2 mousePos =  GetMousePosition();
								Vector2 centerPos = actionElem->pos(NoGUI::Align(0, 0));
								Vector2 newRadius = actionElem->radius;
								if ( mousePos.x > centerPos.x )
								{
									cursor = 7;
									newRadius.x = mousePos.x - centerPos.x;
								}
								else
								{
									cursor = 8;
									cursorDeterminant *= -1;
									newRadius.x = centerPos.x - mousePos.x;
								}
								if ( mousePos.y > centerPos.y )
								{
									newRadius.y = mousePos.y - centerPos.y;
								}
								else
								{
									cursor += cursorDeterminant;
									newRadius.y = centerPos.y - mousePos.y;
								}
								SetMouseCursor(cursor);
								if ( (int)newRadius.x % cellSize == 0 )
								{
									actionElem->radius.x = newRadius.x;
								}
								if ( (int)newRadius.y % cellSize == 0 )
								{
									actionElem->radius.y = newRadius.y;
								}
								
								break;
							}
							
							case TransformState::ROTATE:
							{
								SetMouseCursor(MOUSE_CURSOR_ARROW);
								Vector2 vec = Vector2Subtract(mousePos, actionElem->pos());
								float angle = RAD2DEG * atan2(vec.y, vec.x) + 90;
								if ( IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT) )
								{
									if ( (int)angle % 10 == 0 )
									{
										actionElem->angle = angle;
									}
								}
								else
								{
									actionElem->angle = angle;
								}
								
								break;
							}
						}
					}
				}
			}
			gui.render();
		EndDrawing();
	}
	
	return 0;
}