#include "../../../../src/GUI.h"

int main(int argc, char ** argv)
{
	// initialization
	Vector2 window = {1280, 720};
	InitWindow(window.x, window.y, "test");
	SetTargetFPS(60);
	std::vector< std::shared_ptr< NoGUI::Element > > elemVec;
	
	Vector2 arrowSize = {35, 35};
	Vector2 baseSize = {50, 25};
	Vector2 polySize = {75, 75};
	
	std::shared_ptr< NoGUI::Fill > fill = std::make_shared< NoGUI::Fill >(WHITE, GREEN);
	std::shared_ptr< NoGUI::Fill > outlineFill = std::make_shared< NoGUI::Fill >(GRAY);
	std::shared_ptr< NoGUI::Outline > outline = std::make_shared< NoGUI::Outline >(outlineFill);
	
	std::shared_ptr< NoGUI::nShape > rect = std::make_shared< NoGUI::nShape >(4, fill, outline);
	std::shared_ptr< NoGUI::nShape > triangle = std::make_shared< NoGUI::nShape >(3, fill, outline);
	std::shared_ptr< NoGUI::nShape > circle = std::make_shared< NoGUI::nShape >(0, fill, outline);
	std::shared_ptr< NoGUI::nShape > pentagon = std::make_shared< NoGUI::nShape >(5, fill, outline);
	std::shared_ptr< NoGUI::nShape > secagon = std::make_shared< NoGUI::nShape >(6, fill, outline);
	std::shared_ptr< NoGUI::nShape > septagon = std::make_shared< NoGUI::nShape >(7, fill, outline);
	std::shared_ptr< NoGUI::nShape > octagon = std::make_shared< NoGUI::nShape >(8, fill, outline);
	
	NoGUI::Transform rightBaseT = NoGUI::Transform((Vector2){window.x / 8, window.y / 2}, baseSize, NoGUI::Align(0, 0));
	NoGUI::Transform leftBaseT = NoGUI::Transform((Vector2){window.x - window.x / 8, window.y / 2}, baseSize, NoGUI::Align(0, 0));
	NoGUI::Transform centerT = NoGUI::Transform((Vector2){window.x / 2, window.y / 2}, polySize, NoGUI::Align(0, 0));
	NoGUI::Transform rightArrowT = NoGUI::Transform((Vector2){arrowSize.x, 0}, arrowSize, NoGUI::Align(1, 0), 90);
	NoGUI::Transform leftArrowT = NoGUI::Transform((Vector2){arrowSize.x * -1, 0}, arrowSize, NoGUI::Align(-1, 0), -90);
	NoGUI::Transform topT = NoGUI::Transform((Vector2){0, -1 * polySize.y}, polySize, NoGUI::Align(0, -1));
	NoGUI::Transform bottomT = NoGUI::Transform((Vector2){0, polySize.y}, polySize, NoGUI::Align(0, 1));
	NoGUI::Transform leftT = NoGUI::Transform((Vector2){polySize.x * -1, 0}, polySize, NoGUI::Align(-1, 0));
	NoGUI::Transform rightT = NoGUI::Transform((Vector2){polySize.x, 0}, polySize, NoGUI::Align(1, 0));
	
	std::shared_ptr< NoGUI::CContainer > rightArrowComps = std::make_shared< NoGUI::CContainer >();
	std::shared_ptr< NoGUI::CContainer > leftArrowComps = std::make_shared< NoGUI::CContainer >();
	std::shared_ptr< NoGUI::CContainer > centerComps = std::make_shared< NoGUI::CContainer >();
	NoGUI::CMultiShape& rightArrowShapes = rightArrowComps->addComponent< NoGUI::CMultiShape >();
	NoGUI::CMultiShape& leftArrowShapes = leftArrowComps->addComponent< NoGUI::CMultiShape >();
	NoGUI::CMultiShape& centerShapes = centerComps->addComponent< NoGUI::CMultiShape >();
	rightArrowShapes.shapes.push_back(std::pair< std::shared_ptr< NoGUI::nShape >, NoGUI::Transform >(triangle, rightArrowT));
	leftArrowShapes.shapes.push_back(std::pair< std::shared_ptr< NoGUI::nShape >, NoGUI::Transform >(triangle, leftArrowT));
	centerShapes.shapes.push_back(std::pair< std::shared_ptr< NoGUI::nShape >, NoGUI::Transform >(pentagon, topT));
	centerShapes.shapes.push_back(std::pair< std::shared_ptr< NoGUI::nShape >, NoGUI::Transform >(secagon, rightT));
	centerShapes.shapes.push_back(std::pair< std::shared_ptr< NoGUI::nShape >, NoGUI::Transform >(septagon, bottomT));
	centerShapes.shapes.push_back(std::pair< std::shared_ptr< NoGUI::nShape >, NoGUI::Transform >(octagon, leftT));
	
	std::shared_ptr< NoGUI::Element > rightArrow = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, rightBaseT, rightArrowComps, "pointRight");
	std::shared_ptr< NoGUI::Element > leftArrow = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, rect, leftBaseT, leftArrowComps, "pointLeft");
	std::shared_ptr< NoGUI::Element > centerShape = std::make_shared< NoGUI::Element >(NoMAD::OBJCOUNT, circle, centerT, centerComps, "spinner");
	elemVec.push_back(rightArrow);
	elemVec.push_back(leftArrow);
	elemVec.push_back(centerShape);
	
	while ( !WindowShouldClose() )
	{
		bool toggleCollision = false;
		bool rLeft = false;
		bool rRight = false;
		float translateX = 0.0f;
		float translateY = 0.0f;
		if ( IsKeyPressed( KEY_SPACE ) )
		{
			toggleCollision = true;
		}
		if ( IsMouseButtonDown(MOUSE_LEFT_BUTTON) )
		{
			rLeft = true;
		}
		else if ( IsMouseButtonDown(MOUSE_RIGHT_BUTTON) )
		{
			rRight = true;
		}
		if ( IsKeyDown(KEY_UP) || IsKeyDown(KEY_W) )
		{
			translateY -= 1.0f;
		}
		else if ( IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S) )
		{
			translateY += 1.0f;
		}
		if ( IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A) )
		{
			translateX -= 1.0f;
		}
		else if ( IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D) )
		{
			translateX += 1.0f;
		}
		
		BeginDrawing();
			ClearBackground(BLACK);
			for ( std::shared_ptr< NoGUI::Element > elem : elemVec )
			{
				NoGUI::CMultiShape& multiShape = elem->components->getComponent< NoGUI::CMultiShape >();
				if ( multiShape.active && toggleCollision )
				{
					multiShape.collision = !multiShape.collision;
				}
				if ( rLeft )
				{
					if ( !TextIsEqual(elem->getTag(), "pointRight") )
					{
						elem->rotate(-1, NoGUI::Align(0, 0));
					}
					else
					{
						elem->rotate(1, NoGUI::Align(0, 0));
					}
				}
				else if ( rRight )
				{
					if ( !TextIsEqual(elem->getTag(), "pointRight") )
					{
						elem->rotate(1, NoGUI::Align(0, 0));
					}
					else
					{
						elem->rotate(-1, NoGUI::Align(0, 0));
					}
				}
				if ( TextIsEqual(elem->getTag(), "pointRight") )
				{
					elem->translate(translateX, translateY);
				}
				else if ( TextIsEqual(elem->getTag(), "pointLeft") )
				{
					elem->translate(translateX * -1, translateY);
				}
				elem->draw();
				elem->isHover();
			}
		EndDrawing();
	}
	return 0;
}