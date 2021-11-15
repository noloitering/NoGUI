#pragma once

#include <vector>
#include <memory>

namespace NoGUI
{
	class Element;

	class Listener
	{
	public:
		Listener() {}
		virtual ~Listener() {}
		virtual void onNotify(std::shared_ptr< Element > elem) = 0;
	};

	// TODO: handle dynamic allocation better
	class Notifier
	{
	private:
		std::vector< std::shared_ptr< Listener > > listeners;
		size_t total;
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
}