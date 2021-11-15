#pragma once

#include <iostream>
#include <string>
#include <map>
#include <tuple>
#include <limits>

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
		std::string inner;
		bool active = true;
		bool alive = true;
		bool changed = false;
		bool focus = false;
		bool hover = false;
		bool visible = true;
		size_t frames = 0;
		Components components;
		Color hoverCol;
	public:
		Element(const size_t& num, const Style& look, const std::string& in="")
			: id(num), style(look), inner(in), hoverCol(look.backCol) {}
		Element(const size_t& num, const Style& look, const Color& hovCol, const std::string& in="")
			: id(num), style(look), inner(in), hoverCol(hovCol) {}
		
		virtual void draw();
		virtual bool isFocus();
		virtual void setFocus(bool set);
		Color getHoverCol();
		const size_t id = 0;
		bool isActive();
		bool isAlive();
		bool isVisible();
		bool isHover();
		bool getHover();
		bool getFocus();
		std::string getInner();
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
	
		template <class C>
		C& getComponent()
		{
			
			return std::get< C >(components);
		}
	
		template <class C, typename... Args>
		C& addComponent(Args&&... CArgs)
		{
			auto& component = getComponent<C>();
			component = C(std::forward<Args>(CArgs)...);
			component.owned = true;
		
			return component;
		}
	
		template <class C>
		C& addComponent(C& newComponent)
		{
			auto& component = getComponent< C >();
			component = newComponent;
			component.owned = true;
		
			return component;
		}
	
		template <class C>
		bool hasComponent()
		{
		
			return getComponent< C >().owned;
		}
	};

	class Button : public Element // Focus on press; Notify on press;
	{
	public:
		Button(const size_t& num, const Style& look, const std::string& in="") 
			: Element(num, look, (Color){look.backCol.r - 10, look.backCol.g - 10, look.backCol.b - 10, look.backCol.a}, in) {}
		Button(const size_t& num, const Style& look, const Color& hovCol, const std::string& in="") 
			: Element(num, look, hovCol, in) {}
		bool isFocus();
	};
	
	class Input : public Element // Focus on hover; Notify on hover, and off hover;
	{
		public:
		Input(const size_t& num, const Style& look, const std::string& in="")
			: Element(num, look, (Color){look.backCol.r, look.backCol.g, look.backCol.b, look.backCol.a}, in) {}
		Input(const size_t& num, const Style& look, const Color& hovCol, const std::string& in="") 
			: Element(num, look, hovCol, in) {}
		bool isFocus();
	};
	
	class InputButton : public Element // Focus on press; Notify on hover, off hover, and on press;
	{
	public:
		InputButton(const size_t& num, const Style& look, const std::string& in="") 
			: Element(num, look, (Color){look.backCol.r - 10, look.backCol.g - 10, look.backCol.b - 10, look.backCol.a}, in) {}
		InputButton(const size_t& num, const Style& look, const Color& hovCol, const std::string& in="") 
			: Element(num, look, hovCol, in) {}
		bool isFocus();
	};
	
	class InputToggle : public Element // Toggle Focus on/off on press; Notify on hover, off hover, and on press;
	{
	public:
		InputToggle(const size_t& num, const Style& look, const std::string& in="") 
			: Element(num, look, (Color){look.backCol.r, look.backCol.g, look.backCol.b, look.backCol.a}, in) {}
		InputToggle(const size_t& num, const Style& look, const Color& hovCol, const std::string& in="") 
			: Element(num, look, hovCol, in) {}
		bool isFocus();
	};
	
	class InputTrigger : public Element // Focus while held; Notify on press, on release, on hover, and off hover;
	{
		InputTrigger(const size_t& num, const Style& look, const std::string& in="") 
			: Element(num, look, (Color){look.backCol.r - 10, look.backCol.g - 10, look.backCol.b - 10, look.backCol.a}, in) {}
		InputTrigger(const size_t& num, const Style& look, const Color& hovCol, const std::string& in="") 
			: Element(num, look, hovCol, in) {}
		bool isFocus();
	};
	
	class Toggle : public Element // Toggle Focus on/off on press; Notify on press;
	{
	public:
		Toggle(const size_t& num, const Style& look, const std::string& in="") 
			: Element(num, look, (Color){look.backCol.r, look.backCol.g, look.backCol.b, look.backCol.a}, in) {}
		Toggle(const size_t& num, const Style& look, const Color& hovCol, const std::string& in="") 
			: Element(num, look, hovCol, in) {}
		bool isFocus();
	};
	
	class Trigger : public Element // Focus while held; Notify on press, and on release;
	{
	public:
		Trigger(const size_t& num, const Style& look, const std::string& in="") 
			: Element(num, look, (Color){look.backCol.r - 10, look.backCol.g - 10, look.backCol.b - 10, look.backCol.a}, in) {}
		Trigger(const size_t& num, const Style& look, const Color& hovCol, const std::string& in="") 
			: Element(num, look, hovCol, in) {}
		bool isFocus();
	};
	
	class CheckBox : public Toggle // Draw inner on Focus
	{
		public:
		CheckBox(const size_t& num, const Style& look, const std::string& in="") 
			: Toggle(num, look, (Color){look.backCol.r, look.backCol.g, look.backCol.b, look.backCol.a}, in) {}
		CheckBox(const size_t& num, const Style& look, const Color& hovCol, const std::string& in="") 
			: Toggle(num, look, hovCol, in) {}
		void draw();
	};

	// TODO: fix map so that elements are ordered by time of insertion
	class Page // Container for Elements
	{
	protected:
		Components components;
		std::map< std::string, std::vector< std::shared_ptr< Element > > > elements;
		std::map< std::string, std::vector< std::shared_ptr< Element > > > toAdd;
		std::map< std::string, size_t > ids;
		size_t total = 0;
		bool active = true;
	public:
		Page(bool init=true);
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
		std::shared_ptr< Element > addElement(const Style& style, const std::string& inner="", const std::string& tag="", const std::string& id="")
		{
			auto e = std::shared_ptr< Element >(new C(total++, style, inner));
			e->components = components;
			toAdd[tag].push_back(e);
			if ( !id.empty() )
			{
				ids[id] = e->id;
			}
			
			return e;
		}
		
		template <class C>
		C& getComponent()
		{
			
			return std::get< C >(components);
		}
	
		template <class C, typename... Args>
		C& addComponent(Args&&... CArgs)
		{
			auto& component = getComponent<C>();
			component = C(std::forward<Args>(CArgs)...);
			component.owned = true;
		
			return component;
		}
	
		template <class C>
		C& addComponent(C& newComponent)
		{
			auto& component = getComponent< C >();
			component = newComponent;
			component.owned = true;
		
			return component;
		}
	
		template <class C>
		bool hasComponent()
		{
		
			return getComponent< C >().owned;
		}
	};
	
	class DropDown : public Page
	{
	private:
		std::shared_ptr< Element > parent;
		TextWrap wrap = TextWrap::NONE;
	public:
		DropDown(std::shared_ptr< Element > p, const TextWrap& w=TextWrap::NONE, bool init=false)
		: Page(init), parent(p), wrap(w) {}
		std::shared_ptr< Element > getParent();
		void setParent(std::shared_ptr< Element > elem);
		void wrapElements(const TextWrap& wrapStyle);
		
		template <class C>
		std::shared_ptr< Element > addElement(const Style& style, const std::string& inner="", const std::string& tag="Option", const std::string& id="")
		{
			auto e = std::shared_ptr< Element >(new C(total++, style, inner));
			e->components = components;
			toAdd[tag].push_back(e);
			if ( !id.empty() )
			{
				ids[id] = e->id;
			}
			
			return e;
		}
		
		template <class C>
		std::shared_ptr< Element > addElement(const std::string& inner="", const std::string& tag="Option", const std::string& id="")
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
			auto e = std::shared_ptr< Element >(new C(total++, style, inner));
			e->components = components;
			toAdd[tag].push_back(e);
			if ( !id.empty() )
			{
				ids[id] = e->id;
			}
			
			return e;
		}
	};

	class GUIManager : public Notifier, public NoMVC::Model // handles Pages and Notifications
	{
	private:
		std::vector< std::shared_ptr< Page > > pages;
	public:
		GUIManager();
	
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
		std::shared_ptr< Element > addElement(const Style& style, const std::string& inner="", const std::string& tag="", int pageIndex=0)
		{
		
			return pages[pageIndex]->addElement< C >(style, inner, tag);
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


