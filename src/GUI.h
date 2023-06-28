#pragma once
#include "Core.h"
#include "Component.h"
#include "raymath.h"

namespace NoGUI
{
	class Transform
	{
	public:
		Transform(const Vector2& p, const Vector2& radi, const Align& a, float r=0)
			: position(p), radius(radi), origin(a), angle(r) {}
		Vector2 position;
		Vector2 radius;
		Align origin;
		float angle = 0;
		Vector2 pos() const; // current position
		Vector2 pos(const Align& originPoint) const; // theoritical position at given unit coordnite
		Vector2 size() const; // full dimensions (width, height)
		float width() const; 
		float height() const;
		float rotation() const; // current angle of rotation
		Vector2 offset() const; // distance from center of transform
		Vector2 translate(float x, float y); // add to position
		Vector2 translate(const Vector2 inc); // add to position
		Vector2 repos(Vector2 newPos); // move to position
		Vector2 repos(Vector2 newPos, const Align& originPoint, bool update=false); // move to position
		void resize(const Vector2& size);
		void rotate(float degrees, const Align& originPoint, bool update=false); // rotate around relative point
		void rotate(float degrees, const Vector2& originPoint); // rotate around absolute point
		void reorient(float degrees, const Align& originPoint, bool update=false);
		void reorient(float degrees, const Vector2& originPoint);
	};
	
	class Element : public NoMAD::GameObj, public NoGUI::Transform
	{
	protected:
		bool active = true; // logic switch
		bool focus = false; // programmable state
		std::shared_ptr< nShape > shape;
	public:
		Element(const size_t& num, std::shared_ptr< nShape > style, const Vector2& pos={0.0f, 0.0f}, const Vector2& size={0.0f, 0.0f}, float rotation=0.0f, const Align& origin=Align(), std::shared_ptr< CContainer > c=nullptr, const char* type="Default", const char* in="")
			: GameObj(num, type, in), Transform(pos, size, origin, rotation), shape(style), components(c) {}
		Element(const size_t& num, std::shared_ptr< nShape > style, const Transform& dimension, std::shared_ptr< CContainer > c=nullptr, const char* type="Default", const char* in="")
			: GameObj(num, type, in), Transform(dimension), shape(style), components(c) {}
		virtual void draw();
		std::shared_ptr< CContainer > components;
		bool getFocus(); 
		bool getActive();
		std::shared_ptr< nShape > style(); // TODO: better name
	};
	
	void DrawShape(const nShape& shape, Vector2 center, Vector2 radius, Vector2 origin={0, 0}, float angle=0);
	void DrawShape(const nShape& shape, const NoGUI::Transform& transform);
	void DrawCImageCropped(CImage& img, std::shared_ptr< nShape > shape, const NoGUI::Transform& transform);
	void DrawCImageFitted(CImage& img, std::shared_ptr< nShape > shape, const NoGUI::Transform& transform);
	void DrawCImageShaped(CImage& img, const NoGUI::Transform& transform, std::shared_ptr< nShape > shape);
	void DrawCImage(CImage& img, std::shared_ptr< nShape > shape, const NoGUI::Transform& transform);
	void DrawScrollBars(std::shared_ptr< nShape > bar, std::shared_ptr< nShape > cursor, const NoGUI::Transform& transform, const Vector2& scrollPos, const Vector2& percentShown, float size);
	void DrawElement(Element* elem);
}