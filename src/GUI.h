#pragma once
#include "Core.h"
#include "Component.h"
#include "Observer.h"
#include "raymath.h"

namespace NoGUI
{
	class Transform
	{
	public:
		Transform(const Vector2& p=(Vector2){0, 0}, const Vector2& radi=(Vector2){0, 0}, const Align& a=Align(), float r=0)
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
	friend class Manager;
	friend class ManagerGrid;
	protected:
		bool active = true; // logic switch
		bool alive = true; // to be or not to be
		bool focus = false; // programmable state
		bool hover = false; // mouse hover
		std::shared_ptr< nShape > shape;
	public:
		Element(const size_t& num, std::shared_ptr< nShape > style, const Vector2& pos={0.0f, 0.0f}, const Vector2& size={0.0f, 0.0f}, float rotation=0.0f, const Align& origin=Align(), const char* type="Default", const char* in="", std::shared_ptr< CContainer > c=nullptr)
			: GameObj(num, type, in), Transform(pos, size, origin, rotation), shape(style), components(c) {}
		Element(const size_t& num, std::shared_ptr< nShape > style, const Transform& dimensions, const char* type="Default", const char* in="", std::shared_ptr< CContainer > c=nullptr)
			: GameObj(num, type, in), Transform(dimensions), shape(style), components(c) {}
		virtual void draw();
		virtual bool isFocus();
		std::shared_ptr< CContainer > components;
		std::shared_ptr< nShape > getShape();
		std::shared_ptr< nShape > setShape(std::shared_ptr< nShape > set);
		bool getActive();
		bool getFocus();
		bool getHover();
		bool getAlive();
		bool isHover();
		bool setActive(bool set);
		bool setFocus(bool set);
		void kill();
	};
	
	class Button : public Element
	{
	public:
		Button(const size_t& num, std::shared_ptr< nShape > style, const Vector2& pos={0.0f, 0.0f}, const Vector2& size={0.0f, 0.0f}, float rotation=0.0f, const Align& origin=Align(), const char* type="Default", const char* in="", std::shared_ptr< CContainer > c=nullptr)
			: Element(num, style, pos, size, rotation, origin, type, in, c) {}
		Button(const size_t& num, std::shared_ptr< nShape > style, const Transform& dimensions, const char* type="Default", const char* in="", std::shared_ptr< CContainer > c=nullptr)
			: Element(num, style, dimensions, type, in, c) {}
		bool isFocus();
	};
	
	class Hoverable : public Element
	{
	public:
		Hoverable(const size_t& num, std::shared_ptr< nShape > style, const Vector2& pos={0.0f, 0.0f}, const Vector2& size={0.0f, 0.0f}, float rotation=0.0f, const Align& origin=Align(), const char* type="Default", const char* in="", std::shared_ptr< CContainer > c=nullptr)
			: Element(num, style, pos, size, rotation, origin, type, in, c) {}
		Hoverable(const size_t& num, std::shared_ptr< nShape > style, const Transform& dimensions, const char* type="Default", const char* in="", std::shared_ptr< CContainer > c=nullptr)
			: Element(num, style, dimensions, type, in, c) {}
		bool isFocus();
	};
	
	class Toggle : public Element
	{
	public:
		Toggle(const size_t& num, std::shared_ptr< nShape > style, const Vector2& pos={0.0f, 0.0f}, const Vector2& size={0.0f, 0.0f}, float rotation=0.0f, const Align& origin=Align(), const char* type="Default", const char* in="", std::shared_ptr< CContainer > c=nullptr)
			: Element(num, style, pos, size, rotation, origin, type, in, c) {}
		Toggle(const size_t& num, std::shared_ptr< nShape > style, const Transform& dimensions, const char* type="Default", const char* in="", std::shared_ptr< CContainer > c=nullptr)
			: Element(num, style, dimensions, type, in, c) {}
		bool isFocus();
	};
	
