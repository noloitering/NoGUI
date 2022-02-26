#pragma once

#include <iostream>
#include <string>
#include <map>
#include <tuple>
#include <limits>
#include <cstring>

#include "Component.h"
#include "Observer.h"
#include "Model.h"

namespace NoGUI
{
	// Classes
	class Element // Base Element to inherit from; Focus is manually set;
	{
	protected:
	friend class Page;
	friend class DropDown;
		Style style;
		const size_t id = 0;
		std::string tag = "Default";
		std::string inner;
		std::vector< std::string > innerWrap;
		bool active = true;
		bool alive = true;
		bool changed = false;
		bool focus = false;
		bool hover = false;
		bool visible = true;
		size_t frames = 0;
		Color hoverCol;
	public:
		Element(const size_t& num, const Style& look, const std::string t="Default", const std::string& in="")
			: id(num), style(look), tag(t), inner(in), hoverCol(look.backCol) {}
		Element(const size_t& num, const Style& look, const Color& hovCol, const std::string t="Default", const std::string& in="")
			: id(num), style(look), tag(t), inner(in), hoverCol(hovCol) {}
		virtual void draw();
		virtual bool isFocus();
		virtual void setFocus(bool set);
		std::shared_ptr< CContainer > components;
		const size_t getId();
		std::string getTag();
		Color getHoverCol();
		bool isActive();
		bool isAlive();
		bool isVisible();
		bool isHover();
		bool getHover();
		bool getFocus();
		std::string getInner();
		std::vector< std::string > getInnerWrap();
		Style styling();
		void kill();
		size_t lifetime();
		void repos(const Vector2& newPos);
		void resize(const Vector2& newRadi);
		void recol (const Color& newBack, const Color& newHover);
		void reshape(int newSides);
		void rotate(float rotation);
		void setHoverCol(const Color& col);
		void setInner(const std::string& in);
		void setInnerWrap(std::vector< std::string > in);
		void setTag(const std::string& t, std::shared_ptr< CContainer > comps);
	};

	class Button : public Element // Focus on press; Notify on press;
	{
	public:
		Button(const size_t& num, const Style& look, const std::string t="Default", const std::string& in="") 
			: Element(num, look, (Color){look.backCol.r - 10, look.backCol.g - 10, look.backCol.b - 10, look.backCol.a}, t, in) {}
		Button(const size_t& num, const Style& look, const Color& hovCol, const std::string t="Default", const std::string& in="") 
			: Element(num, look, hovCol, t, in) {}
		bool isFocus();
	};
	
	class Input : public Element // Focus on hover; Notify on hover, and off hover;
	{
	public:
		Input(const size_t& num, const Style& look, const std::string t="Default", const std::string& in="")
			: Element(num, look, (Color){look.backCol.r, look.backCol.g, look.backCol.b, look.backCol.a}, t, in) {}
		Input(const size_t& num, const Style& look, const Color& hovCol, const std::string t="Default", const std::string& in="") 
			: Element(num, look, hovCol, t, in) {}
		bool isFocus();
	};
	
	class InputButton : public Element // Focus on press; Notify on hover, off hover, and on press;
	{
	public:
		InputButton(const size_t& num, const Style& look, const std::string t="Default", const std::string& in="") 
			: Element(num, look, (Color){look.backCol.r - 10, look.backCol.g - 10, look.backCol.b - 10, look.backCol.a}, t, in) {}
		InputButton(const size_t& num, const Style& look, const Color& hovCol, const std::string t="Default", const std::string& in="") 
			: Element(num, look, hovCol, t, in) {}
		bool isFocus();
	};
	
	class InputToggle : public Element // Toggle Focus on/off on press; Notify on hover, off hover, and on press;
	{
	public:
		InputToggle(const size_t& num, const Style& look, const std::string t="Default", const std::string& in="") 
			: Element(num, look, (Color){look.backCol.r, look.backCol.g, look.backCol.b, look.backCol.a}, t, in) {}
		InputToggle(const size_t& num, const Style& look, const Color& hovCol, const std::string t="Default", const std::string& in="") 
			: Element(num, look, hovCol, t, in) {}
		bool isFocus();
	};
	
	class InputTrigger : public Element // Focus while held; Notify on press, on release, on hover, and off hover;
	{
	public:
		InputTrigger(const size_t& num, const Style& look, const std::string t="Default", const std::string& in="") 
			: Element(num, look, (Color){look.backCol.r - 10, look.backCol.g - 10, look.backCol.b - 10, look.backCol.a}, t, in) {}
		InputTrigger(const size_t& num, const Style& look, const Color& hovCol, const std::string t="Default", const std::string& in="") 
			: Element(num, look, hovCol, t, in) {}
		bool isFocus();
	};
	
