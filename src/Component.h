#pragma once

#include <memory>
#include <variant>
#include <vector>

#include "raylib.h"
namespace NoGUI
{
	const size_t BUFFER = 256;
	const size_t NUMCOMPONENTS = 5;
	enum class Crop {NONE, FIT, SCROLL};
	enum class TextAlign {LEFT, CENTER, RIGHT, TOP, BOTTOM, BOTTOML, BOTTOMR};
	enum class Align {NONE, LEFT, CENTER, RIGHT, TOP, BOTTOM};
	enum class TextWrap {NONE = 0, DOWN = 1, UP = -1, AROUND = 2};
	class DropDown;

	struct Style
	{
		Color backCol = GRAY;
		Color outlineCol = BLACK;
		Vector2 pos;
		Vector2 radius;
		int sides = 4;
		int outlineThick = 0;
		float rotation = 0;
	};

	struct Shadow
	{
		Color col = BLACK;
		Vector2 offset = {0, 0};
		bool draw = false;
	};

	class CInterface
	{
	public:
		bool owned = false;
	};

	class CText : public CInterface
	{
	public:
		// default
		CText(std::shared_ptr< Font > f=nullptr, float s=20, float r=0, const Vector2& space={4, 0}, const Vector2& m={0, 0}, const Color& c=WHITE, TextAlign a=TextAlign::LEFT, TextWrap w=TextWrap::NONE, bool scl = false)
			: font(f), size(s), rotation(r), spacing(space), margin(m), col(c), align(a), wrap(w), scale(scl) {}
		// with shadow
		CText(const Shadow& shade, std::shared_ptr< Font > f=nullptr, float s=20, float r=0, const Vector2& space={4, 0}, const Vector2& m={0, 0}, const Color& c=WHITE, TextAlign a=TextAlign::LEFT, TextWrap w=TextWrap::NONE, bool scl = false)
			: shadow(shade), font(f), size(s), rotation(r), spacing(space), margin(m), col(c), align(a), wrap(w), scale(scl) {}
		Shadow shadow;
		Crop cropping = Crop::NONE; // TODO: implement
		std::shared_ptr< Font > font; // TTF, XNA fonts, AngelCode fonts
		float size = 20; // font size
		float rotation = 0; // TODO: implement
		Vector2 spacing = {4, 0};
		Vector2 margin = {0, 0};
		Color col = WHITE; // font colour (RGBA)
		TextAlign align = TextAlign::LEFT;
		TextWrap wrap = TextWrap::NONE;
		bool scale = false; // TODO: implement
	};

	class CImage : public CInterface
	{
	public:
		CImage(std::shared_ptr< Texture2D > t=nullptr, const Vector2& s={1, 1}, float r=0, const Vector2& m={0, 0}, const Color& c=WHITE)
			: texture(t), scale(s), rotation(r), margin(m), col(c) {}
		Crop cropping = Crop::FIT;
		std::shared_ptr< Texture2D > texture;
		Vector2 scale = {1, 1};
		float rotation = 0;
		Vector2 margin = {0, 0};
		Color col = WHITE; // font colour (RGBA)
	};

	class CInput : public CInterface
	{
	public:
		CInput(size_t max=BUFFER, size_t current=0)
			: cap(max), i(current) {}
		size_t cap = BUFFER;
		size_t i = 0;
	};

	class CMultiStyle : public CInterface
	{
	public:
		CMultiStyle() {}
		CMultiStyle(const std::vector< Style >& s)
			: styles(s) {}
		CMultiStyle(const Style& s) {styles.push_back(s);}
		std::vector< Style > styles;
	};
	
	// TODO: This component does not hold pure data
	class CDropDown : public CInterface
	{
	public:
		CDropDown() {}
		CDropDown(const std::shared_ptr< DropDown > o)
			: options(o) {}
		
		std::shared_ptr< DropDown > options;
	};

	typedef std::tuple< CText, CImage, CInput, CMultiStyle, CDropDown > Components;
	typedef std::tuple< std::vector < CText >, std::vector < CImage >, std::vector < CInput >, std::vector< CMultiStyle >, std::vector< CDropDown > > CompContainer;
	typedef std::variant< CText, CImage, CInput, CMultiStyle, CDropDown > Component;
	
	class CContainer
	{
	protected:
		Components components;
	public:
		CContainer() {}
		CContainer(Components c)
			: components(c) {}
		virtual ~CContainer() {}
		
		Components getComponents()
		{
			
			return components;
		}
		
		void setComponents(Components c)
		{
			components = c;
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
	
	class CMap
	{
	protected:
		std::map< std::string, std::shared_ptr< CContainer > > cmap;
	public:
		CMap() {}
		CMap(std::map< std::string, std::shared_ptr< CContainer > > compMap)
			: cmap(compMap) {}
		virtual ~CMap() {}
		
		std::map< std::string, std::shared_ptr< CContainer > > getCMap()
		{
			
			return cmap;
		}
		
		std::shared_ptr< CContainer > getComponents(const std::string& key)
		{
			
			return cmap[key];
		}
		
		void addComponents(const std::string& key, std::shared_ptr< CContainer > comps)
		{
			cmap[key] = comps;
		}
		
		std::shared_ptr< CContainer > addComponents(const std::string& key, CContainer comps)
		{
			cmap[key] = std::make_shared< CContainer >(comps);
			
			return cmap[key];
		}
		
		std::shared_ptr< CContainer > addComponents(const std::string& key, Components comps)
		{
			cmap[key] = std::make_shared< CContainer >(comps);
			
			return cmap[key];
		}
		
		std::shared_ptr< CContainer > addComponents(const std::string& key)
		{
			cmap[key] = std::make_shared< CContainer >();
			
			return cmap[key];
		}
	};
}