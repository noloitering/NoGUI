# NoGUI
 GUI library for NoMAD Game Engine
## About
NoGUI is a GUI library built upon [raylib](https://github.com/raysan5/raylib) that deploys an [observer/listener](https://gameprogrammingpatterns.com/observer.html) event system. The library conists of Elements, Components, and DOM-like Containers as well as procedural functions to create graphical user interfaces with.
## Procedural Use
Styles are structs that hold shape data:
```
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
```
NoGUI provides functions for drawing Styles to a window:
```
void DrawGUIStyle(const Style& elem);
void DrawGUIStyles(const Style& elem, const CMultiStyle& children);
void DrawGUIText(const char * text, const CText& fmt, const Style& elem);
void DrawGUITextV(const char* text, const CText& fmt, const Vector2& pos);
void DrawGUITextWrapped(const std::vector<std::string>& text, CText fmt, const Style& elem);
void DrawGUIImage(const CImage& fmt, const Style& elem);
```
## Components
Components hold additional data to be drawn like fonts, text shadow, margins, textures, and more. Components can be added to Elements, or can be passed to the procedural functions listed above. Currently there are 5 different components [which can be viewed here](https://twitter.com/NoLoStudios/status/1462439012984139778)
1) CText - holds text data such as font, size, position, shadow, etc
2) CImage - holds image data
3) CMultiStyle - holds a vector of Styles to be positioned relative to another "parent" Style or Element
4) CInput - allows a user to enter text input into a hovered Element. Holds data on the max number of characters allowed to be entered through this method
5) CDropDown - holds a Page of Elements to be drawn when the "parent" Element is focused

https://user-images.githubusercontent.com/93274535/144685917-7e7d964d-155f-4bbb-9598-1f6a21ebd082.mp4

## Elements
Elements wrap a Style and provide it with 2 binary states: focus, and hover. Hover is mainly handled by the library but the focus state is programmable through the `virtual isFocus()` function. NoGUI offers several implementations that may be useful. [They are showcased in this video](https://twitter.com/NoLoStudios/status/1462439012984139778) which can be compiled for yourself in `examples/components`

https://user-images.githubusercontent.com/93274535/144684876-72213395-1ca0-4b3f-9bef-967ff03505b5.mp4

## Pages
Pages are a container for Elements. They are held in a map that is stored alphabetically by key. Multiple Elements can have the same key since each Element also has a unique identifier for it within a page. This is to simulate the "class" and "id" attributes seen in Document Object Models. It should noted that Pages should be updated whenever an element is added or removed through the `void update()` function.
## Manager
The GUI Manager is a container and helper class for Pages. It holds Pages within a vector and also notifies Listeners whenever an event occurs. It also contains some wrappers for Page functions.
## Event System
NoGUI uses an observer/listener event system:
```
class Listener
{
public:
	Listener() {}
	virtual ~Listener() {}
	virtual void onNotify(std::shared_ptr< Element > elem) = 0;
};

class Notifier
{
private:
	std::vector< std::shared_ptr< Listener > > listeners;
protected:
	void notify(std::shared_ptr< Element > elem)
	{	
		for (auto l : listeners)
		{
			l->onNotify(elem);
		}
	}
public:
	size_t addListener(std::shared_ptr< Listener > listener)
	{
		listeners.push_back(listener);
	
		return listeners.size() - 1;
	}
	
	void removeListener(size_t pos)
	{
		listeners.erase(listeners.begin() + pos - 1);
	}
};
```
Objects that are intended to recieve events inherit from the Listener class and are then added to a Notifier object. Whenever the Notifier calls `void notify(std::shared_ptr< Element >)` the Listener's `void onNotify(std::shared_ptr< Element >)` function is called. The Elements hover and focus states can then be used to contextualize what event occured. To help understand this concept, the GUI Manager Class inherits from Notifier in the code example provided here: https://github.com/noloitering/NoGUI/blob/main/examples/types/main.cpp 
