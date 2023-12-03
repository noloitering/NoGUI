#include "../../../src/GUI.h"

int main(int argc, char ** argv)
{
	Vector2 window = {1280, 720};
	Vector2 elemSize = {75, 75};
	std::vector< const char* > stringsEntered = {"+"};
	size_t tagInputID;
	size_t addTagID;
	size_t toDel;
	std::shared_ptr< NoGUI::Fill > baseFill = std::make_shared< NoGUI::Fill >(GRAY);
	std::shared_ptr< NoGUI::Fill > noFill = std::make_shared< NoGUI::Fill >((Color){1, 1, 1, 1});
	std::shared_ptr< NoGUI::Fill > elemFill = std::make_shared< NoGUI::Fill >(GRAY, DARKGRAY);
	std::shared_ptr< NoGUI::Fill > buttonFill = std::make_shared< NoGUI::Fill >(DARKGRAY, BLACK);
	std::shared_ptr< NoGUI::Fill > outFill = std::make_shared< NoGUI::Fill >(WHITE);
	std::shared_ptr< NoGUI::Fill > closeFill = std::make_shared< NoGUI::Fill >(RED, MAROON);
	std::shared_ptr< NoGUI::Fill > badEntryFill = std::make_shared< NoGUI::Fill >(MAROON, BLACK);
	std::shared_ptr< NoGUI::Outline > outline = std::make_shared< NoGUI::Outline >(outFill, 2);
	
	std::shared_ptr< NoGUI::nShape > rect = std::make_shared< NoGUI::nShape >(4, baseFill, outline);
	std::shared_ptr< NoGUI::nShape > noShape = std::make_shared< NoGUI::nShape >(4, noFill);
	std::shared_ptr< NoGUI::nShape > button = std::make_shared< NoGUI::nShape >(4, elemFill, outline);
	std::shared_ptr< NoGUI::nShape > closeShape = std::make_shared< NoGUI::nShape >(4, closeFill, outline);
	std::shared_ptr< NoGUI::nShape > buttonShape = std::make_shared< NoGUI::nShape >(4, buttonFill, outline);
	std::shared_ptr< NoGUI::nShape > inputShape = std::make_shared< NoGUI::nShape >(4, buttonFill, outline);
	
	NoGUI::Transform startPos = NoGUI::Transform((Vector2){20, 20}, elemSize, NoGUI::Align(-1, -1));
	NoGUI::Transform tagButtonPos = NoGUI::Transform((Vector2){startPos.position.x, startPos.position.y + startPos.height() + 20}, elemSize, startPos.origin);
	NoGUI::Transform elemButtonPos = NoGUI::Transform((Vector2){startPos.position.x + startPos.width() + 20, startPos.position.y}, elemSize, startPos.origin);
	NoGUI::Transform centerPos = NoGUI::Transform((Vector2){window.x / 2, window.y / 2}, (Vector2){300, 150}, NoGUI::Align());
	NoGUI::Transform textPos = NoGUI::Transform((Vector2){centerPos.position.x, centerPos.position.y - 40}, (Vector2){centerPos.radius.x, 20}, NoGUI::Align());
	Vector2 centerBottom = centerPos.pos(NoGUI::Align(0, 1));
	NoGUI::Transform inputPos = NoGUI::Transform((Vector2){centerBottom.x, centerBottom.y - 8}, (Vector2){150, 50}, NoGUI::Align(0, 1));
	NoGUI::Transform clearPos = NoGUI::Transform(inputPos.position, (Vector2){60, inputPos.radius.y}, inputPos.origin);
	Vector2 centerBottomRight = centerPos.pos(NoGUI::Align(1, 1));
	NoGUI::Transform submitPos = NoGUI::Transform((Vector2){centerBottomRight.x - 8, centerBottomRight.y - 8}, (Vector2){50, 50}, NoGUI::Align(1, 1));
	NoGUI::Transform delPos = NoGUI::Transform(submitPos.position, (Vector2){submitPos.width(), submitPos.radius.y}, submitPos.origin);
	Vector2 centerTopRight = centerPos.pos(NoGUI::Align(1, -1));
	NoGUI::Transform closePos = NoGUI::Transform(centerTopRight, (Vector2){15, 15}, NoGUI::Align(1, -1));
	Vector2 centerBottomLeft = centerPos.pos(NoGUI::Align(-1, 1));
	NoGUI::Transform cancelPos = NoGUI::Transform((Vector2){centerBottomLeft.x + 8, centerBottomLeft.y - 8}, (Vector2){submitPos.radius.x * 2, submitPos.radius.y}, NoGUI::Align(-1, 1));
	NoGUI::Transform cancelPosSmall = NoGUI::Transform((Vector2){centerBottomLeft.x + 8, centerBottomLeft.y - 8}, submitPos.radius, NoGUI::Align(-1, 1));
	
	std::shared_ptr< NoGUI::CContainer > components = std::make_shared< NoGUI::CContainer >();
	components->addComponent< NoGUI::CText >(outFill);
	NoGUI::Page elemPg = NoGUI::Page();
	elemPg.addComponents("Default", components);
	elemPg.addComponents("addTag", components);
	std::shared_ptr< NoGUI::Element > startElem = elemPg.addElement(button, startPos, "Default", "Default");
	addTagID = elemPg.size();
	std::shared_ptr< NoGUI::Element > addTag = elemPg.addElement(button, tagButtonPos, "addTag", "+");
	std::shared_ptr< NoGUI::Element > addElem = elemPg.addElement(button, elemButtonPos, "Default", "+");
	
	std::shared_ptr< NoGUI::CContainer > inputField = std::make_shared< NoGUI::CContainer >();
	inputField->addComponent< NoGUI::CText >(outFill);
	inputField->addComponent< NoGUI::CInput >(NoMAD::TAGBUFF);
	std::shared_ptr< NoGUI::CContainer > limitText = std::make_shared< NoGUI::CContainer >();
	limitText->addComponent< NoGUI::CText >(outFill, nullptr, 30.0f, NoGUI::Align(), NoGUI::Wrap::DOWN, 0.0f, (Vector2){10, 0});
	NoGUI::Page inputPg = NoGUI::Page(false);
	inputPg.addComponents("TextBox", components);
	inputPg.addComponents("CharLimit", limitText);
	inputPg.addComponents("TagButton", components);
	inputPg.addComponents("Close", components);
	inputPg.addComponents("Tag", inputField);
	std::shared_ptr< NoGUI::Element > box = inputPg.addElement(rect, centerPos, "Container");
	std::shared_ptr< NoGUI::Element > textBox = inputPg.addElement(noShape, textPos, "TextBox", "Enter new tag for map entry:");
	std::shared_ptr< NoGUI::Element > charLimit = inputPg.addElement(noShape, centerPos, "CharLimit", "0/50");
	tagInputID = inputPg.size();
	std::shared_ptr< NoGUI::Element > tagInput = inputPg.addElement(inputShape, inputPos, "Tag");
	std::shared_ptr< NoGUI::Element > submitButton = inputPg.addElement(buttonShape, submitPos, "TagButton", "Submit");
	std::shared_ptr< NoGUI::Element > closeInputButton = inputPg.addElement(closeShape, closePos, "Close", "X");
	std::shared_ptr< NoGUI::Element > cancelInput = inputPg.addElement(buttonShape, cancelPosSmall, "Close", "Cancel");
	inputPg.update();
	
	NoGUI::Page popPg = NoGUI::Page(false);
	popPg.addComponents("Container", components);
	popPg.addComponents("DeleteButton", components);
	popPg.addComponents("Close", components);
	popPg.addComponents("ClearButton", components);
	std::shared_ptr< NoGUI::Element > popup = popPg.addElement(rect, centerPos, "Container", "Are you sure you want to DELETE element?");
	std::shared_ptr< NoGUI::Element > delButton = popPg.addElement(buttonShape, delPos, "DeleteButton", "Yes");
	std::shared_ptr< NoGUI::Element > closePopButton = popPg.addElement(closeShape, closePos, "Close", "X");
	std::shared_ptr< NoGUI::Element > cancelPopup = popPg.addElement(buttonShape, cancelPos, "Close", "Cancel");
	std::shared_ptr< NoGUI::Element > clearAll = popPg.addElement(closeShape, clearPos, "ClearButton", "Clear All");
	popPg.update();
	
	InitWindow(window.x, window.y, "test");
	SetTargetFPS(60);
	while ( !WindowShouldClose() )
	{
		if ( IsKeyPressed(KEY_DELETE) )
		{
			elemPg.clearElements();
			popPg.setActive(false);
			inputPg.setActive(false);
		}
		
		BeginDrawing();
			ClearBackground(BLACK);
			elemPg.update();
			for (auto elem : elemPg.getElements())
			{
				elem->isHover();
				if ( elemPg.getActive() )
				{
					if ( TextIsEqual(elem->getTag(), "addTag") )
					{
						if ( elem->getHover() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
						{
							inputPg.setActive(!inputPg.getActive());
						}
					}
					else if ( TextIsEqual(elem->getInner(), "+") )
					{
						if ( elem->getHover() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
						{
							NoGUI::Transform newPos = *(elem);
							elem->translate(elem->width() + 20, 0);
							std::shared_ptr< NoGUI::Element > newElem = elemPg.addElement(button, newPos, elem->getTag(), elem->getTag());
						}
					}
					else
					{
						if ( elem->getHover() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
						{
							if ( !popPg.getActive() )
							{
								popPg.setActive(true);
								toDel = elem->getId();
								SetMousePosition(window.x / 2, window.y / 2);
							}
						}
					}
				}
				elem->draw();
			}
			if ( inputPg.getActive() )
			{
				elemPg.setActive(false);
				for (auto elem : inputPg.getElements())
				{
					elem->isHover();
					charLimit->setInner(TextFormat("%i/%i", tagInput->components->getComponent< NoGUI::CInput >().i, NoMAD::TAGBUFF));
					if ( TextIsEqual(elem->getTag(), "TagButton") )
					{
						if ( elem->getHover() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
						{
							// create new element
							bool isUnique = true;
							const char* newTag = inputPg.getElement(tagInputID)->getInner();
							for (const char* string : stringsEntered)
							{
								if ( TextIsEqual(string, newTag) )
								{
									isUnique = false;
									
									break;
								}
							}
							if ( isUnique )
							{
								NoGUI::Transform newPos = *(elemPg.getElement(addTagID));
								elemPg.addComponents(newTag, components);
								std::shared_ptr< NoGUI::Element > newTagElem = elemPg.addElement(button, newPos, newTag, newTag);
								stringsEntered.push_back(newTagElem->getInner());
								// create new button
								NoGUI::Transform buttonPos = newPos;
								buttonPos.translate(newPos.width() + 20, 0);
								std::shared_ptr< NoGUI::Element > newButton = elemPg.addElement(button, buttonPos, newTag, "+");
								// reset
								tagInput->getShape()->fill = buttonFill;
								addTag->translate(0, addTag->height() + 20);
								tagInput->setInner("");
								textBox->setInner("Enter new tag for map entry:");
								tagInput->components->getComponent< NoGUI::CInput >().i = 0;
								inputPg.setActive(false);
								elemPg.setActive(true);
							}
							else
							{
								tagInput->getShape()->fill = badEntryFill;
								textBox->setInner("Tags MUST be unique!");
							}
						}
					}
					if ( TextIsEqual(elem->getTag(), "Close") )
					{
						if ( elem->getHover() && IsMouseButtonReleased(MOUSE_LEFT_BUTTON) )
						{
							inputPg.setActive(false);
							elemPg.setActive(true);
						}
					}
					elem->draw();
				}
			}
			if ( popPg.getActive() )
			{
				elemPg.setActive(false);
				for (auto elem : popPg.getElements())
				{
					elem->isHover();
					if ( TextIsEqual(elem->getTag(), "Close") )
					{
						if ( elem->getHover() && IsMouseButtonReleased(MOUSE_LEFT_BUTTON) )
						{
							popPg.setActive(false);
							elemPg.setActive(true);
						}
					}
					if ( TextIsEqual(elem->getTag(), "DeleteButton") )
					{
						if ( elem->getHover() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
						{
							std::shared_ptr< NoGUI::Element > elemToDel = elemPg.getElement(toDel);
							std::vector< std::shared_ptr< NoGUI::Element > > vec = elemPg.getElements(elemToDel->getTag());
							elemPg.removeElement(toDel); // would be more efficient to call kill on elemToDel directly but this is for testing
							for (auto e : vec)
							{
								if ( TextIsEqual(e->getInner(), "+") || e->getId() > toDel )
								{
									e->translate(elemSize.x * -2 - 20, 0);
								}
							}
							popPg.setActive(false);
							elemPg.setActive(true);
						}
					}
					if ( TextIsEqual(elem->getTag(), "ClearButton") )
					{
						if ( elem->getHover() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
						{
							const char* tagToDel = elemPg.getElement(toDel)->getTag();
							NoGUI::Transform replacePos = *(elemPg.getElement(toDel));
							replacePos.position.x = startPos.position.x;
							elemPg.removeElements(tagToDel);
							elemPg.addElement(button, replacePos, tagToDel, "+");
							popPg.setActive(false);
							elemPg.setActive(true);
						}	
					}
					elem->draw();
				}
			}
		EndDrawing();
	}
	
	return 0;
}