	class Toggle : public Element // Toggle Focus on/off on press; Notify on press;
	{
	public:
		Toggle(const size_t& num, const Style& look, const std::string t="Default", const std::string& in="") 
			: Element(num, look, (Color){look.backCol.r, look.backCol.g, look.backCol.b, look.backCol.a}, t, in) {}
		Toggle(const size_t& num, const Style& look, const Color& hovCol, const std::string t="Default", const std::string& in="") 
			: Element(num, look, hovCol, t, in) {}
		bool isFocus();
	};
	
	class Trigger : public Element // Focus while held; Notify on press, and on release;
	{
	public:
		Trigger(const size_t& num, const Style& look, const std::string t="Default", const std::string& in="") 
			: Element(num, look, (Color){look.backCol.r - 10, look.backCol.g - 10, look.backCol.b - 10, look.backCol.a}, t, in) {}
		Trigger(const size_t& num, const Style& look, const Color& hovCol, const std::string t="Default", const std::string& in="") 
			: Element(num, look, hovCol, t, in) {}
		bool isFocus();
	};
	
	class CheckBox : public Toggle // Draw inner on Focus
	{
	public:
		CheckBox(const size_t& num, const Style& look, const std::string t="Default", const std::string& in="") 
			: Toggle(num, look, (Color){look.backCol.r, look.backCol.g, look.backCol.b, look.backCol.a}, t, in) {}
		CheckBox(const size_t& num, const Style& look, const Color& hovCol, const std::string t="Default", const std::string& in="") 
			: Toggle(num, look, hovCol, t, in) {}
		void draw();
	};

	// TODO: fix map so that elements are ordered by time of insertion
	class Page : public CMap // Container for Elements
	{
	protected:
		std::map< std::string, std::vector< std::shared_ptr< Element > > > elements;
		std::map< std::string, std::vector< std::shared_ptr< Element > > > toAdd;
		size_t total = 0;
		bool active = true;
	public:
		Page(bool init=true)
			: active(init) {}
		Page(std::map< std::string, std::shared_ptr< CContainer > > comps, bool init=true)
			: CMap(comps), active(init) {}
		std::map< std::string, std::vector< std::shared_ptr< Element > > > getBody();
		std::shared_ptr< Element > getElement(size_t id);
		std::vector< std::shared_ptr< Element > > getElements(const std::string& tag);
		std::vector< std::shared_ptr< Element > > getElements();
		size_t size();
		bool isActive();
		void clearElements();
		void removeElement(size_t id);
		void removeElement(std::string id);
		void setActive(bool set);
		void update();
	
		template <class C>
		std::shared_ptr< Element > addElement(const Style& style, const std::string& tag="Default", const std::string& inner="")
		{
			auto e = std::shared_ptr< Element >(new C(total++, style, tag, inner));
			std::shared_ptr< CContainer > components = cmap[tag];
			if ( components )
			{
				e->components = components;
			}
			else if ( e->components )
			{
				components = e->components;
			}
			else
			{
				components = std::make_shared< CContainer >();
				e->components = components;
			}
			CDropDown& dropdown = e->components->getComponent< CDropDown >();
			if ( dropdown.owned  )
			{
				if ( !dropdown.options->getParent() )
				{
					dropdown.options->setParent(e);
				}
			}
			toAdd[tag].push_back(e);
			
			return e;
		}
	};
	
	// TODO: implement spacing and alignment
	class DropDown : public Page
	{
	private:
		std::shared_ptr< Element > parent;
		TextWrap wrap = TextWrap::NONE;
	public:
		DropDown(std::shared_ptr< Element > p, std::map< std::string, std::shared_ptr< CContainer > > comps, const TextWrap& w=TextWrap::NONE, bool init=false)
			: Page(comps, init), parent(p), wrap(w) {}
		DropDown(std::shared_ptr< Element > p, const TextWrap& w=TextWrap::NONE, bool init=false)
			: Page(init), parent(p), wrap(w) {}
		std::shared_ptr< Element > getParent();
		TextWrap getWrap();
		void setParent(std::shared_ptr< Element > elem);
		void wrapElements(const TextWrap& wrapStyle);
		
		template <class C>
		std::shared_ptr< Element > addElement(const Style& style, const std::string& tag="Option", const std::string& inner="")
		{
			auto e = std::shared_ptr< Element >(new C(total++, style, tag, inner));
			std::shared_ptr< CContainer > components = cmap[tag];
			if ( components )
			{
				e->components = components;
			}
			else if ( e->components )
			{
				components = e->components;
			}
			else
			{
				components = std::make_shared< CContainer >();
				e->components = components;
			}
			CDropDown& dropdown = e->components->getComponent< CDropDown >();
			if ( dropdown.owned  )
			{
				if ( !dropdown.options->getParent() )
				{
					dropdown.options->setParent(e);
				}
			}
			toAdd[tag].push_back(e);
			
			return e;
		}
		
