#include "../../../src/GUI.h"

NoGUI::Manager manager = NoGUI::Manager();
float multiplier = 1.0f;

class EventHandler : public NoGUI::Listener
{
	void onNotify(std::shared_ptr< NoGUI::Element > elem, NoGUI::HoverEvent hevent, NoGUI::FocusEvent fevent)
	{
		if ( TextIsEqual(elem->getTag(), "Input") )
		{
			if ( elem == manager.getPage(1)->getElements("Input").front() )
			{
				// TODO: text to float
				multiplier = TextToInteger(elem->getInner());
				for (std::shared_ptr< NoGUI::Element > slider : manager.getPage()->getElements("Slider"))
				{
					slider->setFocus(true);
				}
			}
			else if ( elem == manager.getPage(1)->getElements("Input")[1] )
			{
				for ( std::shared_ptr< NoGUI::Element > slider : manager.getPage()->getElements() )
				{
					slider->angle = TextToInteger(elem->getInner());
				}
			}
			else if ( elem == manager.getPage(1)->getElements("Input")[2] )
			{
				NoGUI::NotchedCursorer* slider = dynamic_cast< NoGUI::NotchedCursorer* >(manager.getPage()->getElements("Slider").back().get());
				if ( slider )
				{
					slider->setNotches((unsigned int)TextToInteger(elem->getInner()));
				}
			}
		}
		else if ( TextIsEqual(elem->getTag(), "Slider") )
		{
			std::shared_ptr< NoGUI::Element > textBox = manager.getPage()->getElement(elem->getId() + 1);
			float val = TextToInteger(textBox->getInner());
			if ( TextIsEqual(elem->getInner(), "Slider") )
			{
				NoGUI::Slider* slider = dynamic_cast< NoGUI::Slider* >(elem.get());
				val = slider->getSlideTransform().radius.x * 2 * multiplier;
			}
			else if ( TextIsEqual(elem->getInner(), "Cursorer") )
			{
				NoGUI::Cursorer* cursorer = dynamic_cast< NoGUI::Cursorer* >(elem.get());
				val = cursorer->getSlideTransform().position.x * multiplier;
			}

			textBox->setInner(TextFormat("%f", val));
		}
		else if ( TextIsEqual(elem->getTag(), "DropDown") )
		{
			std::shared_ptr< NoGUI::Page > contextMenu = manager.getPage(2);
			if ( fevent == NoGUI::FocusEvent::ONFOCUS )
			{
				contextMenu->setEnabled(!contextMenu->getActive());
			}
			if ( hevent == NoGUI::HoverEvent::OFFHOVER )
			{
				bool enable = false;
				for (std::shared_ptr< NoGUI::Element > elem : contextMenu->getElements())
				{
					if ( elem->isHover() )
					{
						enable = true;
						
						break;
					}
				}
				manager.getPage(2)->setEnabled(enable);
			}
		}
		else if ( TextIsEqual(elem->getTag(), "Option") )
		{
			NoGUI::ContextPage* options = dynamic_cast< NoGUI::ContextPage* >(manager.getPage(2).get());
			std::shared_ptr< NoGUI::Element > context = options->getContext();
			if ( fevent == NoGUI::FocusEvent::ONFOCUS )
			{
				manager.getPage(2)->setEnabled(false);
				manager.getPage(1)->getElements("DropDown").front()->setInner(elem->getInner());
				for (std::shared_ptr< NoGUI::Element > slider : manager.getPage()->getElements("Slider"))
				{
					NoGUI::Slider* sliderCast = dynamic_cast< NoGUI::Slider* >(slider.get());
					NoGUI::Transform slideTransform = sliderCast->getSlideTransform();
					if ( elem->getId() == 0 )
					{
						slideTransform.origin = NoGUI::Align(-1, 0);
					}
					else if ( elem->getId() == 1 )
					{
						slideTransform.origin = NoGUI::Align(1, 0);
					}
					else if ( elem->getId() == 2 )
					{
						slideTransform.origin = NoGUI::Align(0, 0);
					}
					sliderCast->setSlide(nullptr, slideTransform);
					sliderCast->setFocus(true);
				}
			}
			
			if ( hevent == NoGUI::HoverEvent::OFFHOVER )
			{
				bool enable = context->isHover();
				if ( enable == false )
				{
					std::vector< std::shared_ptr< NoGUI::Element > > optionElems = options->getElements();
					NoGUI::Transform collisionArea = NoGUI::Transform(*optionElems.front().get());
					int shapeSides = optionElems.front()->getShape()->n;
					for (size_t i=1; i < optionElems.size(); i++)
					{
						collisionArea.radius.y += (optionElems[i]->getShape()->outline) ? optionElems[i]->radius.y + optionElems[i]->getShape()->outline->thick : optionElems[i]->radius.y;
					}
					if ( optionElems.back()->getShape()->outline )
					{
						collisionArea.radius.y -= optionElems.back()->getShape()->outline->thick * 2;
					}
					enable = CheckCollisionPointShape(GetMousePosition(), shapeSides, collisionArea);
				}
				options->setEnabled(enable);
			}
		}
	}
};