	class Trigger : public Element
	{
	public:
		Trigger(const size_t& num, std::shared_ptr< nShape > style, const Vector2& pos={0.0f, 0.0f}, const Vector2& size={0.0f, 0.0f}, float rotation=0.0f, const Align& origin=Align(), const char* type="Default", const char* in="", std::shared_ptr< CContainer > c=nullptr)
			: Element(num, style, pos, size, rotation, origin, type, in, c) {}
		Trigger(const size_t& num, std::shared_ptr< nShape > style, const Transform& dimensions, const char* type="Default", const char* in="", std::shared_ptr< CContainer > c=nullptr)
			: Element(num, style, dimensions, type, in, c) {}
		bool isFocus();
	};
	
	class CheckBox : public Toggle
	{
	public:
		CheckBox(const size_t& num, std::shared_ptr< nShape > style, const Vector2& pos={0.0f, 0.0f}, const Vector2& size={0.0f, 0.0f}, float rotation=0.0f, const Align& origin=Align(), const char* type="Default", const char* in="", std::shared_ptr< CContainer > c=nullptr)
			: Toggle(num, style, pos, size, rotation, origin, type, in, c) {}
		CheckBox(const size_t& num, std::shared_ptr< nShape > style, const Transform& dimensions, const char* type="Default", const char* in="", std::shared_ptr< CContainer > c=nullptr)
			: Toggle(num, style, dimensions, type, in, c) {}
		void draw();
	};
	
	class Slider : public Trigger
	{
	protected:
		std::shared_ptr< nShape > slide;
		Transform slideTransform;
	public:
		Slider(const size_t& num, std::shared_ptr< nShape > style, const Vector2& pos={0.0f, 0.0f}, const Vector2& size={0.0f, 0.0f}, float rotation=0.0f, const Align& origin=Align(), const char* type="Default", const char* in="", std::shared_ptr< CContainer > c=nullptr, std::shared_ptr< nShape > slideStyle=nullptr, const Align& slideAlign=Align(-1, 0))
			: Trigger(num, style, pos, size, rotation, origin, type, in, c)
			{
				if ( slideStyle ) 
				{ 
					slide = slideStyle;
				}
				else 
				{
					slide = std::make_shared< nShape >(style->n, std::make_shared< Fill >(style->fill->col, style->fill->hoverCol), style->outline);
				}
				slideTransform = Transform((Vector2){0, 0}, (Vector2){0.0f, size.y}, slideAlign);
			}
		Slider(const size_t& num, std::shared_ptr< nShape > style, const Transform& dimensions, const char* type="Default", const char* in="", std::shared_ptr< CContainer > c=nullptr, std::shared_ptr< nShape > slideStyle=nullptr, const Align& slideAlign=Align(-1, 0))
			: Trigger(num, style, dimensions, type, in, c)
			{
				if ( slideStyle != nullptr )
				{
					slide = slideStyle;
				}
				else
				{
					slide = std::make_shared< nShape >(style->n, std::make_shared< Fill >(style->fill->col, style->fill->hoverCol), style->outline); 
				}
				slideTransform = Transform((Vector2){0, 0}, (Vector2){0.0f, dimensions.radius.y}, slideAlign);
			}
		void draw();
		bool isFocus();
		std::shared_ptr< nShape > getSlide();
		const Transform& getSlideTransform();
		void setSlide(std::shared_ptr< nShape > slideStyle);
		void setSlide(std::shared_ptr< nShape > slideStyle, const Transform& transform);
	};
	