		template <class C>
		std::shared_ptr< Element > addElement(const std::string& tag, const std::string& inner)
		{
			Style style = parent->styling();
			switch (wrap)
			{
				case TextWrap::NONE:
				{
					
					break;
				}
				
				case TextWrap::DOWN:
				{
					style.pos.y += style.radius.y * 2 * (total + 1) + style.outlineThick;
					
					break;
				}
				
				case TextWrap::UP:
				{
					style.pos.y -= style.radius.y * 2 * (total + 1) + style.outlineThick;
					
					break;
				}
				
				case TextWrap::AROUND:
				{
					if ( total == 0 )
					{
						style.pos.y -= style.radius.y * 2 * (total + 1) + style.outlineThick;
					}
					else if ( total % 2 == 0 )
					{
						style.pos.y -= style.radius.y * 2 * ((total + 2) / 2) + style.outlineThick;
					}
					else
					{
						style.pos.y += style.radius.y * 2 * ((total + 2) / 2) + style.outlineThick;
					}
					
					break;
				}
			}
			
			return addElement< C >(style, tag, inner);
		}
		
		template <class C>
		std::shared_ptr< Element > addElement(const std::string& inner="")
		{
			
			return addElement< C >("Option", inner);
		}
	};

	// TODO: decouple event system
	class GUIManager : public Notifier, public NoMVC::Model // handles Pages and Notifications
	{
	private:
		std::vector< std::shared_ptr< Page > > pages;
	public:
		GUIManager(bool withPg=true);
		GUIManager(std::shared_ptr< Page > pg);
		GUIManager(std::vector< std::shared_ptr< Page > > pgs)
			: pages(pgs) {}
		std::shared_ptr< DropDown > addDropDown(std::shared_ptr< Element > parent, std::map< std::string, std::shared_ptr< CContainer > > comps, const TextWrap& wrap=TextWrap::NONE, bool init=false);
		std::shared_ptr< DropDown > addDropDown(std::shared_ptr< Element > parent, const TextWrap& wrap=TextWrap::NONE, bool init=false);
		std::shared_ptr< Page > addPage(std::map< std::string, std::shared_ptr< CContainer > > comps, bool active=false);
		std::shared_ptr< Page > addPage(bool active=false);
		std::shared_ptr< Page > addPage(std::shared_ptr< Page > page);
		std::shared_ptr< Page > getPage(int pageIndex=0);
		size_t size();
		void removeElement(size_t id, int pageIndex=0);
		void removeElement(const std::string& id, int pageIndex=0);
		void removePage(int pageIndex);
		void update();
		void render();
		void setActive(size_t index);
	
		template <class C>
		std::shared_ptr< Element > addElement(const Style& style, const std::string& tag="", const std::string& inner="", int pageIndex=0)
		{
		
			return pages[pageIndex]->addElement< C >(style, tag, inner);
		}
	};

	// Functions
	Vector2 alignTextLeft(const CText& fmt, const Style& elem, int lineNum = 0);
	Vector2 alignTextCenter(const char* text, const CText& fmt, const Style& elem, int lineNum = 0);
	Vector2 alignTextTop(const char* text, const CText& fmt, const Style& elem, int lineNum = 0);
	Vector2 alignTextBottom(const char* text, const CText& fmt, const Style& elem, int lineNum = 0);
	Vector2 alignTextBottomLeft(const char* text, const CText& fmt, const Style& elem, int lineNum = 0);
	Vector2 alignTextBottomRight(const char* text, const CText& fmt, const Style& elem, int lineNum = 0);
	Vector2 alignTextRight(const char* text, const CText& fmt, const Style& elem, int lineNum = 0);
	Vector2 alignText(const char* text, const CText& fmt, const Style& elem, int lineNum = 0);
	std::vector< std::string > wrapText(const char* text, const CText& fmt, int width = std::numeric_limits<int>::max());
	std::string collectInput(Element* elem);
	void DrawGUIElement(Element* elem);
	void DrawGUIStyle(const Style& elem);
	void DrawGUIStyles(const Style& elem, const CMultiStyle& children);
	void DrawGUIText(const char * text, const CText& fmt, const Style& elem);
	void DrawGUITextV(const char* text, const CText& fmt, const Vector2& pos);
	void DrawGUITextWrapped(const std::vector<std::string>& text, CText fmt, const Style& elem);
	void DrawGUIImage(const CImage& fmt, const Style& elem);
}