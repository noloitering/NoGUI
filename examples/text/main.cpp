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
	NoGUI::CText leftText = NoGUI::CText();
	leftText.wrap = NoGUI::TextWrap::AROUND;
	NoGUI::CText botLeftText = leftText;
	botLeftText.align = NoGUI::TextAlign::BOTTOML;
	NoGUI::CText rightText = leftText;
	rightText.align = NoGUI::TextAlign::RIGHT;
	NoGUI::CText botRightText = leftText;
	botRightText.align = NoGUI::TextAlign::BOTTOMR;
	NoGUI::CText topText = leftText;
	topText.align = NoGUI::TextAlign::TOP;
	NoGUI::CText centerText = leftText;
	centerText.align = NoGUI::TextAlign::CENTER;
	NoGUI::CText bottomText = leftText;
	bottomText.align = NoGUI::TextAlign::BOTTOM;
	
	NoGUI::Style leftStyle = {BLACK, GRAY, (Vector2){102, 155}, (Vector2){50, 50}, 4, 0, 0};
	NoGUI::Style topStyle = {BLACK, GRAY, (Vector2){center.x, 155}, (Vector2){50, 50}, 4, 0, 0};
	NoGUI::Style rightStyle = {BLACK, GRAY, (Vector2){368, 155}, (Vector2){50, 50}, 4, 0, 0};
	NoGUI::Style leftWrapStyle = {BLACK, GRAY, (Vector2){102, 360}, (Vector2){50, 50}, 4, 0, 0};
	NoGUI::Style centerStyle = {BLACK, GRAY, (Vector2){center.x, 360}, (Vector2){50, 50}, 4, 0, 0};
	NoGUI::Style rightWrapStyle = {BLACK, GRAY, (Vector2){368, 360}, (Vector2){50, 50}, 4, 0, 0};
	NoGUI::Style botLeftStyle = {BLACK, GRAY, (Vector2){102, 565}, (Vector2){50, 50}, 4, 0, 0};
	NoGUI::Style bottomStyle = {BLACK, GRAY, (Vector2){center.x, 565}, (Vector2){50, 50}, 4, 0, 0};
	NoGUI::Style botRightStyle = {BLACK, GRAY, (Vector2){368, 565}, (Vector2){50, 50}, 4, 0, 0};
	
	std::shared_ptr< NoGUI::Element > left = manager.addElement< NoGUI::Element >(leftStyle, "Label", "Left");
	std::shared_ptr< NoGUI::Element > top = manager.addElement< NoGUI::Element >(topStyle, "Label", "Top");
	std::shared_ptr< NoGUI::Element > right = manager.addElement< NoGUI::Element >(rightStyle, "Label", "Right");
	std::shared_ptr< NoGUI::Element > leftWrap = manager.addElement< NoGUI::Element >(leftWrapStyle, "Label", "Left wrap down");
	std::shared_ptr< NoGUI::Element > center = manager.addElement< NoGUI::Element >(centerStyle, "Label", "Center");
	std::shared_ptr< NoGUI::Element > rightWrap = manager.addElement< NoGUI::Element >(rightWrapStyle, "Label", "Right wrap down");
	std::shared_ptr< NoGUI::Element > bottomLeft = manager.addElement< NoGUI::Element >(botLeftStyle, "Label", "Bottom Left wrap up");
	std::shared_ptr< NoGUI::Element > bottom = manager.addElement< NoGUI::Element >(bottomStyle, "Label", "Bottom");
	std::shared_ptr< NoGUI::Element > bottomRight = manager.addElement< NoGUI::Element >(botRightStyle, "Label", "Bottom Right wrap up");
	
	left->components->addComponent< NoGUI::CText >(leftText);
	top->components->addComponent< NoGUI::CText >(topText);
	right->components->addComponent< NoGUI::CText >(rightText);
	leftWrap->components->addComponent< NoGUI::CText >(leftText);
	center->components->addComponent< NoGUI::CText >(centerText);
	rightWrap->components->addComponent< NoGUI::CText >(rightText);
	bottomLeft->components->addComponent< NoGUI::CText >(botLeftText);
	bottom->components->addComponent< NoGUI::CText >(bottomText);
	bottomRight->components->addComponent< NoGUI::CText >(botRightText);
	
	manager.update();
	
	while ( !WindowShouldClose() )
	{
		BeginDrawing();
			ClearBackground(GRAY);
			manager.render();
		EndDrawing();
	}

	return 0;
}