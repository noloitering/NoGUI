#pragma once
#include "Core.h"
#include "Component.h"
//#include "rlgl.h"

namespace NoGUI
{
	class Element : public NoMAD::GameObj, public NoGUI::Transform
	{
	protected:
		bool active = true; // logic switch
		bool focus = false; // programmable state
		std::shared_ptr< nShape > shape;
	public:
		Element(const size_t& num, std::shared_ptr< nShape > style, const char* type="Default", const char* in="", const Align& origin=Align(), const Vector2& pos={0.0f, 0.0f}, const Vector2& size={0.0f, 0.0f}, float rotation=0.0f)
			: GameObj(num, type, in), Transform(pos, size, origin, rotation), shape(style) {}
		Element(const size_t& num, std::shared_ptr< nShape > style, const Transform& dimension, const char* type="Default", const char* in="")
			: GameObj(num, type, in), Transform(dimension), shape(style) {}
		virtual void draw();
		bool getFocus();
		bool getActive();
		std::shared_ptr< nShape > style(); // TODO: better name
	};
	
	void DrawShape(const nShape& shape, Vector2 center, Vector2 radius, Vector2 origin={0, 0}, float angle=0);
	void DrawShape(const nShape& shape, const NoGUI::Transform& transform);
	void DrawElement(Element* elem);
}