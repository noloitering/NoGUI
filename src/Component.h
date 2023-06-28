#pragma once

#include <memory>
#include <math.h>
//#include <variant>
//#include <vector>

namespace NoGUI
{
	enum class Wrap {NONE = 0, DOWN = 1, UP = -1, AROUND = 2};
	enum class XAlign {LEFT = -1, CENTER = 0, RIGHT = 1};
	enum class YAlign {TOP = -1, CENTER = 0, BOTTOM = 1};
	enum class Crop {NONE, FIT, CUT};
	
	struct Align
	{
		XAlign x = XAlign::CENTER;
		YAlign y = YAlign::CENTER;
		Align(const XAlign& xalign=XAlign::CENTER, const YAlign& yalign=YAlign::CENTER)
			: x(xalign), y(yalign) {}
		Align(int xint, int yint)
		{
			if ( xint < 0 )
			{
				x = XAlign::LEFT;
			}
			else if ( xint > 0 )
			{
				x = XAlign::RIGHT;
			}
			
			if ( yint < 0 )
			{
				y = YAlign::TOP;
			}
			else if ( yint > 0 )
			{
				y = YAlign::BOTTOM;
			}
		}
	};
	
	struct Fill
	{
		Color col;
		Color hoverCol;
		Fill(Color c, Color hc)
			: col(c), hoverCol(hc) {}
		Fill(Color c=WHITE)
			: col(c), hoverCol(c) {}
	};
	
	struct Outline
	{
		std::shared_ptr< Fill > fill;
		int thick = 1;
		Wrap border = Wrap::AROUND; // down = outline into the element, UP = outline outwards from the element, AROUND = outline about center of the element
		Outline(std::shared_ptr< Fill > col, int width=1, const Wrap& style=Wrap::AROUND)
			: fill(col), thick(width), border(style) {}
	};
	
	struct Shadow
	{
		std::shared_ptr< Fill > fill;
		Vector2 offset = {0, 0};
		Shadow(std::shared_ptr< Fill > col, const Vector2& pos)
			: fill(col), offset(pos) {}
	};
	
	struct nShape
	{
		int n = 4;
		std::shared_ptr< Fill > fill;
		std::shared_ptr< Outline > outline;
		nShape(int sides=4, std::shared_ptr< Fill > col=nullptr, std::shared_ptr< Outline > out=nullptr)
			: n(sides), fill(col), outline(out)
			{
				if ( fill == nullptr )
				{
					fill = std::make_shared< Fill >();
				}
				if ( outline == nullptr )
				{
					outline = std::make_shared< Outline >(fill);
				}
			}
	};
	
	class CInterface
	{
	public:
		bool active = false;
	};
	
	class CImage : public CInterface
	{
	public:
		CImage(std::shared_ptr< Texture2D > texture=nullptr, std::shared_ptr< nShape > nshape=nullptr, const Crop& cropping=Crop::NONE, bool scroll=false, const Vector2& scaleVec={1, 1})
			: img(texture), shape(nshape), crop(cropping), scrollable(scroll), scale(scaleVec) {}
		std::shared_ptr< Texture2D > img;
		std::shared_ptr< nShape > shape;
		Crop crop = Crop::NONE;
		bool scrollable = false;
		Vector2 scale = {1, 1};
		Vector2 scrollPos = {0.5, 0.5};
	};
	
	typedef std::tuple< CImage > Components;
	
	class CContainer
	{
	protected:
		Components components;
	public:
		CContainer() {}
		CContainer(Components c)
			: components(c) {}
		
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
			component.active = true;
			
			return component;
		}
		
		template <class C>
		C& addComponent(C& c)
		{
			auto& component = getComponent< C >();
			component = c;
			component.active = true;
			
			return component;
		}
		
		template <class C>
		C& hasComponent()
		{
			
			return getComponent< C >().active;
		}
	};
}