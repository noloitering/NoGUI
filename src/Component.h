#pragma once

#include <memory>
#include <variant>
#include <vector>

#include "raylib.h"
namespace NoGUI
{
	const size_t BUFFER = 256;
	enum class Crop {NONE, FIT, SCROLL};
	enum class TextAlign {LEFT, CENTER, RIGHT, TOP, BOTTOM, BOTTOML, BOTTOMR};
	enum class TextWrap {NONE = 0, DOWN = 1, UP = -1, AROUND = 2};

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
		std::vector< std::string > contents;
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
		size_t cap;
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

	typedef std::tuple< CText, CImage, CInput, CMultiStyle > Components;
	typedef std::tuple< std::vector < CText >, std::vector < CImage >, std::vector < CInput >, std::vector< CMultiStyle > > CompContainer;
	typedef std::variant< CText, CImage, CInput, CMultiStyle > Component;
}