	class Cursorer : public Slider
	{
	public:
		Cursorer(const size_t& num, std::shared_ptr< nShape > style, const Vector2& pos={0.0f, 0.0f}, const Vector2& size={0.0f, 0.0f}, float rotation=0.0f, const Align& origin=Align(), const char* type="Default", const char* in="", std::shared_ptr< CContainer > c=nullptr, std::shared_ptr< nShape > slideStyle=nullptr, const Align& slideAlign=Align(-1, 0), const Vector2& slideSize={10.0f, 10.0f})
			: Slider(num, style, pos, size, rotation, origin, type, in, c, slideStyle) 
			{
				if ( slideStyle == nullptr )
				{
					slide.reset(new nShape(0, std::make_shared< Fill >(BLUE), std::make_shared< Outline >(std::make_shared< Fill >(BLACK), 1)));
				}
				slideTransform = Transform((Vector2){0, 0}, slideSize, slideAlign);
			}
		Cursorer(const size_t& num, std::shared_ptr< nShape > style, const Transform& dimensions, const char* type="Default", const char* in="", std::shared_ptr< CContainer > c=nullptr, std::shared_ptr< nShape > slideStyle=nullptr, const Align& slideAlign=Align(-1, 0), const Vector2& slideSize={10.0f, 10.0f})
			: Slider(num, style, dimensions, type, in, c, slideStyle) 
			{
				if ( slideStyle == nullptr )
				{
					slide.reset(new nShape(0, std::make_shared< Fill >(BLUE), std::make_shared< Outline >(std::make_shared< Fill >(BLACK), 1)));
				}
				slideTransform = Transform((Vector2){0, 0}, slideSize, slideAlign);
			}
		bool isFocus();
	};
	
	class NotchedCursorer : public Cursorer
	{
	protected:
		unsigned int notches = 1;
	public:
		NotchedCursorer(const size_t& num, std::shared_ptr< nShape > style, const Vector2& pos={0.0f, 0.0f}, const Vector2& size={0.0f, 0.0f}, float rotation=0.0f, const Align& origin=Align(), const char* type="Default", const char* in="", std::shared_ptr< CContainer > c=nullptr, std::shared_ptr< nShape > slideStyle=nullptr, const Align& slideAlign=Align(-1, 0), const Vector2& slideSize={10.0f, 10.0f}, unsigned int numNotches=1)
			: Cursorer(num, style, pos, size, rotation, origin, type, in, c, slideStyle, slideAlign, slideSize) {notches = numNotches;}
		NotchedCursorer(const size_t& num, std::shared_ptr< nShape > style, const Transform& dimensions, const char* type="Default", const char* in="", std::shared_ptr< CContainer > c=nullptr, std::shared_ptr< nShape > slideStyle=nullptr, const Align& slideAlign=Align(-1, 0), const Vector2& slideSize={10.0f, 10.0f}, unsigned int numNotches=1)
			: Cursorer(num, style, dimensions, type, in, c, slideStyle, slideAlign, slideSize) {notches = numNotches;}
		bool isFocus();
		unsigned int getNotches();
		void setNotches(unsigned int notchNum);
	};
	
	class Page : public CMap // Container for Elements
	{
	protected:
		std::map< const NoMAD::ObjTag, std::vector< std::shared_ptr< Element > > > elements;
		std::map< const NoMAD::ObjTag, std::vector< std::shared_ptr< Element > > > toAdd;
		size_t total = 0; // total amount of elements ever created
		bool active = true;
	public:
		Page(bool init=true)
			: active(init) {}
		Page(std::map< const NoMAD::ObjTag, std::shared_ptr< CContainer > > comps, bool init=true)
			: CMap(comps), active(init) {}
		std::map< const NoMAD::ObjTag, std::vector< std::shared_ptr< Element > > > getBody();
		std::shared_ptr< Element > getElement(size_t id);
		std::vector< std::shared_ptr< Element > > getElements(const char* tag);
		std::vector< std::shared_ptr< Element > > getElements();
		void removeElement(size_t id);
		void removeElements(const char* tag);
		void clearElements();
		void update();
		size_t size();
		bool getActive();
		bool setActive(bool set);
		
		template <class C=Element, typename... Args>
		std::shared_ptr< C > addElement(Args&&... EArgs)
		{
			auto elem = std::shared_ptr< C >(new C(total++, std::forward<Args>(EArgs)...));
			if ( elem->components == nullptr )
			{
				std::shared_ptr< CContainer > components = getComponents(elem->getTag());
				if ( components == nullptr )
				{
					components = addComponents(elem->getTag());
				}
				elem->components = components;
			}
			toAdd[elem->getTag()].push_back(elem);
	
			return elem;
		}
	};
	
