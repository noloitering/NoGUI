#pragma once

#include "Core.h"
#include "Component.h"

#include "rlgl.h"

namespace NoGUI
{
	class Element : public NoMAD::GameObj
	{
	protected:
		bool active = true; // logic switch
		bool focus = false; // programmable state
		Transform transform;
		std::shared_ptr< Shape > shape;
	public:
		Element(const size_t& num, std::shared_ptr< Shape > style, const char* type="Default", const char* in="", const Align& origin=Align::CENTER, const Vector2& pos={0.0f, 0.0f}, const Vector2& size={0.0f, 0.0f}, float rotation=0.0f)
			: GameObj(num, type, in), transform(pos, size, origin, rotation), shape(style) {}
		virtual bool isFocus();
		bool getFocus();
		bool getActive();
		Transform getTransform();
		Vector2 pos(const Align& origin);
		Vector2 size();
		Align alignment();
		float rotation();
		Vector2 repos(const Vector2& newPos);
		Vector2 repos(const Vector2& newPos, const Align& origin, bool update=false);
		Vector2 resize(const Vector2& size);
		void rotate(float degrees, const Align& origin=Align::CENTER);
		void rotate(float degrees, const Vector2& origin);
	};
	
	void DrawShape(const Transform& transform, const Shape& shape);
	void DrawShape(const Vector2& pos, const Vector2& radius, const Shape& shape, const Align& origin=Align::CENTER, float angle=0);
	void DrawShape(int posX, int posY, float radiusH, float radiusV, const Shape& shape, const Align& origin=Align::CENTER, float angle=0);
	void DrawShapeCenter(const Vector2& pos, const Vector2& radius, const Shape& shape, float angle=0);
	void DrawShapeCenter(int posX, int posY, float radiusH, float radiusV, const Shape& shape, float angle=0);
	void DrawShapeLeft(const Vector2& pos, const Vector2& radius, const Shape& shape, float angle=0);
	void DrawShapeLeft(int posX, int posY, float radiusH, float radiusV, const Shape& shape, float angle=0);
	void DrawShapeRight(const Vector2& pos, const Vector2& radius, const Shape& shape, float angle=0);
	void DrawShapeRight(int posX, int posY, float radiusH, float radiusV, const Shape& shape, float angle=0);
	void DrawShapeTop(const Vector2& pos, const Vector2& radius, const Shape& shape, float angle=0);
	void DrawShapeTop(int posX, int posY, float radiusH, float radiusV, const Shape& shape, float angle=0);
	void DrawShapeBottom(const Vector2& pos, const Vector2& radius, const Shape& shape, float angle=0);
	void DrawShapeBottom(int posX, int posY, float radiusH, float radiusV, const Shape& shape, float angle=0);
	void DrawShapeBottomL(const Vector2& pos, const Vector2& radius, const Shape& shape, float angle=0);
	void DrawShapeBottomL(int posX, int posY, float radiusH, float radiusV, const Shape& shape, float angle=0);
	void DrawShapeBottomR(const Vector2& pos, const Vector2& radius, const Shape& shape, float angle=0);
	void DrawShapeBottomR(int posX, int posY, float radiusH, float radiusV, const Shape& shape, float angle=0);
	void DrawPolyEx(Vector2 center, int sides, Vector2 radius, float angle=0, Color col=RAYWHITE);
	void DrawElipsePro(int centerX, int centerY, float radiusH, float radiusV, float angle=0, Color col=RAYWHITE);
}