int main(int argc, char ** argv)
{
	// initialization
	Vector2 window = {1280, 720};
	Vector2 elemSize = {200, 50};
	Vector2 textSize = {75, 50};
	float margin = 25.0f;
	manager.addListener(std::make_shared< EventHandler >());
	
	std::shared_ptr< NoGUI::Fill > noFill = std::make_shared< NoGUI::Fill >(BLANK);
	std::shared_ptr< NoGUI::Fill > lineFill = std::make_shared< NoGUI::Fill >(GRAY);
	std::shared_ptr< NoGUI::Fill > outlineFill = std::make_shared< NoGUI::Fill >(BROWN);
	std::shared_ptr< NoGUI::Fill > slideFill = std::make_shared< NoGUI::Fill >(GREEN);
	std::shared_ptr< NoGUI::Fill > cursorFill = std::make_shared< NoGUI::Fill >(RAYWHITE);
	std::shared_ptr< NoGUI::Fill > textFill = std::make_shared< NoGUI::Fill >(BLACK);
	
	std::shared_ptr< NoGUI::Outline > outline = std::make_shared< NoGUI::Outline >(outlineFill, 3);
	std::shared_ptr< NoGUI::nShape > bar = std::make_shared< NoGUI::nShape >(4, noFill, outline);
	std::shared_ptr< NoGUI::nShape > filledBar = std::make_shared< NoGUI::nShape >(4, textFill, outline);
	std::shared_ptr< NoGUI::nShape > label = std::make_shared< NoGUI::nShape >(4, noFill);
	std::shared_ptr< NoGUI::nShape > box = std::make_shared< NoGUI::nShape >(4, cursorFill);
	std::shared_ptr< NoGUI::nShape > slide = std::make_shared< NoGUI::nShape >(4, slideFill);
	std::shared_ptr< NoGUI::nShape > line = std::make_shared< NoGUI::nShape >(2, lineFill);
	std::shared_ptr< NoGUI::nShape > cursor = std::make_shared< NoGUI::nShape >(0, cursorFill, outline);
	
	NoGUI::Transform centerPos1 = NoGUI::Transform((Vector2){window.x / 2.0f - textSize.x - margin, window.y / 2.0f - (elemSize.y * 2.0f + margin) * 1.5f}, elemSize, NoGUI::Align(0, 0));
	NoGUI::Transform textPos1 = NoGUI::Transform((Vector2){centerPos1.position.x + elemSize.x + margin, centerPos1.position.y}, textSize, NoGUI::Align(-1, 0));
	NoGUI::Transform centerPos3 = NoGUI::Transform((Vector2){centerPos1.position.x, window.y - centerPos1.position.y}, elemSize, NoGUI::Align(0, 0));
	NoGUI::Transform textPos3 = NoGUI::Transform((Vector2){textPos1.position.x, centerPos3.position.y}, textSize, NoGUI::Align(-1, 0));
	NoGUI::Transform centerPos2 = NoGUI::Transform((Vector2){centerPos1.position.x, (centerPos1.position.y + centerPos3.position.y) / 2.0f}, elemSize, NoGUI::Align(0, 0));
	NoGUI::Transform textPos2 = NoGUI::Transform((Vector2){textPos1.position.x, centerPos2.position.y}, textSize, NoGUI::Align(-1, 0));
	NoGUI::Transform controlsPos = NoGUI::Transform((Vector2){window.x, window.y / 2}, (Vector2){(window.x / 2 - elemSize.x - textSize.x * 3 - margin * 2.5f), window.y / 2}, NoGUI::Align(1, 0));
	Vector2 controlCenter = controlsPos.pos(NoGUI::Align(0, -1));
	NoGUI::Transform labelPos1 = NoGUI::Transform((Vector2){controlCenter.x - textSize.x, controlCenter.y + margin}, textSize, NoGUI::Align(0, -1));
	NoGUI::Transform inputPos1 = NoGUI::Transform((Vector2){controlCenter.x, labelPos1.position.y}, textSize, NoGUI::Align(-1, -1));
	NoGUI::Transform labelPos2 = NoGUI::Transform((Vector2){labelPos1.position.x, labelPos1.pos(NoGUI::Align(0, 1)).y + margin}, textSize, NoGUI::Align(0, -1));
	NoGUI::Transform inputPos2 = NoGUI::Transform((Vector2){controlCenter.x, labelPos2.position.y}, textSize, NoGUI::Align(-1, -1));
	NoGUI::Transform labelPos3 = NoGUI::Transform((Vector2){labelPos1.position.x, labelPos2.pos(NoGUI::Align(0, 1)).y + margin}, textSize, NoGUI::Align(0, -1));
	NoGUI::Transform inputPos3 = NoGUI::Transform((Vector2){controlCenter.x, labelPos3.position.y}, textSize, NoGUI::Align(-1, -1));
	NoGUI::Transform labelPos4 = NoGUI::Transform((Vector2){labelPos1.position.x, labelPos3.pos(NoGUI::Align(0, 1)).y + margin}, textSize, NoGUI::Align(0, -1));
	NoGUI::Transform inputPos4 = NoGUI::Transform((Vector2){controlCenter.x, labelPos4.position.y}, textSize, NoGUI::Align(-1, -1));
	
	std::shared_ptr< NoGUI::CContainer > textBoxComps = std::make_shared< NoGUI::CContainer >();
	textBoxComps->addComponent< NoGUI::CText >(textFill);
	std::shared_ptr< NoGUI::CContainer > textComps = std::make_shared< NoGUI::CContainer >();
	textComps->addComponent< NoGUI::CText >(cursorFill);
	std::shared_ptr< NoGUI::CContainer > inputComps = std::make_shared< NoGUI::CContainer >();
	inputComps->addComponent< NoGUI::CText >(textFill);
	inputComps->addComponent< NoGUI::CInput >(10);
	manager.getPage()->addComponents("Value", textBoxComps);
	manager.getPage()->addElement< NoGUI::Slider >(bar, centerPos1, "Slider", "Slider", nullptr, slide);
	manager.getPage()->addElement< NoGUI::Element >(box, textPos1, "Value", "0");
	manager.getPage()->addElement< NoGUI::Cursorer >(line, centerPos2, "Slider", "Cursorer");
	manager.getPage()->addElement< NoGUI::Element >(box, textPos2, "Value", "0");
	manager.getPage()->addElement< NoGUI::NotchedCursorer >(line, centerPos3, "Slider", "Cursorer", nullptr, nullptr, NoGUI::Align(-1, 0), (Vector2){10.0f, 10.0f}, 5);
	manager.getPage()->addElement< NoGUI::Element >(box, textPos3, "Value", "0");
	manager.addPage(true);
	manager.getPage(1)->addComponents("Label", textComps);
	manager.getPage(1)->addComponents("DropDown", textComps);
	manager.getPage(1)->addComponents("Value", textBoxComps);
	manager.getPage(1)->addComponents("Input", inputComps);
	manager.getPage(1)->addElement< NoGUI::Element >(bar, controlsPos, "Container", "");
	manager.getPage(1)->addElement< NoGUI::Element >(label, labelPos2, "Label", "Multipler:");
	manager.getPage(1)->addElement< NoGUI::Hoverable >(box, inputPos2, "Input", "1.0");
	manager.getPage(1)->addElement< NoGUI::Element >(label, labelPos3, "Label", "Angle:");
	manager.getPage(1)->addElement< NoGUI::Hoverable >(box, inputPos3, "Input", "0");
	manager.getPage(1)->addElement< NoGUI::Element >(label, labelPos4, "Label", "Notch Count:");
	manager.getPage(1)->addElement< NoGUI::Hoverable >(box, inputPos4, "Input", "5");
	manager.getPage(1)->addElement< NoGUI::Element >(label, labelPos1, "Label", "Alignment:");
	std::shared_ptr< NoGUI::Button > alignMenuElem = manager.getPage(1)->addElement< NoGUI::Button >(filledBar, inputPos1, "DropDown", "LEFT");
	std::shared_ptr< NoGUI::ContextPage > alignMenu = std::make_shared< NoGUI::ContextPage >(alignMenuElem, alignMenuElem->pos(NoGUI::Align(0, 1)), false);
	alignMenu->addComponents("Option", textComps);
	alignMenu->addElement< NoGUI::Button >(filledBar, textSize, "Option", "LEFT");
	alignMenu->update();
	alignMenu->addElement< NoGUI::Button >(filledBar, textSize, "Option", "RIGHT");
	alignMenu->update();
	alignMenu->addElement< NoGUI::Button >(filledBar, textSize, "Option", "CENTER");
	alignMenu->update();
	manager.addPage(alignMenu);
	
	// main
	InitWindow(window.x, window.y, "test");
	SetTargetFPS(60);
	while ( !WindowShouldClose() )
	{
		manager.update();
		BeginDrawing();
			manager.render();
			ClearBackground(BLACK);
		EndDrawing();
	}
	
	return 0;
}