	class ContextPage : public Page
	{
	protected:
		std::shared_ptr< Element > context;
		Wrap flow = Wrap::DOWN;
	public:
		ContextPage(std::shared_ptr< Element > element, const Vector2& pos, bool init=true)
			: Page(init), context(element), position(pos) {}
		ContextPage(std::shared_ptr< Element > element, const Vector2& pos, std::map< const NoMAD::ObjTag, std::shared_ptr< CContainer > > comps, bool init=true)
			: Page(comps, init), context(element), position(pos) {}
		Vector2 position;
		std::shared_ptr< Element > getContext();
		Wrap getFlow();
		void setContext(std::shared_ptr< NoGUI::Element > element);
		void setFlow(const Wrap& wrap);
		
		template <class C=Element, typename... Args>
		std::shared_ptr< C > addElement(std::shared_ptr< nShape > style, const Vector2& radius, Args&&... EArgs)
		{
			float increment = 0.0f;
			Vector2 pos = position;
			Align alignment = context->origin;
			// TODO: check toAdd??
			std::shared_ptr< Element > lastElement = getElement(size() - 1);
			if ( style->outline )
			{
				increment += style->outline->thick / 2;
			}
			if ( lastElement )
			{
				pos = lastElement->pos(NoGUI::Align());
				std::shared_ptr< nShape > lastShape = lastElement->getShape();
				increment += lastElement->radius.y;
				if ( lastShape->outline )
				{
					increment += lastShape->outline->thick / 2;
				}
			}
			switch (flow)
			{
				case Wrap::NONE:
				{
					
					break;
				}
				
				case Wrap::DOWN:
				{
					alignment = NoGUI::Align(0, -1);
					pos.y += increment;
					
					break;
				}
				
				case Wrap::UP:
				{
					alignment = NoGUI::Align(0, 1);
					pos.y -= increment;
					
					break;
				}
				
				case Wrap::AROUND:
				{
					alignment = NoGUI::Align(0, 0);
					// TODO: circle around context
					
					break;
				}
			}
			Transform transform = Transform(pos, radius, alignment);
			auto elem = std::shared_ptr< C >(new C(total++, style, transform, std::forward<Args>(EArgs)...));
			if ( elem->components == nullptr )
			{
				std::shared_ptr< CContainer > components = getComponents(elem->getTag());
				if ( components == nullptr )
				{
					components = addComponents(elem->getTag());
				}
				elem->components = components;
			}
			toAdd[elem->getTag()].push_back(elem);
	
			return elem;
		}
	};
	
	class Manager : public Notifier // Container for Pages
	{
	friend class ManagerGrid;
	private:
		std::vector< std::shared_ptr< Page > > pages;
		bool onFocus = false;
	public:
		Manager(bool withPg=true)
		{
			if ( withPg )
			{
				addPage(true);
			}
		}
		Manager(std::shared_ptr< Page > pg)
		{
			addPage(pg);
		}
		Manager(std::vector< std::shared_ptr< Page > > pgs)
			: pages(pgs) {}
		virtual void render();
		virtual void update();
//		std::shared_ptr< Element > addElement(std::shared_ptr< nShape > style, const Transform& dimensions, const char* tag="Default", const char* inner="", size_t pageIndex=0);
		std::shared_ptr< Page > addPage(bool active=false);
		std::shared_ptr< Page > addPage(std::shared_ptr< Page > pg);
		std::shared_ptr< Page > addPage(std::map< const NoMAD::ObjTag, std::shared_ptr< CContainer > > comps, bool active=false);
		std::shared_ptr< Page > getPage(size_t pageIndex=0);
		std::vector< std::shared_ptr< Page > > getPages();
		size_t size();
//		void removeElement(size_t id, size_t pageIndex=0);
		void removePage(size_t pageIndex);
		void clear();
		void setActive(size_t index);
	};
	
