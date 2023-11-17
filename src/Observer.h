#pragma once

#include <vector>
#include <memory>

namespace NoGUI
{
	class Element;
	enum Event {ONHOVER=1, HOVERING=2, OFFHOVER=4, ONFOCUS=8, FOCUSING=16, OFFFOCUS=32};
	
	class Listener
	{
	public:
		Listener() {}
		virtual ~Listener() {}
		virtual void onNotify(std::shared_ptr< Element > elem, Event event) = 0;
	};

	// TODO: handle dynamic allocation better
	class Notifier
	{
	private:
		std::vector< std::shared_ptr< Listener > > listeners;
		size_t total;
	protected:
		void notify(std::shared_ptr< Element > elem, Event event)
		{
			for (auto l : listeners)
			{
				l->onNotify(elem, event);
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
}