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
	NoGUI::CText leftWrapText = leftText;
	leftWrapText.wrap = NoGUI::TextWrap::DOWN;
	NoGUI::CText botLeftText = leftText;
	botLeftText.align = NoGUI::TextAlign::BOTTOML;
	botLeftText.wrap = NoGUI::TextWrap::UP;
	NoGUI::CText rightText = leftText;
	rightText.align = NoGUI::TextAlign::RIGHT;
	NoGUI::CText rightWrapText = rightText;
	rightWrapText.wrap = NoGUI::TextWrap::DOWN;
	NoGUI::CText botRightText = leftText;
	botRightText.align = NoGUI::TextAlign::BOTTOMR;
	botRightText.wrap = NoGUI::TextWrap::UP;
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
	
	std::shared_ptr< NoGUI::Element > left = manager.addElement< NoGUI::Element >(leftStyle, "Left", "Label");
	std::shared_ptr< NoGUI::Element > top = manager.addElement< NoGUI::Element >(topStyle, "Top", "Label");
	std::shared_ptr< NoGUI::Element > right = manager.addElement< NoGUI::Element >(rightStyle, "Right", "Label");
	std::shared_ptr< NoGUI::Element > leftWrap = manager.addElement< NoGUI::Element >(leftWrapStyle, "Left wrap down", "Label");
	std::shared_ptr< NoGUI::Element > center = manager.addElement< NoGUI::Element >(centerStyle, "Center", "Label");
	std::shared_ptr< NoGUI::Element > rightWrap = manager.addElement< NoGUI::Element >(rightWrapStyle, "Right wrap down", "Label");
	std::shared_ptr< NoGUI::Element > bottomLeft = manager.addElement< NoGUI::Element >(botLeftStyle, "Bottom Left wrap up", "Label");
	std::shared_ptr< NoGUI::Element > bottom = manager.addElement< NoGUI::Element >(bottomStyle, "Bottom", "Label");
	std::shared_ptr< NoGUI::Element > bottomRight = manager.addElement< NoGUI::Element >(botRightStyle, "Bottom Right wrap up", "Label");
	
	left->addComponent< NoGUI::CText >(leftText);
	top->addComponent< NoGUI::CText >(topText);
	right->addComponent< NoGUI::CText >(rightText);
	leftWrap->addComponent< NoGUI::CText >(leftWrapText);
	center->addComponent< NoGUI::CText >(centerText);
	rightWrap->addComponent< NoGUI::CText >(rightWrapText);
	bottomLeft->addComponent< NoGUI::CText >(botLeftText);
	bottom->addComponent< NoGUI::CText >(bottomText);
	bottomRight->addComponent< NoGUI::CText >(botRightText);
	
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