	class ManagerGrid : public Manager
	{
	private:
		Vector2 cellSize = {16, 16};
	public:
		ManagerGrid(bool withPg=true, float cellX=16, float cellY=16)
			: Manager(withPg) {cellSize.x = cellX; cellSize.y = cellY;}
		ManagerGrid(std::shared_ptr< Page > pg, float cellX=16, float cellY=16)
			: Manager(pg) {cellSize.x = cellX; cellSize.y = cellY;}
		ManagerGrid(std::vector< std::shared_ptr< Page > > pgs, float cell=16)
			: Manager(pgs) {cellSize.x = cell; cellSize.y = cell;}
		void update();
		void render();
		void drawCells(const Color& col=GRAY);
		void setCellSize(float newSize);
		void setCellSize(float x, float y);
		Vector2 getCellSize();
	};
	
	// helper functions
	std::vector< std::tuple< const char*, float, unsigned int > > WrapText(const char* txt, const Font& font, float fontSize, float spacing, const NoGUI::Transform& area);
	std::vector< std::tuple< const char*, float, unsigned int > > WrapText(const char* txt, const NoGUI::CText& fmt, const NoGUI::Transform& area);
	Vector2 AlignText(const NoGUI::Align& alignment, const NoGUI::Wrap& wrap, Vector2 lineSize, int lineNum, int numLines, float lineSpacing=0);
	Vector2 AlignText(const NoGUI::CText& fmt, Vector2 lineSize, int lineNum, int numLines);
	bool CheckCollisionPointShape(Vector2 point, int sides, const Transform& area);
	void collectInput(Element* elem);
	// Drawing functions
	void DrawEllipseFill(std::shared_ptr< Fill > fill, Vector2 center, Vector2 radius, Vector2 origin={0, 0}, float angle=0, bool hovered=false);
	void DrawEllipseFill(std::shared_ptr< Fill > fill, const Transform& transform, bool hovered=false);
	void DrawPixelFill(std::shared_ptr< Fill > fill, Vector2 pos, bool hovered=false);
	void DrawPixelFill(std::shared_ptr< Fill > fill, const Transform& transform, bool hovered=false);
	void DrawLineFill(std::shared_ptr< Fill > fill, const Vector2& start, const Vector2& end, float thickness, bool hovered=false);
	void DrawLineFill(std::shared_ptr< Fill > fill, const Transform& transform, bool hovered=false);
	void DrawTriangleFill(std::shared_ptr< Fill > fill, const Vector2& v1, const Vector2& v2, const Vector2& v3, bool hovered=false);
	void DrawTriangleFill(std::shared_ptr< Fill > fill, const Transform& transform, bool hovered=false);
	void DrawRectangleFill(std::shared_ptr< Fill > fill, const Rectangle& rect, const Vector2& origin, float angle=0, bool hovered=false);
	void DrawRectangleFill(std::shared_ptr< Fill > fill, const Transform& transform, bool hovered=false);
	void DrawPolyFill(std::shared_ptr< Fill > fill, unsigned int n, const Vector2& center, const Vector2& radius, const Vector2& origin={0, 0}, float angle=0, bool hovered=false);
	void DrawPolyFill(std::shared_ptr< Fill > fill, unsigned int n, const Transform& transform, bool hovered=false);
	void DrawShapeFill(unsigned int n, std::shared_ptr< Fill > fill, Vector2 center, Vector2 radius, Vector2 origin={0, 0}, float angle=0, bool hovered=false);
	void DrawShapeFill(unsigned int n, std::shared_ptr< Fill > fill, const Transform& transform, bool hovered=false);
	void DrawEllipseOutline(std::shared_ptr< Outline > outline, Vector2 center, Vector2 radius, Vector2 origin={0, 0}, float angle=0, bool hovered=false);
	void DrawEllipseOutline(std::shared_ptr< Outline > outline, const Transform& transform, bool hovered=false);
	// void DrawPixelOutline(std::shared_ptr< Outline > outline, Vector2 pos, bool hovered=false);
	// void DrawPixelOutline(std::shared_ptr< Outline > outline, const Transform& transform, bool hovered=false);
	// void DrawLineOutline(std::shared_ptr< Outline > outline, const Vector2& start, const Vector2& end, float thickness, bool hovered=false);
	// void DrawLineOutline(std::shared_ptr< Outline > outline, const Transform& transform, bool hovered=false);
	void DrawTriangleOutline(std::shared_ptr< Outline > outline, const Vector2& v1, const Vector2& v2, const Vector2& v3, bool hovered=false);
	void DrawTriangleOutline(std::shared_ptr< Outline > outline, const Transform& transform, bool hovered=false);
	void DrawRectangleOutline(std::shared_ptr< Outline > outline, const Rectangle& rect, const Vector2& origin, float angle=0, bool hovered=false);
	void DrawRectangleOutline(std::shared_ptr< Outline > outline, const Transform& transform, bool hovered=false);
	void DrawPolyOutline(std::shared_ptr< Outline > outline, unsigned int n, const Vector2& center, const Vector2& radius, const Vector2& origin={0, 0}, float angle=0, bool hovered=false);
	void DrawPolyOutline(std::shared_ptr< Outline > outline, unsigned int n, const Transform& transform, bool hovered=false);
	void DrawShapeOutline(unsigned int n, std::shared_ptr< Outline > outline, Vector2 center, Vector2 radius, Vector2 origin={0, 0}, float angle=0, bool hovered=false);
	void DrawShapeOutline(unsigned int n, std::shared_ptr< Outline > outline, const Transform& transform, bool hovered=false);
	void DrawShape(const nShape& shape, Vector2 center, Vector2 radius, Vector2 origin={0, 0}, float angle=0, bool hovered=false);
	void DrawShape(const nShape& shape, const NoGUI::Transform& transform, bool hovered=false);
	void DrawShapeAnchored(const nShape& shape, const NoGUI::Transform& transform, const NoGUI::Transform& anchor, bool hovered=false);
	void DrawScrollBars(std::shared_ptr< nShape > bar, std::shared_ptr< nShape > cursor, const NoGUI::Transform& transform, const Vector2& scrollPos, const Vector2& percentShown, float size);
	// Components
	void DrawCTextBox(const char* txt, CTextBox& fmt, const NoGUI::Transform& transform);
	void DrawCTextBoxWrapped(const char* txt, CTextBox& fmt, const NoGUI::Transform& transform);
	void DrawCText(const char* txt, CText& fmt, const NoGUI::Transform& transform);
	void DrawCImageCropped(CImage& img, std::shared_ptr< nShape > shape, const NoGUI::Transform& transform);
	void DrawCImageFitted(CImage& img, std::shared_ptr< nShape > shape, const NoGUI::Transform& transform);
	void DrawCImageShaped(CImage& img, const NoGUI::Transform& transform, std::shared_ptr< nShape > shape);
	void DrawCImage(CImage& img, std::shared_ptr< nShape > shape, const NoGUI::Transform& transform);
	void DrawCInput(CInput& input, std::shared_ptr< Font > font, float fontSize, const char* txt, const Color& col, const Vector2& spacing, const Align& txtAlign, const Transform& transform, const Crop& cropping=Crop::NONE, float angle=0);
	void DrawCInput(CInput& input, CText& fmt, const char* txt, const NoGUI::Transform& transform);
	void DrawCInput(CInput& input, CTextBox& fmt, const char* txt, const NoGUI::Transform& transform);
	void DrawCMultiShape(const Transform& anchor, const CMultiShape& shapes, bool hovered=false);
	void DrawComponents(Components& components, std::shared_ptr< nShape > shape, const NoGUI::Transform& transform, const char* inner, bool hovered=false);
	void DrawComponents(Element* elem);
	// Elements
	void DrawElement(const NoGUI::Transform& transform, std::shared_ptr< nShape > shape, const char* inner, std::shared_ptr< NoGUI::CContainer > components=nullptr, bool hovered=false);
	void DrawElement(Element* elem);
}