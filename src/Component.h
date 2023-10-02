#pragma once

#include <memory>
//#include <math.h>
#include <vector>
//#include <variant>

namespace NoGUI
{
	class Transform;
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
	
	// TODO: change n to unsigned int
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
		Vector2 scale = {1.0f, 1.0f};
		Vector2 scrollPos = {0.5f, 0.5f};
	};
	
	class CText : public CInterface
	{
	public:
		CText(std::shared_ptr< Fill > col=nullptr, std::shared_ptr< Font > style=nullptr, float big=20.0f, const Align& pos=Align(), const Wrap& wrapping=Wrap::DOWN, float rotation=0.0f, const Vector2& space={2,0})
			:  fill(col), font(style), align(pos), wrap(wrapping), spacing(space), size(big), angle(rotation) {}
		std::shared_ptr< Fill > fill;
		std::shared_ptr< Font > font;
		Align align;
		Wrap wrap = Wrap::DOWN;
		Vector2 spacing = {2.0f, 0.0f};
		float size = 20.0f;
		float angle = 0.0f;
	};
	
	// TODO: Text flow/direction/wrap and rotation
	class CTextBox : public CInterface
	{
	public:
		CTextBox(std::shared_ptr< Fill > col=nullptr, std::shared_ptr< Font > style=nullptr, float big=20.0f, const Align& pos=Align(), bool wrapText=false, const Vector2& space={2,0})
			:  fill(col), font(style), align(pos), spacing(space), wrap(wrapText), size(big) {}
		std::shared_ptr< Fill > fill;
		std::shared_ptr< Font > font;
		Align align;
//		Wrap wrap = Wrap::DOWN;
		Vector2 spacing = {2.0f, 0.0f};
		Vector2 scrollAmount = {0.0f, 0.0f};
		bool wrap = false;
		float size = 20.0f;
	};
	
	class CMultiShape : public CInterface
	{
	public:
		CMultiShape(bool hoverable=false) 
			: collision(hoverable) {}
		std::vector< std::pair< std::shared_ptr< nShape >, Transform > > shapes;
		bool collision = false;
	};
	
	typedef std::tuple< CImage, CText, CTextBox, CMultiShape > Components;
	
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